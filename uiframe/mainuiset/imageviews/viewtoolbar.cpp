/****************************************************************************
 *  @file     viewtoolbar.cpp
 *  @brief    图像视窗工具条类
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "viewtoolbar.h"
#include "vimocommon/vimocommon.h"
#include "ui_viewtoolbar.h"
#include <QFileDialog>
#include <QStyle>
#include <QTextCodec>

namespace vimo::display
{
using CameraState = vimo::common::CameraState;
using ImageListForwarder = vimo::common::ImageListForwarder;

ViewToolBar::ViewToolBar(QWidget *parent) : QWidget(parent), ui(new Ui::ViewToolBar)
{
    init();
}

ViewToolBar::~ViewToolBar()
{
    delete ui;
}

void ViewToolBar::setViewInfo(const ImageView::ViewInfo &info)
{
    m_view_info = info;
    ui->view_name_lab->setText(m_view_info.view_name);
    QFontMetrics font_width(ui->view_name_lab->font());
    QString elide_note = font_width.elidedText(m_view_info.view_name, Qt::ElideRight, 80);

    ui->view_name_lab->setText(elide_note);
    if (elide_note != m_view_info.view_name)
        ui->view_name_lab->setToolTip(m_view_info.view_name);

    updateDeviceIcon();
    updateCameraStatus();
}

void ViewToolBar::setScalefactor(int factor)
{
    ui->scale_factor_lab->setText(QString("%1%").arg(static_cast<size_t>(factor)));
}

void ViewToolBar::init()
{
    initWidgets();
    initConnects();
}

void ViewToolBar::initWidgets()
{
    ui->setupUi(this);
    updateDeviceIcon();
    updateCameraStatus();
}

void ViewToolBar::initConnects()
{
}

void ViewToolBar::updateCameraStatus()
{
}

void ViewToolBar::updateCameraStatus(CameraState state)
{
    switch (state)
    {
        case CameraState::disconnect:
            ui->camera_status_lab->setProperty("camera_status", "disconnect");
            break;
        case CameraState::opening:
            ui->camera_status_lab->setProperty("camera_status", "open");
            break;
        case CameraState::closed:
            ui->camera_status_lab->setProperty("camera_status", "close");
            break;
    }
    style()->polish(ui->camera_status_lab);
}

void ViewToolBar::updateDeviceIconToolTip()
{
    
}

void ViewToolBar::updateDeviceIcon()
{
    
    updateDeviceIconToolTip();

    style()->polish(ui->camera_status_lab);
}

void ViewToolBar::on_zoomout_btn_clicked()
{
    emit signalZoomoutImage();
}

void ViewToolBar::on_zoomin_btn_clicked()
{
    emit signalZoominImage();
}

void ViewToolBar::on_revert_btn_clicked()
{
    emit signalRevertImage();
}

void ViewToolBar::changeEvent(QEvent *e)  //重写的事件处理方法
{
    QWidget::changeEvent(e);  //让基类执行事件处理方法
    QString name;
    switch (e->type())
    {
        case QEvent::LanguageChange:  //如果是语言改变事件
            if (ui)
                ui->retranslateUi(this);  //更新UI的语言
            updateDeviceIconToolTip();
            break;
        default:
            break;
    }
}

}  // namespace vimo::display
