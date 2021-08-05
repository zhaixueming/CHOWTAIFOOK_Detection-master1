/****************************************************************************
 *  @file     pointdialog.h
 *  @brief    点位设置界面
 *  @author
 *  @email
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef CAMSETDIALOG_H
#define CAMSETDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QWidget>
#include <QDateTime>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <windows.h>
#include "configtitlebar.h"
#include "vimocommon/vimocommon.h"
#include "uiframe/mainuiset/imageviews/sixviewswidget.h"

namespace Ui
{
	class CamsetDialog;
}

namespace vimo::display
{
	class CamsetDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit CamsetDialog(QWidget *parent = nullptr);
		~CamsetDialog();

	private slots:
		void slotCheckAndClose();
		//添加按钮
		void on_ButtonAdd_clicked();
		//加载
		void on_ButtonLoad_clicked();
		//删除
		void on_ButtonDelete_clicked();		
		//获取相机参数
		void on_Buttongetcam_clicked();		
		//保存按钮
		void on_ButtonSave_clicked();
		//取消按钮
		void on_ButtonCancel_clicked();
		
		//单张取图
		void on_Buttononeimage_clicked();
		//实时取图
		void on_Buttonlive_clicked();
		//测试参数
		void on_Buttontest1_clicked();
		void on_Buttontest2_clicked();
		void on_Buttontest3_clicked();
		void on_Buttontest4_clicked();
		//存图
		void on_Buttonsaveimage1_clicked();
		void on_Buttonsaveimage2_clicked();
		void on_Buttonsaveimage3_clicked();
		void on_Buttonsaveimage4_clicked();
		//获取相机参数
		void getcamparamslots(float e1, float g1, float e2, float g2, float e3, float g3, float e4, float g4);

	signals:
		void camparamsignal();

		void sendcam1esignal(float exp);
		void sendcam2esignal(float exp);
		void sendcam3esignal(float exp);
		void sendcam4esignal(float exp);

		void sendcam1gsignal(float gain);
		void sendcam2gsignal(float gain);
		void sendcam3gsignal(float gain);
		void sendcam4gsignal(float gain);
	private:
		void initWidgets();
		void initComboBox();
			
		//获取参数
		void getparam(QString index);
		//设置参数
		void setparam(QString index);
		
	private:
		Ui::CamsetDialog *ui;
		ConfigTitleBar *m_titleBar{ nullptr };
		std::vector<ImageView::ViewInfo> info_list;
		// 图片显式框
		QWidget *m_view_frame{ nullptr };
	};
}  // namespace vtk::display
#endif  // MATERIALSETDIALOG_H
