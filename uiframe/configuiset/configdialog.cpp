/****************************************************************************
 *  @file     configdialog.cpp
 *  @brief    设置界面
 *  @author
 *  @email
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "configdialog.h"
#include "configtitlebar.h"
#include "ui_configdialog.h"
#include "uiframe/commonuiset/messagedialog/messagedialog.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>

namespace vimo::display
{
	ConfigDialog::ConfigDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ConfigDialog)
	{
		ui->setupUi(this);
		setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
		setWindowModality(Qt::ApplicationModal);

		initWidgets();
		ReadingData();
	}

	ConfigDialog::~ConfigDialog()
	{
		delete ui;
	}

	void ConfigDialog::initWidgets()
	{
		m_titleBar = new ConfigTitleBar(this);
		m_titleBar->m_pTitleContent->setText(tr("设置"));
		ui->titlebar_layout->addWidget(m_titleBar);
		connect(m_titleBar, SIGNAL(signalClose()), this, SLOT(slotCheckAndClose()));
	}

	void ConfigDialog::slotCheckAndClose()
	{
		
		accept();
	}

	//读取文件
	SystemParam ConfigDialog::GetSystemParamFromFile(std::string path)
	{
		SystemParam param;
		std::ifstream fi(path.c_str());
		if (fi.good())
		{
			nlohmann::json j;
			fi >> j;
			param = j.get<SystemParam>();
		}
		else
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("Get System Param File faild!"));
			message_box_dialog.exec();
		}
		return param;
	}

	//保存配置
	void ConfigDialog::SaveConfig()
	{
		std::string sysparamDir = QCoreApplication::applicationDirPath().toStdString() + "/SysParamConfig.json";
		std::ofstream fo(sysparamDir.c_str());
		nlohmann::json j = _systemparam;
		fo << std::setw(4) << j << std::endl;
		fo.flush();
	}

	//加载到控件中
	void ConfigDialog::ReadingData()
	{
		//init
		std::string systemparamDir = QCoreApplication::applicationDirPath().toStdString() + "/SysParamConfig.json";
		_systemparam = GetSystemParamFromFile(systemparamDir);
		
		ui->lineEditPLCIP->setText(QString().fromStdString(_systemparam.plc_ipadd));
		ui->lineEditPLCPort->setText(QString().fromStdString(_systemparam.plc_port));
		ui->lineEditupdata->setText(QString().fromStdString(_systemparam.plc_update));
		ui->lineEditmateial->setText(QString().fromStdString(_systemparam.plc_updateUid));
		ui->lineEditprofile->setText(QString().fromStdString(_systemparam.plc_updatematerial));
		ui->lineEditstart->setText(QString().fromStdString(_systemparam.plc_start));
		ui->lineEditlose->setText(QString().fromStdString(_systemparam.plc_lose));
		ui->lineEditlcodes->setText(QString().fromStdString(_systemparam.plc_lcode));
		ui->lineEditlok->setText(QString().fromStdString(_systemparam.plc_lok));
		ui->lineEditlng->setText(QString().fromStdString(_systemparam.plc_lng));
		ui->lineEditlcode->setText(QString().fromStdString(_systemparam.plc_lcodeback));
		ui->lineEditlcodeb->setText(QString().fromStdString(_systemparam.plc_lcodestart));
		ui->lineEditrcodes->setText(QString().fromStdString(_systemparam.plc_rcode));
		ui->lineEditrok->setText(QString().fromStdString(_systemparam.plc_rok));
		ui->lineEditrng->setText(QString().fromStdString(_systemparam.plc_rng));
		ui->lineEditrcode->setText(QString().fromStdString(_systemparam.plc_rcodeback));
		ui->lineEditrcodeb->setText(QString().fromStdString(_systemparam.plc_rcodestart));
		
		ui->lineEditLeftFront->setText(QString().fromStdString(_systemparam.LeftFront_Save_Dir));
		ui->lineEditLeftContrary->setText(QString().fromStdString(_systemparam.LeftContrary_Save_Dir));
		ui->lineEditRightFront->setText(QString().fromStdString(_systemparam.RightFront_Save_Dir));
		ui->lineEditRightContrary->setText(QString().fromStdString(_systemparam.RightContrary_Save_Dir));

		ui->lineEditLeftFrontCam->setText(QString().fromStdString(_systemparam.LeftFront));
		ui->lineEditLeftContraryCam->setText(QString().fromStdString(_systemparam.LeftContrary));
		ui->lineEditRightFrontCam->setText(QString().fromStdString(_systemparam.RightFront));
		ui->lineEditRightContraryCam->setText(QString().fromStdString(_systemparam.RightContrary));

		ui->lineEdithoneywell_l1IP->setText(QString().fromStdString(_systemparam.honeywelipl1));
		ui->lineEdithoneywell_r1IP->setText(QString().fromStdString(_systemparam.honeywelipr1));
		ui->lineEdithoneywell_l2IP->setText(QString().fromStdString(_systemparam.honeywelipl2));
		ui->lineEdithoneywell_r2IP->setText(QString().fromStdString(_systemparam.honeywelipr2));
		ui->lineEdithoneywell_l1port->setText(QString().fromStdString(_systemparam.honeywelportl1));
		ui->lineEdithoneywell_l2port->setText(QString().fromStdString(_systemparam.honeywelportl2));
		ui->lineEdithoneywell_r1port->setText(QString().fromStdString(_systemparam.honeywelportr1));
		ui->lineEdithoneywell_r2port->setText(QString().fromStdString(_systemparam.honeywelportr2));

		ui->lineEditRect->setText(QString().fromStdString(_systemparam.Rect));
		ui->lineEditUnit->setText(QString().fromStdString(_systemparam.Unit));
		ui->lineEditNG->setText(QString().fromStdString(_systemparam.NG));
	}
	//加载地址按钮
	void ConfigDialog::on_ButtonLeftFront_clicked()
	{
		QString StringFile = QFileDialog::getExistingDirectory(this, "选择目录", "E://");
		ui->lineEditLeftFront->setText(StringFile);
	}
	void ConfigDialog::on_ButtonLeftContrary_clicked()
	{
		QString StringFile = QFileDialog::getExistingDirectory(this, "选择目录", "E://");
		ui->lineEditLeftContrary->setText(StringFile);
	}
	void ConfigDialog::on_ButtonRightFront_clicked()
	{
		QString StringFile = QFileDialog::getExistingDirectory(this, "选择目录", "E://");
		ui->lineEditRightFront->setText(StringFile);
	}
	void ConfigDialog::on_ButtonRightContrary_clicked()
	{
		QString StringFile = QFileDialog::getExistingDirectory(this, "选择目录", "E://");
		ui->lineEditRightContrary->setText(StringFile);
	}
	
	//加载地址按钮
	void ConfigDialog::on_ButtonLeftFrontCam_clicked()
	{
		QString StringFile = QFileDialog::getOpenFileName(this, "选择左工位正面相机配置文件", "/", "图像文件 (*.ccf);");
		ui->lineEditLeftFrontCam->setText(StringFile);
	}
	void ConfigDialog::on_ButtonLeftContraryCam_clicked()
	{
		QString StringFile = QFileDialog::getOpenFileName(this, "选择左工位反面相机配置文件", "/", "图像文件 (*.ccf);");
		ui->lineEditLeftContraryCam->setText(StringFile);
	}
	void ConfigDialog::on_ButtonRightFrontCam_clicked()
	{
		QString StringFile = QFileDialog::getOpenFileName(this, "选择右工位正面相机配置文件", "/", "图像文件 (*.ccf);");
		ui->lineEditRightFrontCam->setText(StringFile);
	}
	void ConfigDialog::on_ButtonRightContraryCam_clicked()
	{
		QString StringFile = QFileDialog::getOpenFileName(this, "选择右工位反面相机配置文件", "/", "图像文件 (*.ccf);");
		ui->lineEditRightContraryCam->setText(StringFile);
	}

	//保存按钮
	void ConfigDialog::on_ButtonSave_clicked()
	{
		_systemparam.plc_ipadd = ui->lineEditPLCIP->text().toStdString();
		_systemparam.plc_port = ui->lineEditPLCPort->text().toStdString();

		_systemparam.plc_update = ui->lineEditupdata->text().toStdString();
		_systemparam.plc_updateUid = ui->lineEditmateial->text().toStdString();
		_systemparam.plc_updatematerial = ui->lineEditprofile->text().toStdString();
		_systemparam.plc_start = ui->lineEditstart->text().toStdString();
		_systemparam.plc_lose = ui->lineEditlose->text().toStdString();

		_systemparam.plc_lcode = ui->lineEditlcodes->text().toStdString();
		_systemparam.plc_lok = ui->lineEditlok->text().toStdString();
		_systemparam.plc_lng = ui->lineEditlng->text().toStdString();
		_systemparam.plc_lcodeback = ui->lineEditlcode->text().toStdString();
		_systemparam.plc_lcodestart = ui->lineEditlcodeb->text().toStdString();

		_systemparam.plc_rcode = ui->lineEditrcodes->text().toStdString();
		_systemparam.plc_rok = ui->lineEditrok->text().toStdString();
		_systemparam.plc_rng = ui->lineEditrng->text().toStdString();
		_systemparam.plc_rcodeback = ui->lineEditrcode->text().toStdString();
		_systemparam.plc_rcodestart = ui->lineEditrcodeb->text().toStdString();
		
		_systemparam.LeftFront_Save_Dir = ui->lineEditLeftFront->text().toStdString();
		_systemparam.LeftContrary_Save_Dir = ui->lineEditLeftContrary->text().toStdString();
		_systemparam.RightFront_Save_Dir = ui->lineEditRightFront->text().toStdString();
		_systemparam.RightContrary_Save_Dir = ui->lineEditRightContrary->text().toStdString();

		_systemparam.LeftFront = ui->lineEditLeftFrontCam->text().toStdString();
		_systemparam.LeftContrary = ui->lineEditLeftContraryCam->text().toStdString();
		_systemparam.RightFront = ui->lineEditRightFrontCam->text().toStdString();
		_systemparam.RightContrary = ui->lineEditRightContraryCam->text().toStdString();

		_systemparam.honeywelipl1 = ui->lineEdithoneywell_l1IP->text().toStdString();
		_systemparam.honeywelipr1 = ui->lineEdithoneywell_r1IP->text().toStdString();
		_systemparam.honeywelipl2 = ui->lineEdithoneywell_l2IP->text().toStdString();
		_systemparam.honeywelipr2 = ui->lineEdithoneywell_r2IP->text().toStdString();
		_systemparam.honeywelportl1 = ui->lineEdithoneywell_l1port->text().toStdString();
		_systemparam.honeywelportl2 = ui->lineEdithoneywell_l2port->text().toStdString();
		_systemparam.honeywelportr1 = ui->lineEdithoneywell_r1port->text().toStdString();
		_systemparam.honeywelportr2 = ui->lineEdithoneywell_r2port->text().toStdString();

		_systemparam.Rect = ui->lineEditRect->text().toStdString();
		_systemparam.Unit = ui->lineEditUnit->text().toStdString();
		_systemparam.NG = ui->lineEditNG->text().toStdString();
		
		SaveConfig();
		MessageDialog message_box_dialog(DialogType::infoDialog, tr("保存成功!"));
		message_box_dialog.exec();
	}
	//取消按钮
	void ConfigDialog::on_ButtonCancel_clicked()
	{
		accept();
	}
}  // namespace vtk::display
