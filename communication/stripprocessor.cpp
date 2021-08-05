#include "stripprocessor.h"
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QImage>
#include <fstream>

using namespace std::chrono_literals;
static const int THREAD_NUM = 20;

std::mutex StripProcessor::m_strip_list_mutex;

StripProcessor::StripProcessor()
{
	
}

StripProcessor::~StripProcessor()
{
}

StripProcessor& StripProcessor::getInstance()
{
	static StripProcessor processor;
	return processor;
}

//创建线程池
bool StripProcessor::createThreadPool()
{
	m_threadpool.setMaxThreadCount(THREAD_NUM);
	class StripUploadTask : public QRunnable
	{
	public:
		StripUploadTask(bool i) : m_order(i) {}
		void run() override
		{
			StripProcessor::getInstance().handleStrip(m_order);
		}
	private:
		bool m_order;
	};
	m_running = true;
	for (int i = 0; i < THREAD_NUM; ++i)
	{
		// auto delete
		StripUploadTask *task = new StripUploadTask(i % 2 == 0);
		m_threadpool.start(task);
	}
	return true;
}

//销毁线程池
bool StripProcessor::destroyThreadPool()
{
	m_threadpool.waitForDone();
	m_threadpool.clear();
	return true;
}

bool StripProcessor::startLoop()
{
	qDebug() << __FILE__ << ":" << __func__ << "+";
	
	m_running = true;
	if (!this->isRunning())
	{
		destroyThreadPool();
		createThreadPool();
		this->start();
	}

	qDebug() << __FILE__ << ":" << __func__ << "-";
	return true;
}

bool StripProcessor::stopLoop()
{
	qDebug() << __FILE__ << ":" << __func__ << "+";
	m_running = false;
	m_runing_cv.notify_all();
	m_strip_list_cv.notify_all();

	// 等待线程池销毁
	destroyThreadPool();

	this->wait();
	this->quit();

	qDebug() << __FILE__ << ":" << __func__ << "-";
	return true;
}

void StripProcessor::run()
{
	qDebug() << __FILE__ << ":" << __func__ << "+";
	while (m_running)
	{
		// 上传生产图片间隔
		{
			std::unique_lock<std::mutex> lk(m_runing_mutex);
			m_runing_cv.wait_for(lk, 5s);
			if (!m_running)
			{
				continue;
			}
		}		
	}
	qDebug() << __FILE__ << ":" << __func__ << "-";
}

void StripProcessor::handleStrip(bool front_first)
{
	// 预分配内存
	unsigned long jpegSize = 16384 * 42000 * 2; // bytes
	unsigned char *jpegBuf = (unsigned char *)malloc(jpegSize);
	if (jpegBuf == nullptr)
	{
		qCritical() << "Malloc Mem failed: size=" << jpegSize;
		return;
	}

	
	while (m_running)
	{
		// 上传生产图片间隔
		{
			std::unique_lock<std::mutex> lk(m_strip_list_mutex);
			m_strip_list_cv.wait_for(lk, 60s);
			if (!m_running)
			{
				continue;
			}
		}

		// 处理未上传的信息
		while (!true)
		{
			
		}
	}

	free(jpegBuf);
	jpegBuf = nullptr;
}
