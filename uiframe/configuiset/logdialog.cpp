/****************************************************************************
 *  @file     logdialog.cpp
 *  @brief    料单设置界面
 *  @author
 *  @email
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "logdialog.h"
#include "configtitlebar.h"
#include "ui_logdialog.h"
#include "uiframe/commonuiset/messagedialog/messagedialog.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>

namespace vimo::display
{
	LogDialog::LogDialog(QWidget *parent) : QDialog(parent), ui(new Ui::LogDialog)
	{
		ui->setupUi(this);
		setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
		setWindowModality(Qt::ApplicationModal);

		initWidgets();

		initComboBox();
	}

	LogDialog::~LogDialog()
	{
		delete ui;
	}

	void LogDialog::initWidgets()
	{
		m_titleBar = new ConfigTitleBar(this);
		m_titleBar->m_pTitleContent->setText(tr("日志"));
		ui->titlebar_layout->addWidget(m_titleBar);

		connect(m_titleBar, SIGNAL(signalClose()), this, SLOT(slotCheckAndClose()));
	}

	void LogDialog::slotCheckAndClose()
	{
		accept();
	}

	void LogDialog::initComboBox()
	{
		QDir dir(QCoreApplication::applicationDirPath() + "/logs");//当前文件路径
		QString filtername = "*.txt";
		QStringList filter;
		filter << filtername;
		dir.setNameFilters(filter);
		QStringList Neuronindex = dir.entryList();
		ui->comboBoxSelect->addItems(Neuronindex);//把列表加载到comboBox_3		
	}

	void LogDialog::on_ButtonLoad_clicked()
	{
		QStringList lines;
		QString txtname = ui->comboBoxSelect->currentText();
		QFile file(QCoreApplication::applicationDirPath() + "/logs/" + txtname);
		//QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
		if (file.open(QFile::ReadOnly)) 
		{
			int i = 0;
			QTextStream stream(&file);
			QString line;
			int n = 1;
			while (!stream.atEnd()) 
			{
				line = stream.readLine(); // 不包括“\n”的一行文本
				ui->textBrowser->append(line.at(i));
				i++;
				lines += line;
			}
			file.close();
		}

	}

}  // namespace vtk::display
