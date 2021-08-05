/****************************************************************************
 *  @file     passworddialog.cpp
 *  @brief    登录页面
 *  @author
 *  @email
 *  @version
 *  @date
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "passworddialog.h"
#include "ui_passworddialog.h"
#include <iostream>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>

namespace vimo::display
{
	passwordDialog::passwordDialog(QWidget *parent) : QDialog(parent), ui(new Ui::passwordDialog)
	{
		ui->setupUi(this);
		this->setWindowTitle(tr("修改密码"));  // 设置弹出框标题
		setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

		//init
		std::string adminparamDir = QCoreApplication::applicationDirPath().toStdString() + "/AdminConfig.json";
		_adminparam = GetadminParamFromFile(adminparamDir);

		ui->info_comboBox->addItem("管理员");
		ui->info_comboBox->addItem("操作员");
	}

	passwordDialog::~passwordDialog()
	{
		delete ui;
	}

	void passwordDialog::on_adminButton_clicked()
	{
		QString configpassword;
		QString linepassword = ui->passwordLineEdit->text();
		if (ui->info_comboBox->currentIndex() == 0)
		{
			configpassword = QString::fromStdString(_adminparam.adminpassword);
			if (configpassword == linepassword)
			{
				QString newpassword = ui->passwordLineEditn->text();
				QString newpasswordd = ui->passwordLineEditnd->text();
				if (newpassword == newpasswordd)
				{
					_adminparam.adminpassword = newpassword.toStdString();
					SaveConfig();
					MessageDialog message_box_dialog(DialogType::infoDialog, tr("修改完成!"));
					message_box_dialog.exec();
					accept();
				}
				else
				{
					MessageDialog message_box_dialog(DialogType::infoDialog, tr("重复密码错误!"));
					message_box_dialog.exec();
				}
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
				QString newpassword = ui->passwordLineEditn->text();
				QString newpasswordd = ui->passwordLineEditnd->text();
				if (newpassword == newpasswordd)
				{
					_adminparam.adminpassword = newpassword.toStdString();
					SaveConfig();
					MessageDialog message_box_dialog(DialogType::infoDialog, tr("修改完成!"));
					message_box_dialog.exec();
					accept();
				}
				else
				{
					MessageDialog message_box_dialog(DialogType::infoDialog, tr("重复密码错误!"));
					message_box_dialog.exec();
				}
			}
			else
			{
				MessageDialog message_box_dialog(DialogType::errorDialog, tr("密码错误!"));
				message_box_dialog.exec();
			}
		}
	}

	void passwordDialog::on_cancelButton_clicked()
	{
		reject();
	}

	//读取文件
	AdminParam passwordDialog::GetadminParamFromFile(std::string path)
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
	void passwordDialog::SaveConfig()
	{
		std::string sysparamDir = QCoreApplication::applicationDirPath().toStdString() + "/AdminConfig.json";
		std::ofstream fo(sysparamDir.c_str());
		nlohmann::json j = _adminparam;
		fo << std::setw(4) << j << std::endl;
		fo.flush();
	}
}