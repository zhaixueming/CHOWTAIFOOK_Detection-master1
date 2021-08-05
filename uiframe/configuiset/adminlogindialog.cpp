/****************************************************************************
 *  @file     adminlogindialog.cpp
 *  @brief    登录页面
 *  @author   
 *  @email    
 *  @version
 *  @date     
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "adminlogindialog.h"
#include "ui_adminlogindialog.h"
#include <iostream>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>

namespace vimo::display
{
	adminLoginDialog::adminLoginDialog(QWidget *parent) : QDialog(parent), ui(new Ui::adminLoginDialog)
	{
		ui->setupUi(this);
		this->setWindowTitle(tr("登陆"));  // 设置弹出框标题
		setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

		//init
		std::string adminparamDir = QCoreApplication::applicationDirPath().toStdString() + "/AdminConfig.json";
		_adminparam = GetadminParamFromFile(adminparamDir);

		ui->info_comboBox->addItem("管理员");
		ui->info_comboBox->addItem("操作员");
	}

	adminLoginDialog::~adminLoginDialog()
	{
		delete ui;
	}

	void adminLoginDialog::on_adminButton_clicked()
	{
		QString configpassword;
		QString linepassword = ui->passwordLineEdit->text();
		if (ui->info_comboBox->currentIndex() == 0)
		{
			configpassword = QString::fromStdString(_adminparam.adminpassword);
			if (configpassword == linepassword)
			{
				adminctrl = 1;
				accept();
			}
			else
			{
				MessageDialog message_box_dialog(DialogType::errorDialog, tr("密码错误!"));
				message_box_dialog.exec();
			}
		}
		else if (ui->info_comboBox->currentIndex() == 1)
		{
			configpassword = QString::fromStdString(_adminparam.userpassword);
			if (configpassword == linepassword)
			{
				adminctrl = 2;
				accept();
			}
			else
			{
				MessageDialog message_box_dialog(DialogType::errorDialog, tr("密码错误!"));
				message_box_dialog.exec();
			}
		}		
	}

	void adminLoginDialog::on_cancelButton_clicked()
	{
		reject();
	}

	void adminLoginDialog::on_Buttonchange_clicked()
	{
		passwordDialog passwordDlg;
		passwordDlg.exec();
	}

	//读取文件
	AdminParam adminLoginDialog::GetadminParamFromFile(std::string path)
	{
		AdminParam param;
		std::ifstream fi(path.c_str());
		if (fi.good())
		{
			nlohmann::json j;
			fi >> j;
			param = j.get<AdminParam>();
		}
		else
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("Get System Param File faild!"));
			message_box_dialog.exec();
		}
		return param;
	}

	//保存配置
	void adminLoginDialog::SaveConfig()
	{
		std::string sysparamDir = QCoreApplication::applicationDirPath().toStdString() + "/AdminConfig.json";
		std::ofstream fo(sysparamDir.c_str());
		nlohmann::json j = _adminparam;
		fo << std::setw(4) << j << std::endl;
		fo.flush();
	}
}