#include "serialcommond.h"

namespace vimo::display
{
	SerialCommond &SerialCommond::getInstance()
	{
		static SerialCommond light_serial;
		return light_serial;
	}

	// initialize port communication
	SerialCommond::SerialCommond()
	{
		SerialF1 = new QSerialPort;
		bool initf1 = SerialInit(SerialF1, "COM26");
		if (!initf1)
		{
			binit = false;
			MessageDialog message_box_dialog(DialogType::errorDialog, QObject::tr("串口26初始化失败!"));
			message_box_dialog.exec();
		}
		else
			qDebug() << "COM26";

		SerialF2 = new QSerialPort;
		bool initf2 = SerialInit(SerialF2, "COM27");
		if (!initf2)
		{
			binit = false;
			MessageDialog message_box_dialog(DialogType::errorDialog, QObject::tr("串口27初始化失败!"));
			message_box_dialog.exec();
		}
		else
			qDebug() << "COM27";

		SerialF3 = new QSerialPort;
		bool initf3 = SerialInit(SerialF3, "COM28");
		if (!initf3)
		{
			binit = false;
			MessageDialog message_box_dialog(DialogType::errorDialog, QObject::tr("串口28初始化失败!"));
			message_box_dialog.exec();
		}
		else
			qDebug() << "COM28";

		SerialF4 = new QSerialPort;
		bool initf4 = SerialInit(SerialF4, "COM29");
		if (!initf4)
		{
			binit = false;
			MessageDialog message_box_dialog(DialogType::errorDialog, QObject::tr("串口29初始化失败!"));
			message_box_dialog.exec();
		}
		else
			qDebug() << "COM29";

		SerialF5 = new QSerialPort;
		bool initf5 = SerialInit(SerialF5, "COM30");
		if (!initf5)
		{
			binit = false;
			MessageDialog message_box_dialog(DialogType::errorDialog, QObject::tr("串口30初始化失败!"));
			message_box_dialog.exec();
		}
		else
			qDebug() << "COM30";

		SerialB1 = new QSerialPort;
		bool initb1 = SerialInit(SerialB1, "COM21");
		if (!initb1)
		{
			binit = false;
			MessageDialog message_box_dialog(DialogType::errorDialog, QObject::tr("串口21初始化失败!"));
			message_box_dialog.exec();
		}
		else
			qDebug() << "COM21";

		SerialB2 = new QSerialPort;
		bool initb2 = SerialInit(SerialB2, "COM22");
		if (!initb2)
		{
			binit = false;
			MessageDialog message_box_dialog(DialogType::errorDialog, QObject::tr("串口22初始化失败!"));
			message_box_dialog.exec();
		}
		else
			qDebug() << "COM22";

		SerialB3 = new QSerialPort;
		bool initb3 = SerialInit(SerialB3, "COM23");
		if (!initb3)
		{
			binit = false;
			MessageDialog message_box_dialog(DialogType::errorDialog, QObject::tr("串口23初始化失败!"));
			message_box_dialog.exec();
		}
		else
			qDebug() << "COM23";

		SerialB4 = new QSerialPort;
		bool initb4 = SerialInit(SerialB4, "COM24");
		if (!initb4)
		{
			binit = false;
			MessageDialog message_box_dialog(DialogType::errorDialog, QObject::tr("串口24初始化失败!"));
			message_box_dialog.exec();
		}
		else
			qDebug() << "COM24";

		SerialB5 = new QSerialPort;
		bool initb5 = SerialInit(SerialB5, "COM25");
		if (!initb5)
		{
			binit = false;
			MessageDialog message_box_dialog(DialogType::errorDialog, QObject::tr("串口25初始化失败!"));
			message_box_dialog.exec();
		}
		else
			qDebug() << "COM25";
	}

