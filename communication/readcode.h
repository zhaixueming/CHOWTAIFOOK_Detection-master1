#ifndef READCODE_H
#define READCODE_H

#include <QThread>
#include <QtNetwork/QTcpSocket>
#include <QCoreApplication>
#include <QQueue>
#include <QMutex>
#include <QDateTime>
#include <condition_variable> // std::condition_variable
#include "serializer/Config.h"
#include "uiframe/configuiset/configdialog.h"
#include "uiframe/commonuiset/messagedialog/messagedialog.h"

namespace vimo::display
{
	class LeftReadl : public QThread
	{
		Q_OBJECT
	public:
		static LeftReadl &getInstance();
		LeftReadl();
		~LeftReadl();
		
		//初始化是否成功
		bool binitl = false;
		//是否开始读码
		bool bcodestart = false;
		//队列
		QQueue<int> Queuestart;
		QMutex Mutexstart;
	signals:
		void honeywellcodell(QString lcode);
		void honeywellinitll(QString linit);
	protected:
		void run();

	private:		
		bool send(QString write);
		
		ConfigDialog *config_set{ nullptr };	
		SystemParam _systemparam;
		QTcpSocket* socket_LcodeL;
		
	private slots:
		void ReadMessage();
	};

	class LeftReadr : public QThread
	{
		Q_OBJECT
	public:
		static LeftReadr &getInstance();
		LeftReadr();
		~LeftReadr();
		//初始化是否成功		
		bool binitr = false;
		//是否开始读码
		bool bcodestart = false;
		//队列
		QQueue<bool> Queuestart;
		QMutex Mutexstart;
	signals:
		void honeywellcodelr(QString lcode);
		void honeywellinitlr(QString linit);

	protected:
		void run();

	private:
		bool send(QString write);

		ConfigDialog *config_set{ nullptr };
		SystemParam _systemparam;
		QTcpSocket* socket_LcodeR;

	private slots:
		void ReadMessage();
	};

	class RightReadl : public QThread
	{
		Q_OBJECT
	public:
		static RightReadl &getInstance();
		RightReadl();
		~RightReadl();
		
		//初始化是否成功
		bool binitl = false;
		//是否开始读码
		bool bcodestart = false;
		//队列
		QQueue<bool> Queuestart;
		QMutex Mutexstart;
	signals:
		void honeywellcoderl(QString rcode);
		void honeywellinitrl(QString rinit);

	protected:
		void run();

	private:
		bool send(QString write);

		ConfigDialog *config_set{ nullptr };
		SystemParam _systemparam;

		QTcpSocket* socket_RcodeL;
		
	private slots:
		void ReadMessage();
	};

	class RightReadr : public QThread
	{
		Q_OBJECT
	public:
		static RightReadr &getInstance();
		RightReadr();
		~RightReadr();

		//初始化是否成功
		bool binitr = false;
		//是否开始读码
		bool bcodestart = false;
		//队列
		QQueue<bool> Queuestart;
		QMutex Mutexstart;
	signals:
		void honeywellcoderr(QString rcode);
		void honeywellinitrr(QString rinit);

	protected:
		void run();

	private:
		bool send(QString write);

		ConfigDialog *config_set{ nullptr };
		SystemParam _systemparam;

		QTcpSocket* socket_RcodeR;

	private slots:
		void ReadMessage();
	};
}


#endif // PLCHELPER_H
