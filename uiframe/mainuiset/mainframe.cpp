/****************************************************************************
 *  @file     mainframe.cpp
 *  @brief    界面主显示框类
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "mainframe.h"
#include "vimocommon/vimocommon.h"

#include "logwidget.h"
#include "titlebarwidget.h"
#include "ui_mainframe.h"
#include <QMessageBox>
#include <QtDebug>

 //海康回调
void __stdcall ImageCallBackL(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
{
	if (pFrameInfo)
	{
		vimo::display::HikvisionSDK *camPtr = (vimo::display::HikvisionSDK *)pUser;			
		Mat GetImage = Mat(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC1, pData);		
		camPtr->emitSignall(GetImage);
	}
}
void __stdcall ImageCallBackML(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
{
	if (pFrameInfo)
	{
		vimo::display::HikvisionSDK *camPtr = (vimo::display::HikvisionSDK *)pUser;
		Mat GetImage = Mat(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC1, pData);
		camPtr->emitSignalml(GetImage);
	}
}
void __stdcall ImageCallBackMR(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
{
	if (pFrameInfo)
	{
		vimo::display::HikvisionSDK *camPtr = (vimo::display::HikvisionSDK *)pUser;
		Mat GetImage = Mat(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC1, pData);
		camPtr->emitSignalmr(GetImage);
	}
}
void __stdcall ImageCallBackR(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
{
	if (pFrameInfo)
	{
		vimo::display::HikvisionSDK *camPtr = (vimo::display::HikvisionSDK *)pUser;
		Mat GetImage = Mat(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC1, pData);
		camPtr->emitSignalr(GetImage);
	}
}

namespace vimo::display
{
	MainFrame::MainFrame(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainFrame)
	{
		//初始化
		init();
		//登录
		//load();
	}

	MainFrame::~MainFrame()
	{
		bclose = false;
		delete ui;
		
		try
		{		
			if (LImageListener.joinable())
				LImageListener.join();
			if (MLImageListener.joinable())
				MLImageListener.join();
			if (MRImageListener.joinable())
				MRImageListener.join();
			if (RImageListener.joinable())
				RImageListener.join();			
		}
		catch (const std::exception&)
		{
		}

		try
		{
			qDebug() << "MCPLC::getInstance().stopLoop()";
			MCPLC::getInstance().binit = false;
			MCPLC::getInstance().stopLoop();
			qDebug() << "Read::getInstance().stopLoop()";
			LeftReadl::getInstance().binitl = false;
			LeftReadl::getInstance().wait();
			LeftReadl::getInstance().quit();
			LeftReadr::getInstance().binitr = false;
			LeftReadr::getInstance().wait();
			LeftReadr::getInstance().quit();
			RightReadl::getInstance().binitl = false;
			RightReadl::getInstance().wait();
			RightReadl::getInstance().quit();
			RightReadr::getInstance().binitr = false;
			RightReadr::getInstance().wait();
			RightReadr::getInstance().quit();
		}
		catch (const std::exception&)
		{
		}

		try
		{
			qDebug() << "StripProcessor::getInstance().stopLoop()";
			StripProcessor::getInstance().stopLoop();
		}
		catch (const std::exception&)
		{
		}
	}

	//初始化
	void MainFrame::init()
	{
		//初始化界面
		initWidgets();
		//初始化界面信号槽
		initConnects();

		//初始化配置
		initconfig();
		emit this->progresssignals(1);
		//初始化PLC
		initPlc();
		emit this->progresssignals(30);
		//初始化Hik相机
		initHik();
		emit this->progresssignals(80);		
		//线程初始化
		initthread();		
		qRegisterMetaType<cv::Mat>("cv::Mat");
		qRegisterMetaType<cv::Mat>("cv::Mat&");
		qRegisterMetaType<QString>("QString");
		emit this->progresssignals(90);
		//显示信号槽
		ShowImage();		
		emit this->progresssignals(100);		
	}

	//登录
	void MainFrame::load()
	{
		m_button_widget->adminload();
	}

	//初始化配置
	void MainFrame::initconfig()
	{
		try
		{
			//读取plc、存图配置
			std::string systemparamDir = QCoreApplication::applicationDirPath().toStdString() + "/SysParamConfig.json";
			m_sys_param = m_config_set->GetSystemParamFromFile(systemparamDir);
			CamLFPath = QString::fromStdString(m_sys_param.LeftFront_Save_Dir);
			CamLBPath = QString::fromStdString(m_sys_param.LeftContrary_Save_Dir);
			CamRFPath = QString::fromStdString(m_sys_param.RightFront_Save_Dir);
			CamRBPath = QString::fromStdString(m_sys_param.RightContrary_Save_Dir);
			InfoLog("配置初始化成功！");
		}
		catch (...)
		{
			ErrorLog("配置初始化失败！");
			bstart = false;
		}
	}

	//初始化PLC
	void MainFrame::initPlc()
	{
		MCPLC::getInstance().startLoop();		
	}

	//初始化Hik相机
	void MainFrame::initHik()
	{
		m_hikcam_l = new HikvisionSDK("HikCameraL");
		m_hikcam_ml = new HikvisionSDK("HikCameraML");
		m_hikcam_mr = new HikvisionSDK("HikCameraMR");
		m_hikcam_r = new HikvisionSDK("HikCameraR");
		try
		{
			int resCode = 0;
			resCode = m_hikcam_l->connectCamera("m_sys_param.hik_frontleft_id");
			if (resCode == 0)
			{
				m_hikcam_l->setTriggerMode(1);
				m_hikcam_l->setTriggerSource(0);
				m_hikcam_l->RegisterImageCallBack(ImageCallBackL);
				m_hikcam_l->startCamera();
			}

			resCode = m_hikcam_ml->connectCamera("m_sys_param.hik_frontright_id");
			if (resCode == 0)
			{
				m_hikcam_ml->setTriggerMode(1);
				m_hikcam_ml->setTriggerSource(0);
				m_hikcam_ml->RegisterImageCallBack(ImageCallBackML);
				m_hikcam_ml->startCamera();
			}

			resCode = m_hikcam_mr->connectCamera("m_sys_param.hik_backleft_id");
			if (resCode == 0)
			{
				m_hikcam_mr->setTriggerMode(1);
				m_hikcam_mr->setTriggerSource(0);
				m_hikcam_mr->RegisterImageCallBack(ImageCallBackMR);
				m_hikcam_mr->startCamera();
			}

			resCode = m_hikcam_r->connectCamera("m_sys_param.hik_backright_id");
			if (resCode == 0)
			{
				m_hikcam_r->setTriggerMode(1);
				m_hikcam_r->setTriggerSource(0);
				m_hikcam_r->RegisterImageCallBack(ImageCallBackR);
				m_hikcam_r->startCamera();
			}
		}
		catch (...)
		{
			
		}
	}

	//线程初始化
	void MainFrame::initthread()
	{		
		std::thread CamLthread = std::thread(&MainFrame::ImageLThread, this);
		LImageListener.swap(CamLthread);
		std::thread CamMLthread = std::thread(&MainFrame::ImageMLThread, this);
		MLImageListener.swap(CamMLthread);
		std::thread CamMRthread = std::thread(&MainFrame::ImageMRThread, this);
		MRImageListener.swap(CamMRthread);
		std::thread CamRthread = std::thread(&MainFrame::ImageRThread, this);
		RImageListener.swap(CamRthread);
		InfoLog("线程初始化！");
	}

	//显示信号槽
	void MainFrame::ShowImage()
	{
		//显示链接
		QObject::connect(m_hikcam_l, &HikvisionSDK::imageshowsignall, this,
			[=](const cv::Mat &image)
		{
			if (bshowcam)
			{
				QImage showimage = vimo::common::matToQImage(image);
				//((EightViewsWidget *)this->m_view_frame)->updateImage3(showimage);
			}
		});
		QObject::connect(m_hikcam_ml, &HikvisionSDK::imageshowsignalml, this,
			[=](const cv::Mat &image)
		{
			if (bshowcam)
			{
				QImage showimage = vimo::common::matToQImage(image);
				//((FourViewsWidget *)this->m_view_frame)->updateImage1(showimage);
			}
		});

		QObject::connect(m_hikcam_mr, &HikvisionSDK::imageshowsignalmr, this,
			[=](const cv::Mat &image)
		{
			if (bshowcam)
			{
				QImage showimage = vimo::common::matToQImage(image);
				//((FourViewsWidget *)this->m_view_frame)->updateImage4(showimage);
			}
		});
		QObject::connect(m_hikcam_r, &HikvisionSDK::imageshowsignalr, this,
			[=](const cv::Mat &image)
		{
			if (bshowcam)
			{
				QImage showimage = vimo::common::matToQImage(image);
				//((FourViewsWidget *)this->m_view_frame)->updateImage2(showimage);
			}
		});
	}

	//清理队列
	void MainFrame::clearqueue()
	{		
		QueueImageL.clear();
		QueueImageML.clear();		
		QueueImageMR.clear();
		QueueImageR.clear();	
	}

	//相机设置
	bool MainFrame::CamControl()
	{
		
		return true;
	}

	//
	unsigned int __stdcall MainFrame::ImageLThread()
	{
		while (bclose)
		{
			try
			{
				if (QueueImageL.size() > 0)
				{
					InfoLog("LFSave");
					MutexImageL.lock();
					//获取dalsadown队列第一个图像
					cv::Mat Image = QueueImageL.front();
					QueueImageL.pop_front();
					MutexImageL.unlock();



				}
			}
			catch (...)
			{
				qDebug() << "--LFSave error" << endl;
			}
		}
		return 0;
	}

	//
	unsigned int __stdcall MainFrame::ImageMLThread()
	{
		while (bclose)
		{
			try
			{
				if (QueueImageML.size() > 0)
				{
					InfoLog("LBSave");
					MutexImageML.lock();
					//获取dalsadown队列第一个图像
					cv::Mat Image = QueueImageML.front();
					QueueImageML.pop_front();
					MutexImageML.unlock();
					
				}
			}
			catch (...)
			{
				qDebug() << "--LBSave error" << endl;
			}
		}
		return 0;
	}

	//
	unsigned int __stdcall MainFrame::ImageMRThread()
	{
		while (bclose)
		{
			try
			{
				if (QueueImageMR.size() > 0)
				{
					InfoLog("RFSave");
					MutexImageMR.lock();
					//获取dalsadown队列第一个图像
					cv::Mat Image = QueueImageMR.front();
					QueueImageMR.pop_front();
					MutexImageMR.unlock();
					
				}
			}
			catch (...)
			{
				qDebug() << "--RFSave error" << endl;
			}
		}
		return 0;
	}

	//
	unsigned int __stdcall MainFrame::ImageRThread()
	{
		while (bclose)
		{
			try
			{
				if (QueueImageR.size() > 0)
				{
					MutexImageR.lock();
					//获取dalsadown队列第一个图像
					cv::Mat Image = QueueImageR.front();
					QueueImageR.pop_front();
					MutexImageR.unlock();
					
				}
			}
			catch (...)
			{
				qDebug() << "--RBSave error" << endl;
			}
		}
		return 0;
	}

#pragma region 界面
	//界面初始化
	void MainFrame::initWidgets()
	{
		ui->setupUi(this);
		setWindowFlags(Qt::FramelessWindowHint);
		/*QDesktopWidget *deskdop = QApplication::desktop();
		move((deskdop->width() - this->width()) / 2, (deskdop->height() - this->height()) / 2);*/
		qRegisterMetaType<logservice::LogItem>("LogItem");

		m_titlebar_widget = new TitleBarWidget("思谋", "---", "", this);
		ui->titlebar_layout->addWidget(m_titlebar_widget);

		SingleViewWidget *m_single_view{ nullptr };
		

		m_button_widget = new ButtonWidget();
		m_info_widget = new InfoWidget();
		m_statistics_widget = new StatisticsWidget();
		m_result_widget = new ResultWidget();

		ui->buttonLayout->addWidget(m_button_widget);
		ui->infoLayout->addWidget(m_info_widget);
		ui->numLayout->addWidget(m_statistics_widget);
		ui->resultLayout->addWidget(m_result_widget);
		
		std::vector<ImageView::ViewInfo> info_listOcr;
		info_listOcr.push_back(ImageView::ViewInfo{ QUuid(), QString("1") });
		m_view_frame = new SingleViewWidget(info_listOcr);
		ui->OCRLayout->addWidget(m_view_frame);

		std::vector<ImageView::ViewInfo> info_liststereoscopic;
		info_liststereoscopic.push_back(ImageView::ViewInfo{ QUuid(), QString("1") });
		m_view_frame = new SingleViewWidget(info_liststereoscopic);
		ui->stereoscopiccamLayout->addWidget(m_view_frame);

		std::vector<ImageView::ViewInfo> info_list;
		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("1") });
		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("2") });
		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("3") });
		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("4") });
		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("5") });
		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("6") });		
		m_view_frame = new SixViewsWidget(info_list);
		ui->cam_layout->addWidget(m_view_frame);

		m_data_widget = new DataWidget(tr("RFID"));
		ui->dataLayout->addWidget(m_data_widget);

		m_log_widget = new LogWidget(tr("日志"));		
		ui->log_layout->addWidget(m_log_widget);
		
		logservice::Logger::getInstance();
	}

	//界面信号槽
	void MainFrame::initConnects()
	{
		//切换语言
		connect(m_titlebar_widget, SIGNAL(signalChangeLang()), this, SLOT(slotChangeLang()));
		//进度条
		connect(this, SIGNAL(progresssignals(int)), this, SLOT(progressslots(int)));
		//登录
		connect(m_button_widget, SIGNAL(adminsignal(int)), this, SLOT(loadslot(int)));
		//配方设置
		connect(m_button_widget, SIGNAL(formulasignal()), this, SLOT(formulaslot()));
		//阈值设置
		connect(m_button_widget, SIGNAL(thresholdsignal()), this, SLOT(thresholdslot()));
		//配置设置
		connect(m_button_widget, SIGNAL(configsignal()), this, SLOT(configslot()));		
		//选择配方
		//connect(m_select_control, SIGNAL(formulasignal(QString)), this, SLOT(formulaparameter(QString)));
		//显示配方信息
		//connect(this, SIGNAL(informationsignals(QString, QString)), m_select_control, SLOT(showformula(QString, QString)));
		//显示绘制框
		/*connect(this, SIGNAL(drawsignals(int, int, int, int, int, int, int, int, std::vector<bool>))
			, m_demo_widget, SLOT(drawslots(int, int, int, int, int, int, int, int, std::vector<bool>)));*/
		//跳转到对应图像
		//connect(m_demo_widget, SIGNAL(indexsignal(int)), this, SLOT(skipimage(int)));
	}

	//界面设置中文/英文 的转译器
	void MainFrame::setTranslator(QTranslator *translator)
	{
		m_translator = translator;
	}

	//界面设置中文/英文
	void MainFrame::slotChangeLang()
	{
		qApp->removeTranslator(m_translator);
		m_lang = 1 - m_lang;
		if (m_lang)
			m_translator->load("://uiframe/translations/smore_vimo_en.qm");
		else
			m_translator->load("://uiframe/translations/smore_vimo_zh-cn.qm");
		qApp->installTranslator(m_translator);
		ui->retranslateUi(this);

		m_log_widget->setTitle(tr("Log Analysis"));
		QStringList log_list_header;
		log_list_header << tr("DateTime") << tr("Contents");
		m_log_widget->setHeader(log_list_header);
	}

	//进度条
	void MainFrame::progressslots(int value)
	{
		if (value == 1)
		{
			_bardialog->show();
		}
		else if (value == 100)
		{
			_bardialog->accept();
		}
		else
		{
			_bardialog->setValue(value);
		}
	}

	//按钮控制
	void MainFrame::loadslot(int adminctrl)
	{
		adminstatus = adminctrl;
		if (adminctrl == 1)
		{
			m_button_widget->buttonopen();
		}
		else if (adminctrl == 2)
		{
			m_button_widget->buttonclose();
		}
	}

	//打开配方设置界面
	void  MainFrame::formulaslot()
	{
		//关闭首页显示
		//bshowcam = false;
		//m_formula_set = new FormulaDialog();	
		////实时显示
		////connect(m_formula_set, SIGNAL(camlivesignal(bool)), this, SLOT(camliveslot(bool)));
		////设置曝光
		//connect(m_formula_set, SIGNAL(sendcam1esignal(float)), this, SLOT(lcamslotE(float)));
		//connect(m_formula_set, SIGNAL(sendcam2esignal(float)), this, SLOT(mlcamslotE(float)));
		//connect(m_formula_set, SIGNAL(sendcam3esignal(float)), this, SLOT(mrcamslotE(float)));
		//connect(m_formula_set, SIGNAL(sendcam4esignal(float)), this, SLOT(rcamslotE(float)));
		////设置增益
		//connect(m_formula_set, SIGNAL(sendcag1esignal(float)), this, SLOT(lcamslotG(float)));
		//connect(m_formula_set, SIGNAL(sendcag2esignal(float)), this, SLOT(mlcamslotG(float)));
		//connect(m_formula_set, SIGNAL(sendcag3esignal(float)), this, SLOT(mrcamslotG(float)));
		//connect(m_formula_set, SIGNAL(sendcag4esignal(float)), this, SLOT(rcamslotG(float)));
		////获取参数
		//connect(m_formula_set, SIGNAL(camparamsignal()), this, SLOT(getcamparam()));
		//connect(this, SIGNAL(sendcamparamsignals(float, float, float, float, float, float, float, float)),
		//	m_formula_set, SLOT(getcamparamslots(float, float, float, float, float, float, float, float)));
		//m_formula_set->exec(); 
		//bshowcam = true;
		//载入配方参数
		//m_select_control->refreshcombobox();
	}

	//载入配方参数
	void MainFrame::formulaparameter(QString pathfile)
	{
		QString path = QCoreApplication::applicationDirPath() + "/formula/" + pathfile + ".json";
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("文件读取错误!"));
			message_box_dialog.exec();
			return;
		}

		QJsonParseError *error = new QJsonParseError;
		QJsonDocument jdc = QJsonDocument::fromJson(file.readAll(), error);
		//判断文件是否完整
		if (error->error != QJsonParseError::NoError)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, error->errorString());
			message_box_dialog.exec();
			return;
		}

		QJsonObject obj = jdc.object();        //获取对象	
		QStringList list = obj.keys();

		emit informationsignals(pathfile, QString::number(obj["count"].toInt()));

		int imagenum = obj["count"].toInt();

		int e1 = obj["camE1"].toInt();
		int e2 = obj["camE2"].toInt();
		int e3 = obj["camE3"].toInt();
		int e4 = obj["camE4"].toInt();
		int g1 = obj["camG1"].toInt();
		int g2 = obj["camG2"].toInt();
		int g3 = obj["camG3"].toInt();
		int g4 = obj["camG4"].toInt();
		//设置曝光
		lcamslotE(e1);
		mlcamslotE(e2);
		mrcamslotE(e3);
		rcamslotE(e4);		
		//设置增益
		lcamslotG(g1);
		mlcamslotG(g2);
		mrcamslotG(g3);
		rcamslotG(g4);
		//设置图像顺序
		int topstart = obj["topstart"].toInt();
		int topend = obj["topend"].toInt();
		int rightstart = obj["rightstart"].toInt();
		int rightend = obj["rightend"].toInt();
		int bottomstart = obj["bottomstart"].toInt();
		int bottomend = obj["bottomend"].toInt();
		int leftstart = obj["leftstart"].toInt();
		int leftend = obj["leftend"].toInt();
		std::vector<bool> type(imagenum, true);
		//发送图像顺序
		emit drawsignals(topstart, topend, rightstart, rightend,
			bottomstart, bottomend, leftstart, leftend, type);
	}

	//载入阈值配置
	void MainFrame::thresholdslot()
	{
    
	}

	//载入系统配置
	void MainFrame::configslot()
	{
		//读取plc、存图、数据库、服务器配置
		std::string systemparamDir = QCoreApplication::applicationDirPath().toStdString() + "/SysParamConfig.json";
		m_sys_param = m_config_set->GetSystemParamFromFile(systemparamDir);

		CamLFPath = QString::fromStdString(m_sys_param.LeftFront_Save_Dir);
		CamLBPath = QString::fromStdString(m_sys_param.LeftContrary_Save_Dir);
		CamRFPath = QString::fromStdString(m_sys_param.RightFront_Save_Dir);
		CamRBPath = QString::fromStdString(m_sys_param.RightContrary_Save_Dir);
	}

	//跳转到对应的图像
	void MainFrame::skipimage(int index)
	{

	}

