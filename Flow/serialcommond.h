#ifndef SERIALCOMMOND_H
#define SERIALCOMMOND_H

#include <QDebug>
#include <QObject>  
#include <QDateTime>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QElapsedTimer>
#include <QThread>
#include "uiframe/commonuiset/messagedialog/messagedialog.h"

namespace vimo::display
{
	class SerialCommond : public QObject
	{
		Q_OBJECT
	public:
		static SerialCommond &getInstance();
		SerialCommond();
		~SerialCommond();

		QSerialPort *SerialHoneywell = new QSerialPort;

		//左工位的控制光源串口
		QSerialPort *SerialF1 = nullptr;
		QSerialPort *SerialF2 = nullptr;
		QSerialPort *SerialF3 = nullptr;
		QSerialPort *SerialF4 = nullptr;
		QSerialPort *SerialF5 = nullptr;
		//右工位的控制光源串口
		QSerialPort *SerialB1 = nullptr;
		QSerialPort *SerialB2 = nullptr;
		QSerialPort *SerialB3 = nullptr;
		QSerialPort *SerialB4 = nullptr;
		QSerialPort *SerialB5 = nullptr;
		//初始化是否成功
		bool binit = true;
	public slots:
		//控制左前工位光源
		bool Lightleftfront(int Bright1, int Bright2, int Bright3, int Bright4, int Bright5);
		//控制左后工位光源
		bool Lightleftcontrary(int Bright1, int Bright2, int Bright3, int Bright4, int Bright5);
		//控制右前工位光源
		bool Lightrightfront(int Bright1, int Bright2, int Bright3, int Bright4, int Bright5);
		//控制右口工位光源
		bool Lightrightcontrary(int Bright1, int Bright2, int Bright3, int Bright4, int Bright5);
		//初始化读码器
		bool InitHoneyWell();
		//收取读码器消息
		void ReadHoneyWell();

		void uartRec_timeout();      //定时溢出处理槽函数

		//void SysStateDeal();
	private:
		bool SerialInit(QSerialPort *Serial, QString Com);

		bool SerialCommand(QSerialPort *Serial, int channel, int bright);

	private:
		qint32 rec_buf_len;             //接收累计长度		
		QTimer * uartRecDataTimer;      //串口接收定时器
		qreal uartRecOvertimeCount;     //串口接收超时计数
		QByteArray uart_rec_ss;         //串口接收数据

	signals:
		void honeywellstring(QString honeywellorder);
		
	};
}
#endif // LIGHTSOURCECOMM_H
