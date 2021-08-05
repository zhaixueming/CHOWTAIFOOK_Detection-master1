/****************************************************************************
 *  @file     imageview.cpp
 *  @brief    图像视窗类
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "imageview.h"
#include "vimocommon/vimocommon.h"
#include "ui_imageview.h"
#include "viewtoolbar.h"
#include <QKeyEvent>

namespace vimo::display
{
using namespace vimo::common;

ImageView::ImageView(QWidget *parent) : QWidget(parent), ui(new Ui::ImageView)
{
    init();
}

ImageView::~ImageView()
{
    delete ui;
}

void ImageView::setViewInfo(const ImageView::ViewInfo &info)
{
    m_view_info = info;
    m_view_tool_bar->setViewInfo(m_view_info);
}

const ImageView::ViewInfo &ImageView::getViewInfo() const
{
    return m_view_info;
}

void ImageView::updateViewStatusDisplay(const ImageView::ViewInfo &info)
{
    size_t total_times{0};
}

void ImageView::updateImageDisplay(const QImage image, bool revert)
{  
    ui->image_graphics_view->setImage(image, revert);
}

void ImageView::keyPressEvent(QKeyEvent *e)
{
    if (ui->image_view->hasFocus()&&(e->modifiers() == Qt::ControlModifier&& e->key() == Qt::Key_0))
        ui->image_graphics_view->revertImage();
}

void ImageView::init()
{
    initWidgets();
    initConnects();
}

void ImageView::initWidgets()
{
    ui->setupUi(this);
    m_view_tool_bar = new ViewToolBar;
    ui->toolbar_layout->addWidget(m_view_tool_bar);   
}

void ImageView::initConnects()
{
    connect(m_view_tool_bar, &ViewToolBar::signalChangeDisplayImageType, this, [&](bool is_ai_image) {
        m_is_ai_image = is_ai_image;
        auto image = (m_is_ai_image && !m_ai_image.empty()) ? vimo::common::matToQImage(m_ai_image) :
                                                              vimo::common::matToQImage(m_src_image);
        ui->image_graphics_view->setImage(image, false);
    });
    connect(m_view_tool_bar, &ViewToolBar::signalZoomoutImage, this, [&] { ui->image_graphics_view->zoomoutImage(); });
    connect(m_view_tool_bar, &ViewToolBar::signalZoominImage, this, [&] { ui->image_graphics_view->zoominImage(); });
    connect(m_view_tool_bar, &ViewToolBar::signalRevertImage, this, [&] { ui->image_graphics_view->revertImage(); });
    connect(ui->image_graphics_view, &ImageGraphicsView::signalClicked, this,
            [&]{ui->image_view->setFocus();});
    connect(ui->image_graphics_view, &ImageGraphicsView::signalUpdateFactor, this,
            [&](float factor) { m_view_tool_bar->setScalefactor(factor * 100); });
}

}  // namespace vimo::display