#pragma region 相机设置

	//获取相机参数
	void MainFrame::getcamparam()
	{
		float camle, cammle, cammre, camre;
		float camlg, cammlg, cammrg, camrg;
		camle = m_hikcam_l->getExposureTime();
		cammle = m_hikcam_ml->getExposureTime();
		cammre = m_hikcam_mr->getExposureTime();
		camre = m_hikcam_r->getExposureTime();

		camlg = m_hikcam_l->getGain();
		cammlg = m_hikcam_ml->getGain();
		cammrg = m_hikcam_mr->getGain();
		camrg = m_hikcam_r->getGain();

		emit sendcamparamsignals(camle, camlg, cammle, cammlg, cammre, cammrg, camre, camrg);
	}

	void MainFrame::camliveslot(float value)
	{
		
	}
	//设置曝光
	void MainFrame::lcamslotE(float value)
	{
		m_hikcam_l->setExposureTime(value);
	}
	void MainFrame::mlcamslotE(float value)
	{
		m_hikcam_ml->setExposureTime(value);
	}
	void MainFrame::mrcamslotE(float value)
	{
		m_hikcam_mr->setExposureTime(value);
	}
	void MainFrame::rcamslotE(float value)
	{
		m_hikcam_r->setExposureTime(value);
	}
	//设置增益
	void MainFrame::lcamslotG(float value)
	{
		m_hikcam_l->setGain(value);
	}
	void MainFrame::mlcamslotG(float value)
	{
		m_hikcam_ml->setGain(value);
	}
	void MainFrame::mrcamslotG(float value)
	{
		m_hikcam_mr->setGain(value);
	}
	void MainFrame::rcamslotG(float value)
	{
		m_hikcam_r->setGain(value);
	}
#pragma endregion

	//日志
	void MainFrame::InfoLog(QString log)
	{
		logservice::Logger::getInstance().appendLog({ logservice::LogLevel::Info, logservice::LogSource::AI }, log);
	}
	void MainFrame::WarningLog(QString log)
	{
		logservice::Logger::getInstance().appendLog({ logservice::LogLevel::Warning, logservice::LogSource::Camera }, log);
	}
	void MainFrame::ErrorLog(QString log)
	{
		logservice::Logger::getInstance().appendLog({ logservice::LogLevel::Error, logservice::LogSource::Others }, log);
	}

	//创建文件夹
	bool MainFrame::isDirExist(QString fullPath)
	{
		QDir dir(fullPath);
		if (dir.exists())
		{
			return true;
		}
		else
		{
			bool ok = dir.mkpath(fullPath);//创建多级目录
			return ok;
		}
	}
#pragma endregion
}
// namespace vimo::display
