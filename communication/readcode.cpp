#include <QThread>
#include <thread>
#include <QDebug>
#include "readcode.h"

namespace vimo::display
{
	LeftReadl &LeftReadl::getInstance()
	{
		static LeftReadl _leftl;
		return _leftl;
	}

	LeftReadl::LeftReadl()
	{
		
	}

	LeftReadl::~LeftReadl()
	{
		
	}

	void LeftReadl::run()
	{
		std::string sysparamDir = QCoreApplication::applicationDirPath().toStdString() + "\\SysParamConfig.json";
		_systemparam = config_set->GetSystemParamFromFile(sysparamDir);

		socket_LcodeL = new QTcpSocket();
		connect(socket_LcodeL, SIGNAL(readyRead()), this, SLOT(ReadMessage()), Qt::DirectConnection);

		socket_LcodeL->connectToHost(QString::fromStdString(_systemparam.honeywelipl1), std::stoi(_systemparam.honeywelportl1));
		if (socket_LcodeL->waitForConnected(1000))
		{
			binitl = true;
			emit this->honeywellinitll("honeywell left 1 init success");
			qDebug() << "socket_LcodeL true";
		}
		else
		{
			binitl = false;
			qDebug() << "socket_LcodeL false";
			emit this->honeywellinitll("honeywell left 1 init failed");
		}

		while (binitl)
		{
			msleep(30);
			if (Queuestart.size() > 0)
			{
				Mutexstart.lock();
				int boolstart = Queuestart.front();
				Queuestart.pop_front();
				Mutexstart.unlock();	

				if (boolstart == 1)
				{				
					if (!bcodestart)
					{
						qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss:zzz") + "--LLCodestart" << endl;
						send("T");
						bcodestart = true;
					}
				}
				else
				{
					if (bcodestart)
					{
						qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss:zzz") + "--LLCodeend" << endl;
						send("P");
						bcodestart = false;
					}
				}
			}
		}
	}

	bool LeftReadl::send(QString write)
	{
		QByteArray bytes = write.toLatin1();
		socket_LcodeL->write(bytes);
		bool socketbool = socket_LcodeL->waitForBytesWritten(1000);
		socket_LcodeL->flush();
		socket_LcodeL->waitForReadyRead(5000);
		return socketbool;
	}

	void LeftReadl::ReadMessage()
	{
		if (socket_LcodeL->state() == QAbstractSocket::ConnectedState)
		{
			QByteArray bytearrayl = socket_LcodeL->readAll();
			if (bytearrayl.size() > 0)
			{				
				QString data = bytearrayl;
				emit this->honeywellcodell(data);
			}			
		}		
	}


	LeftReadr &LeftReadr::getInstance()
	{
		static LeftReadr _leftr;
		return _leftr;
	}

	LeftReadr::LeftReadr()
	{

	}

	LeftReadr::~LeftReadr()
	{
		
	}

	void LeftReadr::run()
	{
		std::string sysparamDir = QCoreApplication::applicationDirPath().toStdString() + "\\SysParamConfig.json";
		_systemparam = config_set->GetSystemParamFromFile(sysparamDir);

		socket_LcodeR = new QTcpSocket();
		connect(socket_LcodeR, SIGNAL(readyRead()), this, SLOT(ReadMessage()), Qt::DirectConnection);

		socket_LcodeR->connectToHost(QString::fromStdString(_systemparam.honeywelipl2), std::stoi(_systemparam.honeywelportl2));
		if (socket_LcodeR->waitForConnected(1000))
		{
			binitr = true;
			qDebug() << "socket_LcodeR true";
			emit this->honeywellinitlr("honeywell left 2 init success");
		}
		else
		{
			binitr = false;
			qDebug() << "socket_LcodeR false";
			emit this->honeywellinitlr("honeywell left 2 init failed");
		}

		while (binitr)
		{
			msleep(30);
			if (Queuestart.size() > 0)
			{
				Mutexstart.lock();
				int  boolstart = Queuestart.front();
				Queuestart.pop_front();
				Mutexstart.unlock();

				if (boolstart == 1)
				{
					if (!bcodestart)
					{
						qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss:zzz") + "--LRCodestart" << endl;
						send("T");
						bcodestart = true;
					}
				}
				else
				{
					if (bcodestart)
					{						
						qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss:zzz") + "--LRCodeend" << endl;
						send("P");
						bcodestart = false;
					}
				}
			}
		}
	}

	bool LeftReadr::send(QString write)
	{
		QByteArray bytes = write.toLatin1();
		socket_LcodeR->write(bytes);
		bool socketbool = socket_LcodeR->waitForBytesWritten(1000);
		socket_LcodeR->flush();
		socket_LcodeR->waitForReadyRead(5000);
		return socketbool;
	}

	void LeftReadr::ReadMessage()
	{		
		if (socket_LcodeR->state() == QAbstractSocket::ConnectedState)
		{
			QByteArray bytearrayr = socket_LcodeR->readAll();
			if (bytearrayr.size() > 0)
			{
				QString data = bytearrayr;
				emit this->honeywellcodelr(data);
			}
		}
	}