	SerialCommond::~SerialCommond()
	{
		SerialF1->clear();
		SerialF1->close();
		SerialF1->deleteLater();
		SerialF2->clear();
		SerialF2->close();
		SerialF2->deleteLater();
		SerialF3->clear();
		SerialF3->close();
		SerialF3->deleteLater();
		SerialF4->clear();
		SerialF4->close();
		SerialF4->deleteLater();
		SerialF5->clear();
		SerialF5->close();
		SerialF5->deleteLater();

		SerialB1->clear();
		SerialB1->close();
		SerialB1->deleteLater();
		SerialB2->clear();
		SerialB2->close();
		SerialB2->deleteLater();
		SerialB3->clear();
		SerialB3->close();
		SerialB3->deleteLater();
		SerialB4->clear();
		SerialB4->close();
		SerialB4->deleteLater();
		SerialB5->clear();
		SerialB5->close();
		SerialB5->deleteLater();
	}

	bool SerialCommond::SerialInit(QSerialPort *Serial, QString Com)
	{
		Serial->setPortName(Com);
		Serial->setBaudRate(QSerialPort::Baud9600);
		Serial->setDataBits(QSerialPort::Data8);
		Serial->setParity(QSerialPort::NoParity);
		Serial->setStopBits(QSerialPort::OneStop);
		Serial->setFlowControl(QSerialPort::NoFlowControl);

		bool ret = Serial->open(QIODevice::ReadWrite);
		if (!ret)
		{
			return false;
			qDebug() << Com + " serial init failed";
		}
		else
		{
			return true;
			qDebug() << Com + " serial init success";
		}
	}

	/*
	* Update: Update the brightness setting of the light source controller
	* Input:
	*      n_light: number of lights port on the light source controller
	*      Brightness: array of brightness value for each light port, 0~255 for valid brightness number and -1 for disable
	*/

