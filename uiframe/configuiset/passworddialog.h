/****************************************************************************
 *  @file     passworddialog.h
 *  @brief    登录页面
 *  @author
 *  @email
 *  @version
 *  @date
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>
#include "serializer/AdminConfig.h"
#include "uiframe/commonuiset/messagedialog/messagedialog.h"

namespace Ui 
{
class passwordDialog;
}

namespace vimo::display
{
	class passwordDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit passwordDialog(QWidget *parent = nullptr);
		~passwordDialog();

	private slots:
		void on_adminButton_clicked();
		void on_cancelButton_clicked();

	private:
		//读取文件
		AdminParam GetadminParamFromFile(std::string path);
		//保存配置
		void SaveConfig();


	private:
		Ui::passwordDialog *ui;
		AdminParam _adminparam;
	};
}
#endif // ADMINLOGINDIALOG_H
