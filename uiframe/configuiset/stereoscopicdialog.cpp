/****************************************************************************
 *  @file     thresholddialog.cpp
 *  @brief    阈值设置界面
 *  @author
 *  @email
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "stereoscopicdialog.h"
#include "configtitlebar.h"
#include "ui_stereoscopicdialog.h"
#include "uiframe/commonuiset/messagedialog/messagedialog.h"
#include <QDebug>
#include <QFile>
#include <QGraphicsDropShadowEffect>


namespace vimo::display
{
	StereoscopicDialog::StereoscopicDialog(QWidget *parent) : QDialog(parent), ui(new Ui::StereoscopicDialog)
	{
		ui->setupUi(this);
		setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
		setWindowModality(Qt::ApplicationModal);
		initWidgets();
        ReadingData();
	}

	StereoscopicDialog::~StereoscopicDialog()
	{
		delete ui;
	}

	void StereoscopicDialog::initWidgets()
	{
		m_titleBar = new ConfigTitleBar(this);
		m_titleBar->m_pTitleContent->setText(tr("运动设置"));
		ui->titlebar_layout->addWidget(m_titleBar);
		connect(m_titleBar, SIGNAL(signalClose()), this, SLOT(slotCheckAndClose()));
	}

	void StereoscopicDialog::slotCheckAndClose()
	{
		accept();
	}

	////读取文件
	//StereoscopicParam StereoscopicDialog::GetSystemParamFromFile(std::string path)
 //   {
 //       ThresholdParam param;
 //       std::ifstream fi(path.c_str());
 //       if (fi.good())
 //       {
 //           nlohmann::json j;
 //           fi >> j;
 //           param = j.get<ThresholdParam>();
 //       }
 //       else
 //       {
 //           MessageDialog message_box_dialog(DialogType::errorDialog, tr("Get Threshold Param File faild!"));
 //           message_box_dialog.exec();
 //       }
 //       return param;
 //   }

	void StereoscopicDialog::SaveThreshold()
	{
       /* std::string sysparamDir = QCoreApplication::applicationDirPath().toStdString() + "/SysParamthreshold.json";
        std::ofstream fo(sysparamDir.c_str());
        nlohmann::json j = _thresholdparam;
        fo << std::setw(4) << j << std::endl;
        fo.flush();*/
	}

	void StereoscopicDialog::ReadingData()
	{
       /* std::string systemparamDir = QCoreApplication::applicationDirPath().toStdString() + "/SysParamthreshold.json";
        _thresholdparam = GetSystemParamFromFile(systemparamDir);

		ui->le_pressA->setText(QString().fromStdString(_thresholdparam.pressedA));
        ui->le_pressB->setText(QString().fromStdString(_thresholdparam.pressedB));
        ui->le_pressC->setText(QString().fromStdString(_thresholdparam.pressedC));

        ui->le_bumpsA->setText(QString().fromStdString(_thresholdparam.bumpsA));
        ui->le_bumpsB->setText(QString().fromStdString(_thresholdparam.bumpsB));
        ui->le_bumpsC->setText(QString().fromStdString(_thresholdparam.bumpsC));

        ui->le_scratchHardA->setText(QString().fromStdString(_thresholdparam.scratchHardA));
        ui->le_scratchHardB->setText(QString().fromStdString(_thresholdparam.scratchHardB));
        ui->le_scratchHardC->setText(QString().fromStdString(_thresholdparam.scratchHardC));
        ui->le_scratchSmallA->setText(QString().fromStdString(_thresholdparam.scratchSmallA));
        ui->le_scratchSmallB->setText(QString().fromStdString(_thresholdparam.scratchSmallB));
        ui->le_scratchSmallC->setText(QString().fromStdString(_thresholdparam.scratchSmallC));

        ui->le_brushA->setText(QString().fromStdString(_thresholdparam.brushA));
        ui->le_brushB->setText(QString().fromStdString(_thresholdparam.brushB));
        ui->le_brushC->setText(QString().fromStdString(_thresholdparam.brushC));

        ui->le_baomoBP->setText(QString().fromStdString(_thresholdparam.baomoBP));
        ui->le_baomoTP->setText(QString().fromStdString(_thresholdparam.baomoTP));

        ui->le_pockA->setText(QString().fromStdString(_thresholdparam.pockA));
        ui->le_pockB->setText(QString().fromStdString(_thresholdparam.pockB));
        ui->le_pockC->setText(QString().fromStdString(_thresholdparam.pockC));

        ui->le_dirty->setText(QString().fromStdString(_thresholdparam.dirty));

        ui->le_mirageA->setText(QString().fromStdString(_thresholdparam.mirageA));
        ui->le_mirageB->setText(QString().fromStdString(_thresholdparam.mirageB));
        ui->le_mirageC->setText(QString().fromStdString(_thresholdparam.mirageC));*/

	}

	//保存按钮
	void StereoscopicDialog::on_ButtonSave_clicked()
	{
		//MessageDialog message_box_dialog(DialogType::warningDialog, tr("确认保存"));
		//message_box_dialog.exec();

		/*MessageDialog message_box_dialog(DialogType::warningDialog, tr("料单修改未确认，无法保存! 请确认料单！"));
		message_box_dialog.exec();*/

		/*_thresholdparam.pressedA = ui->le_pressA->text().toStdString();
        _thresholdparam.pressedB = ui->le_pressB->text().toStdString();
        _thresholdparam.pressedC = ui->le_pressC->text().toStdString();

        _thresholdparam.bumpsA = ui->le_bumpsA->text().toStdString();
        _thresholdparam.bumpsA = ui->le_bumpsB->text().toStdString();
        _thresholdparam.bumpsA = ui->le_bumpsC->text().toStdString();

		_thresholdparam.scratchHardA = ui->le_scratchHardA->text().toStdString();
        _thresholdparam.scratchHardB = ui->le_scratchHardB->text().toStdString();
        _thresholdparam.scratchHardC = ui->le_scratchHardC->text().toStdString();
        _thresholdparam.scratchSmallA = ui->le_scratchSmallA->text().toStdString();
        _thresholdparam.scratchSmallB = ui->le_scratchSmallB->text().toStdString();
        _thresholdparam.scratchSmallC = ui->le_scratchSmallC->text().toStdString();

		_thresholdparam.brushA = ui->le_brushA->text().toStdString();
        _thresholdparam.brushB = ui->le_brushB->text().toStdString();
        _thresholdparam.brushC = ui->le_brushC->text().toStdString();

        _thresholdparam.baomoBP = ui->le_baomoBP->text().toStdString();
        _thresholdparam.baomoTP = ui->le_baomoTP->text().toStdString();

        _thresholdparam.dirty = ui->le_dirty->text().toStdString();

		_thresholdparam.pockA = ui->le_pockA->text().toStdString();
        _thresholdparam.pockB = ui->le_pockB->text().toStdString();
        _thresholdparam.pockC = ui->le_pockC->text().toStdString();

        _thresholdparam.mirageA = ui->le_mirageA->text().toStdString();
        _thresholdparam.mirageB = ui->le_mirageB->text().toStdString();
        _thresholdparam.mirageC = ui->le_mirageC->text().toStdString();

		SaveThreshold();*/

		MessageDialog message_box_dialog(DialogType::infoDialog, tr("保存成功!"));
        message_box_dialog.exec();
	}

	//取消按钮
	void StereoscopicDialog::on_pushButtonCancel_clicked()
	{
		accept();
	}
}  // namespace vtk::display