	// Construct the command, for the detail of the command structure please refer to the hardware handbook
	bool SerialCommond::Lightleftfront(int Bright1, int Bright2, int Bright3, int Bright4, int Bright5)
	{
		bool result = false;
		QThread::msleep(100);
		result = SerialCommand(SerialF2, 1, Bright1);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialF2, 2, Bright2);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialF4, 1, Bright3);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialF4, 2, Bright4);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialF1, 1, Bright5);
		if (!result)
			return false;

		return true;
	}

	bool SerialCommond::Lightleftcontrary(int Bright1, int Bright2, int Bright3, int Bright4, int Bright5)
	{
		bool result = false;
		QThread::msleep(100);
		result = SerialCommand(SerialB2, 1, Bright1);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialB1, 1, Bright2);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialB3, 2, Bright3);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialB3, 1, Bright4);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialB1, 2, Bright5);
		if (!result)
			return false;

		return true;
	}

	bool SerialCommond::Lightrightfront(int Bright1, int Bright2, int Bright3, int Bright4, int Bright5)
	{
		bool result = false;
		QThread::msleep(100);
		result = SerialCommand(SerialF3, 1, Bright1);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialF3, 2, Bright2);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialF5, 1, Bright3);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialF5, 2, Bright4);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialF1, 2, Bright5);
		if (!result)
			return false;

		return true;
	}

	bool SerialCommond::Lightrightcontrary(int Bright1, int Bright2, int Bright3, int Bright4, int Bright5)
	{
		bool result = false;
		QThread::msleep(100);
		result = SerialCommand(SerialB2, 2, Bright1);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialB5, 1, Bright2);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialB4, 1, Bright3);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialB4, 2, Bright4);
		if (!result)
			return false;
		QThread::msleep(100);
		result = SerialCommand(SerialB5, 2, Bright5);
		if (!result)
			return false;

		return true;
	}

	bool SerialCommond::SerialCommand(QSerialPort *Serial, int channel, int bright)
	{
		try
		{
			int head = 36;
			int com = 51;
			int channelControl = channel + 48;
			QString qnum = QString::number(bright, 16).right(4);

			int b1 = 48;
			int b2 = 0;
			int b3 = 0;
			if (bright / 16 >= 0 && bright / 16 <= 9)
				b2 = bright / 16 + 48;
			else
				b2 = bright / 16 + 55;
			if (bright % 16 >= 0 && bright % 16 <= 9)
				b3 = bright % 16 + 48;
			else
				b3 = bright % 16 + 55;

			int Control = (head ^ com ^ channelControl ^ b1 ^ b2 ^ b3);

			QString str1 = QString::number(Control / 16, 16);
			QString str2 = QString::number(Control % 16, 16);

			QString brightstring = qnum;
			int l = qnum.count();
			for (int i = 0; i < 3 - l; i++)
				brightstring = "0" + brightstring;

			QString stringmid0 = brightstring.mid(0, 1);
			QString stringmid1 = brightstring.mid(1, 1);
			QString stringmid2 = brightstring.mid(2, 1);

			if (stringmid1 == "a")
				stringmid1 = "A";
			else if (stringmid1 == "b")
				stringmid1 = "B";
			else if (stringmid1 == "c")
				stringmid1 = "C";
			else if (stringmid1 == "d")
				stringmid1 = "D";
			else if (stringmid1 == "e")
				stringmid1 = "E";
			else if (stringmid1 == "f")
				stringmid1 = "F";

			if (stringmid2 == "a")
				stringmid2 = "A";
			else if (stringmid2 == "b")
				stringmid2 = "B";
			else if (stringmid2 == "c")
				stringmid2 = "C";
			else if (stringmid2 == "d")
				stringmid2 = "D";
			else if (stringmid2 == "e")
				stringmid2 = "E";
			else if (stringmid2 == "f")
				stringmid2 = "F";

			QString BrightSend = stringmid0 + stringmid1 + stringmid2;

			QString command = "$3" + QString::number(channel) + BrightSend + str1 + str2;
			//qDebug() << command;
			//QThread::msleep(50);
			Serial->write(command.toLatin1());
			Serial->waitForBytesWritten();
			//char response[100] = { 0 };
			//Serial->waitForReadyRead();
			return true;
		}
		catch (...)
		{
			return false;
		}

		//Serial->read(response, 100);
	}

	//初始化读码器
	bool SerialCommond::InitHoneyWell()
	{
		uartRecOvertimeCount = 0.2; //起始等待时间0.2S
		rec_buf_len = 0;
		
		//设置uart接收缓冲超时定时器
		uartRecDataTimer = new QTimer();
		uartRecDataTimer->stop();
		uartRecDataTimer->setInterval(uartRecOvertimeCount * 1000);                     //设置定时周期，单位：毫秒
		uartRecDataTimer->setSingleShot(true);                                        //设置为单次触发
		QObject::connect(uartRecDataTimer, &QTimer::timeout, this, &SerialCommond::uartRec_timeout);     //设置槽

		SerialHoneywell->setPortName("COM20");
		SerialHoneywell->setBaudRate(QSerialPort::Baud9600);
		SerialHoneywell->setDataBits(QSerialPort::Data8);
		SerialHoneywell->setParity(QSerialPort::NoParity);
		SerialHoneywell->setStopBits(QSerialPort::OneStop);
		SerialHoneywell->setFlowControl(QSerialPort::NoFlowControl);

		bool ret = SerialHoneywell->open(QIODevice::ReadWrite);
		if (!ret)
		{
			binit = false;
			qDebug() << "Serial Honeywell init failed";
		}
		else
		{
			qDebug() << "Serial Honeywell init success";
		}

		QObject::connect(SerialHoneywell, &QSerialPort::readyRead, this, &SerialCommond::ReadHoneyWell);
		return ret;
	}

	//收取读码器消息
	void SerialCommond::ReadHoneyWell()
	{
		qint32 rec_buf_len;
		//串口可读数据长度
		int byteLen = SerialHoneywell->bytesAvailable();
		if (byteLen <= 0)
			return;

		rec_buf_len += byteLen;
		uart_rec_ss.append(SerialHoneywell->readAll());  //读取数据
		emit this->honeywellstring(uart_rec_ss);
		qDebug() << uart_rec_ss;

		//定时器开始工作、定时器重启
		uartRecDataTimer->start();		
	}

	//定时器触发打印串口数据
	void SerialCommond::uartRec_timeout()
	{
		if (!uart_rec_ss.isEmpty())
		{			
			uart_rec_ss.clear();			
			uartRecDataTimer->start();
		}
	}
}
