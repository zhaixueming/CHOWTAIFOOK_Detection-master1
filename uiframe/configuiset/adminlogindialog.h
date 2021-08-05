/****************************************************************************
 *  @file     adminlogindialog.h
 *  @brief    登录页面
 *  @author
 *  @email
 *  @version
 *  @date
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef ADMINLOGINDIALOG_H
#define ADMINLOGINDIALOG_H

#include <QDialog>
#include "uiframe/configuiset/passworddialog.h"
#include "serializer/AdminConfig.h"
#include "uiframe/commonuiset/messagedialog/messagedialog.h"

namespace Ui {
class adminLoginDialog;
}

namespace vimo::display
{
	class adminLoginDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit adminLoginDialog(QWidget *parent = nullptr);
		~adminLoginDialog();

		int adminctrl = 2;

	private slots:
		void on_adminButton_clicked();
		void on_cancelButton_clicked();
		void on_Buttonchange_clicked();
	private:
		//读取文件
		AdminParam GetadminParamFromFile(std::string path);
		//保存配置
		void SaveConfig();


	private:
		Ui::adminLoginDialog *ui;
		AdminParam _adminparam;
	};
}
#endif // ADMINLOGINDIALOG_H
