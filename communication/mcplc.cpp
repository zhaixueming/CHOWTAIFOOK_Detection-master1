#include <QThread>
#include <thread>
#include <QDebug>
#include "mcplc.h"

namespace vimo::display
{
	MCPLC &MCPLC::getInstance()
	{
		static MCPLC _plc;
		return _plc;
	}

	MCPLC::MCPLC()
	{
		
	}

	MCPLC::~MCPLC()
	{
		//m_socket_device->disconnect();
	}

	void MCPLC::startLoop()
	{
		m_running = true;
		start();
	}

	void MCPLC::stopLoop()
	{
		sendboolwrite_queue.clear();		
		sendboolRead_queue.clear();		
		sendintwrite_queue.clear();	
		sendintRead_queue.clear();		
		sendstringwrite_queue.clear();		
		sendstringRead_queue.clear();		
		read_queue.clear();		
		m_running = false;
		wait();
		quit();
		m_socket_device->disconnect();
	}

	void MCPLC::run()
	{
		std::string sysparamDir = QCoreApplication::applicationDirPath().toStdString() + "\\SysParamConfig.json";
		_systemparam = config_set->GetSystemParamFromFile(sysparamDir);

		m_socket_device = new QTcpSocket();
		connect(m_socket_device, SIGNAL(readyRead()), this, SLOT(ReadMessage()), Qt::DirectConnection);

		m_socket_device->connectToHost(QString::fromStdString(_systemparam.plc_ipadd), std::stoi(_systemparam.plc_port));
		if (m_socket_device->waitForConnected(1000))
		{
			binit = true;
			emit this->plcinit("PLC init success");
			qDebug() << "PLC init success";
		}
		else
		{
			binit = false;
			emit this->plcinit("PLC init failed");
			qDebug() << "PLC init failed";
		}

		while (m_running && binit)
		{
			if (sendboolwrite_queue.size() > 0)
			{
				sendboolwrite_mutex.lock();
				Plcbool _boolwrite = sendboolwrite_queue.front();
				sendboolwrite_queue.pop_front();
				sendboolwrite_mutex.unlock();

				sendWritebool(_boolwrite.address, _boolwrite.data);
				msleep(10);
			}
			
			if (sendboolRead_queue.size() > 0)
			{
				sendboolRead_mutex.lock();
				QString address = sendboolRead_queue.front();
				sendboolRead_queue.pop_front();
				sendboolRead_mutex.unlock();

				bool result = sendReadbool(address);				
				msleep(10);
			}
			
			if (sendintwrite_queue.size() > 0)
			{
				sendintwrite_mutex.lock();
				Plcint _intwrite = sendintwrite_queue.front();
				sendintwrite_queue.pop_front();
				sendintwrite_mutex.unlock();

				sendWriteint16(_intwrite.address, _intwrite.data);
				msleep(10);
			}
			
			if (sendintRead_queue.size() > 0)
			{
				sendintRead_mutex.lock();
				QString address = sendintRead_queue.front();
				sendintRead_queue.pop_front();
				sendintRead_mutex.unlock();

				int result = sendReadint16(address);
				Plcint _plcint;
				_plcint.address = address;
				_plcint.data = result;

				if (address == QString::fromStdString(_systemparam.plc_lcodestart))
				{
					LeftReadl::getInstance().Mutexstart.lock();
					LeftReadl::getInstance().Queuestart.append(result);
					LeftReadl::getInstance().Mutexstart.unlock();

					LeftReadr::getInstance().Mutexstart.lock();
					LeftReadr::getInstance().Queuestart.append(result);
					LeftReadr::getInstance().Mutexstart.unlock();
				}
				else if (address == QString::fromStdString(_systemparam.plc_rcodestart))
				{
					RightReadl::getInstance().Mutexstart.lock();
					RightReadl::getInstance().Queuestart.append(result);
					RightReadl::getInstance().Mutexstart.unlock();

					RightReadr::getInstance().Mutexstart.lock();
					RightReadr::getInstance().Queuestart.append(result);
					RightReadr::getInstance().Mutexstart.unlock();
				}

				msleep(10);
			}
			
			if (sendstringwrite_queue.size() > 0)
			{
				sendstringwrite_mutex.lock();
				Plcstring _stringwrite = sendstringwrite_queue.front();
				sendstringwrite_queue.pop_front();
				sendstringwrite_mutex.unlock();

				sendWritestring(_stringwrite.address, _stringwrite.data);
				msleep(10);
			}
			
			if (sendstringRead_queue.size() > 0)
			{
				sendstringRead_mutex.lock();
				Plcstring _stringread = sendstringRead_queue.front();
				sendstringRead_queue.pop_front();
				sendstringRead_mutex.unlock();

				QString result = sendReadstring(_stringread.address, _stringread.num);
				
				if (_stringread.address == QString::fromStdString(_systemparam.plc_lcodeback))
				{
					emit this->plcreturnstringl(result);
				}
				else if (_stringread.address == QString::fromStdString(_systemparam.plc_rcodeback))
				{
					emit this->plcreturnstringr(result);
				}			
				msleep(10);
			}
			
		}
	}

