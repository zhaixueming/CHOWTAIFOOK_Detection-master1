/****************************************************************************
 *  @file     thresholddialog.h
 *  @brief    阈值设置界面
 *  @author
 *  @email
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef STEREOSCOPICDIALOG_H
#define STEREOSCOPICDIALOG_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QDialog>
#include <QLabel>
#include <QWidget>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QFile>
#include <QFileDialog>
#include "configtitlebar.h"
#include "threshold.h"

namespace Ui
{
    class StereoscopicDialog;
}

namespace vimo::display
{
    class StereoscopicDialog : public QDialog
    {
        Q_OBJECT

      public:
        explicit StereoscopicDialog(QWidget *parent = nullptr);
        ~StereoscopicDialog();

      signals:
        void progressordersignals(int value);
      private slots:
        void slotCheckAndClose();
        //保存按钮
        void on_ButtonSave_clicked();
        //取消按钮
        void on_pushButtonCancel_clicked();

		public:
        ThresholdParam GetSystemParamFromFile(std::string path);

      private:
        void initWidgets();
        void ReadingData();
        //ThresholdParam _thresholdparam;
        void SaveThreshold();
      private:
        Ui::StereoscopicDialog *ui;
        ConfigTitleBar *m_titleBar{nullptr};
        
    };
} // namespace vimo::display
#endif // CONFIGDIALOG_H
