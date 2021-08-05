#ifndef MCPLC_H
#define MCPLC_H

#include <QThread>
#include <QtNetwork/QTcpSocket>
#include <QCoreApplication>
#include <QQueue>
#include <QMutex>
#include <condition_variable> // std::condition_variable
#include "communication/readcode.h"
#include "serializer/Config.h"
#include "uiframe/configuiset/configdialog.h"
#include "uiframe/commonuiset/messagedialog/messagedialog.h"

namespace vimo::display
{
	class MCPLC : public QThread
	{
		Q_OBJECT
	public:
		static MCPLC &getInstance();
		MCPLC();
		~MCPLC();
		void startLoop();
		void stopLoop();

		bool sendReadbool(QString address);
		bool sendWritebool(QString address, bool data);
		int sendReadint16(QString address);
		bool sendWriteint16(QString address, int data);
		QString sendReadstring(QString address, int num);
		bool sendWritestring(QString address, QString data);

		struct Plcbool
		{
			QString address; 
			bool data;
		};

		struct Plcint
		{
			QString address;
			int data;
		};

		struct Plcstring
		{
			QString address;
			QString data;
			int num;
		};

		QQueue<Plcbool> sendboolwrite_queue;
		QMutex sendboolwrite_mutex;
		QQueue<QString> sendboolRead_queue;
		QMutex sendboolRead_mutex;
		
		QQueue<Plcint> sendintwrite_queue;
		QMutex sendintwrite_mutex;
		QQueue<QString> sendintRead_queue;
		QMutex sendintRead_mutex;
		
		QQueue<Plcstring> sendstringwrite_queue;
		QMutex sendstringwrite_mutex;
		QQueue<Plcstring> sendstringRead_queue;
		QMutex sendstringRead_mutex;
		
		QQueue<QString> read_queue;
		QMutex read_mutex;
		//plc初始化是否成功
		bool binit = false;
	protected:
		void run();

	private:
		QString asciiinttostring(int asciiint);
		int asciiinttostring(QString asciistring);

		bool sendRead(QString addressnum, QString chunk);
		bool sendWrite(QString addressnum, QString chunk, QString str);

		ConfigDialog *config_set{ nullptr };	
		SystemParam _systemparam;

		bool m_running = false;

		QTcpSocket* m_socket_device;
		
	signals:
		void plcinit(QString init);
		
		void plcreturnstringl(QString _string);
		void plcreturnstringr(QString _string);
	private slots:
		void ReadMessage();
	};
}


#endif // PLCHELPER_H