	bool MCPLC::sendReadbool(QString address)
	{
		bool result = false;
		QString head = address.mid(0, 1);
		QString num = address.mid(1, address.length() - 1);

		QString chunk;
		QString str;
		QString addressnum;
		if (head == "D")
			chunk = "A8";
		if (head == "M")
			chunk = "90";

		QString Val = QString::number(num.toInt(), 16);
		int length = 6 - Val.length();
		for (int i = 0; i < length; i++)
		{
			Val = "0" + Val;
		}

		addressnum = Val.mid(4, 2) + " " + Val.mid(2, 2) + " " + Val.mid(0, 2);

		bool bsend = sendRead(addressnum, chunk);
		if (bsend)
		{
			while (true)
			{
				if (read_queue.size() > 0)
				{
					read_mutex.lock();
					QString result = read_queue.front();
					read_queue.pop_front();
					read_mutex.unlock();
					//qDebug() << result;
					if (result.length() == 26)
					{
						QString str = result.mid(22, 2);
						if (str == "01")
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
		return bsend;
	}

	bool MCPLC::sendWritebool(QString address, bool data)
	{
		QString head = address.mid(0, 1);
		QString num = address.mid(1, address.length() - 1);

		QString chunk;
		QString str;
		QString addressnum;
		if (head == "D")
			chunk = "A8";
		if (head == "M")
			chunk = "90";

		QString Val = QString::number(num.toInt(), 16);
		int length = 6 - Val.length();
		for (int i = 0; i < length; i++)
		{
			Val = "0" + Val;
		}
		addressnum = Val.mid(4, 2) + " " + Val.mid(2, 2) + " " + Val.mid(0, 2);

		if (data)
			str = "01 00";
		else
			str = "00 00";

		bool result = sendWrite(addressnum, chunk, str);
		if (result)
		{
			while (true)
			{
				if (read_queue.size() > 0)
				{
					read_mutex.lock();
					QString result = read_queue.front();
					read_queue.pop_front();
					read_mutex.unlock();
					break;
				}
			}
		}
		return result;
	}

	int MCPLC::sendReadint16(QString address)
	{
		int result = 999;
		QString head = address.mid(0, 1);
		QString num = address.mid(1, address.length() - 1);

		QString chunk;
		QString str;
		QString addressnum;
		if (head == "D")
			chunk = "A8";
		if (head == "M")
			chunk = "90";

		QString Val = QString::number(num.toInt(), 16);
		int length = 6 - Val.length();
		for (int i = 0; i < length; i++)
		{
			Val = "0" + Val;
		}
		addressnum = Val.mid(4, 2) + " " + Val.mid(2, 2) + " " + Val.mid(0, 2);

		bool bsend = sendRead(addressnum, chunk);
		if (bsend)
		{
			while (true)
			{
				if (read_queue.size() > 0)
				{
					read_mutex.lock();
					QString resultstr = read_queue.front();
					read_queue.pop_front();
					read_mutex.unlock();

					if (resultstr.length() == 26)
					{
						QString str = resultstr.mid(22, 4);
						QString str1 = str.mid(2, 2) + str.mid(0, 2);
						bool ok;
						int hexnum = str1.toInt(&ok, 16);
						if (ok)
						{
							return hexnum;
						}
						else
						{
							return result;
						}
					}
					else
					{
						return result;
					}
				}
				return result;
			}
		}
		return result;
	}

	bool MCPLC::sendWriteint16(QString address, int data)
	{
		QString head = address.mid(0, 1);
		QString num = address.mid(1, address.length() - 1);

		QString chunk;
		QString str;
		QString addressnum;
		if (head == "D")
			chunk = "A8";
		if (head == "M")
			chunk = "90";

		QString Val = QString::number(num.toInt(), 16);
		int length = 6 - Val.length();
		for (int i = 0; i < length; i++)
		{
			Val = "0" + Val;
		}
		addressnum = Val.mid(4, 2) + " " + Val.mid(2, 2) + " " + Val.mid(0, 2);

		QString Valsend = QString::number(data, 16);

		int lengthsend = 4 - Valsend.length();
		for (int i = 0; i < lengthsend; i++)
		{
			Valsend = "0" + Valsend;
		}
		str = Valsend.mid(2, 2) + " " + Valsend.mid(0, 2);

		bool result = sendWrite(addressnum, chunk, str);
		if (result)
		{
			while (true)
			{
				if (read_queue.size() > 0)
				{
					read_mutex.lock();
					QString result = read_queue.front();
					read_queue.pop_front();
					read_mutex.unlock();
					break;
				}
			}
		}
		return result;
	}

	QString MCPLC::sendReadstring(QString address, int num)
	{
		int count = num / 2 + num % 2;
		int stringcount = address.length();
		QString sendaddress;
		QString resultstring;
		for (int i = 0; i < count; i++)
		{
			sendaddress = address.mid(0, stringcount - 1) + QString::number(i + address.mid(stringcount - 1, 1).toInt());
			int result = sendReadint16(sendaddress);
			resultstring = resultstring + asciiinttostring(result);
		}
		QChar h0 = 0x00;
		if (resultstring.contains(h0))
		{
			resultstring.replace(h0, "");
		}
		return resultstring;
	}

	bool MCPLC::sendWritestring(QString address, QString data)
	{
		int stringcount = address.length();
		int datacount = data.count();
		int count = datacount / 2 + datacount % 2;
		QString sendaddress;
		QString senddata;
		for (int i = 0; i < count; i++)
		{
			sendaddress = address.mid(0, stringcount - 1) + QString::number(i + address.mid(stringcount - 1, 1).toInt());
			if (i * 2 + 1 < datacount)
			{
				senddata = data.mid(i * 2, 2);
			}
			else
			{
				senddata = data.mid(i * 2, 1);
			}
			if (!sendWriteint16(sendaddress, asciiinttostring(senddata)))
				return false;
		}
		return true;
	}

	QString MCPLC::asciiinttostring(int asciiint)
	{
		int a0 = asciiint;
		int a1 = asciiint;
		a0 = a0 & 0xFF;
		a1 = a1 >> 8;

		QString string0 = (char)a0;
		QString string1 = (char)a1;

		QString resultstring = string0 + string1;
		return resultstring;
	}

	int MCPLC::asciiinttostring(QString asciistring)
	{
		int *a = (int *)malloc(sizeof(int)*asciistring.toStdString().length() + 1);
		a[0] = asciistring.toStdString()[0];
		a[1] = asciistring.toStdString()[1];

		int a0 = a[0];
		int a1 = a[1];
		a1 = a1 << 8;
		int returnint = a1 + a0;
		return returnint;
	}

	bool MCPLC::sendRead(QString addressnum, QString chunk)
	{
		QString head = "50 00 00 FF FF 03 00";
		//数据长度
		QString length = "0C 00";
		QString timeout = "10 00";
		//读写
		QString command = "01 04";//"01 14";写//"01 04";读
		QString subCommand = "00 00";
		//地址
		//地址块
		//个数
		QString count = "01 00";

		QString data = timeout + " " + command + " " + subCommand + " " + addressnum + " " + chunk + " " + count;
		QString temp = data;
		QRegExp regExp("[^a-fA-F0-9]");
		temp.replace(regExp, "");
		QString ret = head + " " + length + " " + data;

		QByteArray arrayHex = QByteArray::fromHex(ret.toLatin1());	// 使用 16 进制格式

		m_socket_device->write(arrayHex);
		bool socketbool = m_socket_device->waitForBytesWritten(1000);
		m_socket_device->flush();
		m_socket_device->waitForReadyRead();
		return socketbool;
	}

	bool MCPLC::sendWrite(QString addressnum, QString chunk, QString str)
	{
		QString head = "50 00 00 FF FF 03 00";
		//数据长度
		QString length = "0E 00";
		QString timeout = "10 00";
		//读写
		QString command = "01 14";//"01 14";写//"01 04";读
		QString subCommand = "00 00";
		//地址
		//地址块
		//个数
		QString count = "01 00";
		QString data = timeout + " " + command + " " + subCommand + " " + addressnum + " " + chunk + " " + count + " " + str;
		QString temp = data;
		QRegExp regExp("[^a-fA-F0-9]");
		temp.replace(regExp, "");
		QString ret = head + " " + length + " " + data;

		QByteArray array = QByteArray::fromHex(ret.toLatin1());	// 使用 16 进制格式
		m_socket_device->write(array);
		bool socketbool = m_socket_device->waitForBytesWritten(1000);
		m_socket_device->flush();
		m_socket_device->waitForReadyRead();
		return socketbool;
	}

	void MCPLC::ReadMessage()
	{
		if (m_socket_device->state() == QAbstractSocket::ConnectedState)
		{			
			QByteArray ba = m_socket_device->readAll();
			if (ba.size() > 0)
			{
				QString data = ba.toHex().toUpper();
				read_mutex.lock();
				read_queue.append(data);
				read_mutex.unlock();
			}
			//}		
		}
	}
}
