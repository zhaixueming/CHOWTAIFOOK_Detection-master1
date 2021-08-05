/****************************************************************************
 *  @file     mainframe.h
 *  @brief    界面主显示框类
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QMainWindow>
#include <QQueue>
#include <QTranslator>
#include <QDir>
#include <windows.h>
#include "titlebarwidget.h"
#include <QDesktopWidget>

#include "logservice/logservice.h"
#include "uiframe/commonuiset/messagedialog/messagedialog.h"
#include "uiframe/commonuiset/messagedialog/progressbardialog.h"
#include "uiframe/configuiset/configdialog.h"
#include "uiframe/configuiset/camsetdialog.h"
#include "uiframe/configuiset/stereoscopicdialog.h"
#include "infowidget.h"
#include "buttonwidget.h"
#include "resultwidget.h"
#include "statisticswidget.h"
#include "datawidget.h"
#include "serializer/Config.h"
#include "communication/stripprocessor.h"
#include "singleviewwidget.h"
#include "imageviews/sixviewswidget.h"
#include "communication/mcplc.h"
#include "communication/readcode.h"
#include "Flow/serialcommond.h"

#include "cameraservice/hikvisionsdk.h"

namespace Ui
{
	class MainFrame;
}

namespace vimo::display
{
	class TitleBarWidget;
	class LogWidget;

	class MainFrame : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit MainFrame(QWidget *parent = nullptr);
		~MainFrame();
		void setTranslator(QTranslator *);

	private:
		Ui::MainFrame *ui;
		TitleBarWidget *m_titlebar_widget{ nullptr };
		ButtonWidget *m_button_widget{ nullptr };
		StatisticsWidget *m_statistics_widget{ nullptr };
		InfoWidget *m_info_widget{ nullptr };
		SingleViewWidget *m_single_view{ nullptr };
		ResultWidget *m_result_widget{ nullptr };
		DataWidget *m_data_widget{ nullptr };
		LogWidget *m_log_widget{ nullptr };

		// 图片显式框
		QWidget *m_view_frame{ nullptr };
		// 界面语言// 语言
		int m_lang{ 0 };
		// 界面语言
		QTranslator *m_translator{ nullptr };
		ConfigDialog *m_config_set{ nullptr };
		CamsetDialog *m_cam_set{ nullptr };
		StereoscopicDialog *m_stereoscopic_set{ nullptr };
		BarDialog *_bardialog = new BarDialog();

	private:
		//存图文件夹
		QString CamLFPath;
		QString CamLBPath;
		QString CamRFPath;
		QString CamRBPath;
		//配方
		SystemParam m_sys_param;
		//阈值
		ThresholdParam m_threshold_param;
		//获取图像队列
		QQueue<cv::Mat> QueueImageL;
		QMutex MutexImageL;
		QQueue<cv::Mat> QueueImageML;
		QMutex MutexImageML;
		QQueue<cv::Mat> QueueImageMR;
		QMutex MutexImageMR;
		QQueue<cv::Mat> QueueImageR;
		QMutex MutexImageR;
		//海康相机声明
		HikvisionSDK* m_hikcam_l;
		HikvisionSDK* m_hikcam_ml;
		HikvisionSDK* m_hikcam_mr;
		HikvisionSDK* m_hikcam_r;

		//图像处理队列
		unsigned int __stdcall ImageLThread();
		unsigned int __stdcall ImageMLThread();
		unsigned int __stdcall ImageMRThread();
		unsigned int __stdcall ImageRThread();
		std::thread LImageListener;
		std::thread MLImageListener;
		std::thread MRImageListener;
		std::thread RImageListener;

		//账号权限
		int adminstatus = 2;
		//初始化是否成功
		bool bstart = true;
		//是否在首页显示
		bool bshowcam = true;
		//关闭软件标志位
		bool bclose = true;

	private:
		//初始化
		void init();
		//登录
		void load();
		//界面初始化
		void initWidgets();
		//界面信号槽
		void initConnects();
		//初始化配置
		void initconfig();
		//初始化PLC
		void initPlc();
		//初始化hik相机
		void initHik();
		//线程初始化
		void initthread();
		//显示信号槽
		void ShowImage();
		//清理队列
		void clearqueue();
		//控制曝光
		bool CamControl();
		
		//日志
		void InfoLog(QString log);
		void WarningLog(QString log);
		void ErrorLog(QString log);

	signals:
		void progresssignals(int value);
		//发送相机参数
		void sendcamparamsignals(float e1, float g1, float e2, float g2, float e3, float g3, float e4, float g4);
		//发送显示信息
		void informationsignals(QString name, QString num);
		//发送 绘制
		void drawsignals(int topstart, int topend, int rightstart, int rightend,
			int bottomstart, int bottomend, int leftstart, int leftend, std::vector<bool> type);
	private slots:
		//修改界面语言	
		void slotChangeLang();
		//按钮控制
		void loadslot(int adminctrl);
		//打开料单设置界面
		void formulaslot();
		//载入配方参数
		void formulaparameter(QString pathfile);
		//载入阈值配置
		void thresholdslot();
		//载入系统配置
		void configslot();
		//跳转到对应的图像
		void skipimage(int index);
		//创建文件夹
		bool isDirExist(QString fullPath);
		//进度条
		void progressslots(int value);
		//相机实时取图
		void camliveslot(float value);
		//获取相机参数
		void getcamparam();
		//设置曝光
		void lcamslotE(float value);
		void mlcamslotE(float value);
		void mrcamslotE(float value);
		void rcamslotE(float value);
		//设置增益
		void lcamslotG(float value);
		void mlcamslotG(float value);
		void mrcamslotG(float value);
		void rcamslotG(float value);
	};
}  // namespace vimo::display
#endif  // MAINFRAME_H
