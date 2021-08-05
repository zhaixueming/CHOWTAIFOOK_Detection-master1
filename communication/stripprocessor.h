#ifndef STRIPPROECSSOR_H
#define STRIPPROECSSOR_H

#include <QThread>
#include <QThreadPool>
#include <mutex>
#include <queue>

class StripProcessor : public QThread
{
	Q_OBJECT
public:
	static StripProcessor& getInstance();
	bool startLoop();
	bool stopLoop();

	virtual ~StripProcessor();
	StripProcessor();

protected:
	void run() override;

private:
	//创建线程池
	bool createThreadPool();
	bool destroyThreadPool();

	//
    void handleStrip(bool front_first);

	static std::mutex m_strip_list_mutex;
	std::condition_variable m_strip_list_cv;
	QThreadPool m_threadpool;

	bool m_running = false;
	std::mutex m_runing_mutex;
	std::condition_variable m_runing_cv;

};

#endif // STRIPPROECSSOR_H
