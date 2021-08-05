/****************************************************************************
 *  @file     logdialog.h
 *  @brief    料单设置界面
 *  @author
 *  @email
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QWidget>
#include <qstring.h>
#include <QFile>
#include <qtextstream.h>
#include <qtextcodec.h>

#include "configtitlebar.h"

namespace Ui
{
	class LogDialog;
}

namespace vimo::display
{
	class LogDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit LogDialog(QWidget *parent = nullptr);
		~LogDialog();

	private slots:
		void slotCheckAndClose();
		void on_ButtonLoad_clicked();

	private:
		void initWidgets();
		void initComboBox();
		
	private:
		Ui::LogDialog *ui;
		ConfigTitleBar *m_titleBar{ nullptr };
		QString m_title;
	};
}  // namespace vtk::display
#endif  // CONFIGDIALOG_H