	RightReadl &RightReadl::getInstance()
	{
		static RightReadl _rightl;
		return _rightl;
	}

	RightReadl::RightReadl()
	{
		
	}

	RightReadl::~RightReadl()
	{
		
	}

	void RightReadl::run()
	{
		std::string sysparamDir = QCoreApplication::applicationDirPath().toStdString() + "\\SysParamConfig.json";
		_systemparam = config_set->GetSystemParamFromFile(sysparamDir);

		socket_RcodeL = new QTcpSocket();
		connect(socket_RcodeL, SIGNAL(readyRead()), this, SLOT(ReadMessage()), Qt::DirectConnection);
		socket_RcodeL->connectToHost(QString::fromStdString(_systemparam.honeywelipr1), std::stoi(_systemparam.honeywelportr1));
		if (socket_RcodeL->waitForConnected(1000))
		{
			binitl = true;
			qDebug() << "socket_RcodeL true";
			emit this->honeywellinitrl("honeywell right 1 init success");
		}
		else
		{
			binitl = false;
			qDebug() << "socket_RcodeL false";
			emit this->honeywellinitrl("honeywell right 1 init failed");
		}

		while (binitl)
		{
			msleep(30);
			if (Queuestart.size() > 0)
			{
				Mutexstart.lock();
				int boolstart = Queuestart.front();
				Queuestart.pop_front();
				Mutexstart.unlock();

				if (boolstart == 1)
				{
					if (!bcodestart)
					{
						qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss:zzz") + "--RLCodestart" << endl;
						send("T");
						bcodestart = true;
					}
				}
				else
				{
					if (bcodestart)
					{
						qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss:zzz") + "--RLCodeend" << endl;
						send("P");
						bcodestart = false;
					}
				}
			}
		}
	}

	bool RightReadl::send(QString write)
	{
		QByteArray bytes = write.toLatin1();
		socket_RcodeL->write(bytes);
		bool socketbool = socket_RcodeL->waitForBytesWritten(1000);
		socket_RcodeL->flush();
		socket_RcodeL->waitForReadyRead(5000);
		return socketbool;
	}

	void RightReadl::ReadMessage()
	{
		if (socket_RcodeL->state() == QAbstractSocket::ConnectedState)
		{
			QByteArray bytearrayl = socket_RcodeL->readAll();
			if (bytearrayl.size() > 0)
			{				
				QString data = bytearrayl;
				emit this->honeywellcoderl(data);
			}
			
		}
	}


	RightReadr &RightReadr::getInstance()
	{
		static RightReadr _rightr;
		return _rightr;
	}

	RightReadr::RightReadr()
	{

	}

	RightReadr::~RightReadr()
	{
		
	}

	void RightReadr::run()
	{
		std::string sysparamDir = QCoreApplication::applicationDirPath().toStdString() + "\\SysParamConfig.json";
		_systemparam = config_set->GetSystemParamFromFile(sysparamDir);

		socket_RcodeR = new QTcpSocket();
		connect(socket_RcodeR, SIGNAL(readyRead()), this, SLOT(ReadMessage()), Qt::DirectConnection);
		socket_RcodeR->connectToHost(QString::fromStdString(_systemparam.honeywelipr2), std::stoi(_systemparam.honeywelportr2));
		if (socket_RcodeR->waitForConnected(1000))
		{
			binitr = true;
			qDebug() << "socket_RcodeR true";
			emit this->honeywellinitrr("honeywell right 2 init success");
		}
		else
		{
			binitr = false;
			qDebug() << "socket_RcodeR false";
			emit this->honeywellinitrr("honeywell right 2 init failed");
		}

		while (binitr)
		{
			msleep(30);
			if (Queuestart.size() > 0)
			{
				Mutexstart.lock();
				int boolstart = Queuestart.front();
				Queuestart.pop_front();
				Mutexstart.unlock();

				if (boolstart == 1)
				{
					if (!bcodestart)
					{
						qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss:zzz") + "--RRCodestart" << endl;
						send("T");
						bcodestart = true;
					}
				}
				else
				{
					if (bcodestart)
					{
						qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss:zzz") + "--RRCodeend" << endl;
						send("P");
						bcodestart = false;
					}
				}
			}
		}
	}

	bool RightReadr::send(QString write)
	{
		QByteArray bytes = write.toLatin1();
		socket_RcodeR->write(bytes);
		bool socketbool = socket_RcodeR->waitForBytesWritten(1000);
		socket_RcodeR->flush();
		socket_RcodeR->waitForReadyRead(5000);
		return socketbool;
	}

	void RightReadr::ReadMessage()
	{		
		if (socket_RcodeR->state() == QAbstractSocket::ConnectedState)
		{
			QByteArray bytearrayr = socket_RcodeR->readAll();
			if (bytearrayr.size() > 0)
			{
				QString data = bytearrayr;
				emit this->honeywellcoderr(data);
			}
		}
	}
}
