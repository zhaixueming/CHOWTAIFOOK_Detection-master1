/****************************************************************************
 *  @file     sixviewswidget.cpp
 *  @brief    六图像视窗框架类
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "sixviewswidget.h"
#include "ui_sixviewswidget.h"

namespace vimo::display
{

SixViewsWidget::SixViewsWidget(const std::vector<ImageView::ViewInfo> &info_list, QWidget *parent)
    : QWidget(parent), ui(new Ui::SixViewsWidget)
{
    ui->setupUi(this);
    ui->view1_widget->setViewInfo(info_list.at(0));
    ui->view2_widget->setViewInfo(info_list.at(1));
    ui->view3_widget->setViewInfo(info_list.at(2));
    ui->view4_widget->setViewInfo(info_list.at(3));
	ui->view5_widget->setViewInfo(info_list.at(4));
	ui->view6_widget->setViewInfo(info_list.at(5));
}

SixViewsWidget::~SixViewsWidget()
{
    delete ui;
}

void SixViewsWidget::updateImage1(QImage Image)
{	
	ui->view1_widget->updateImageDisplay(Image, false);
}

void SixViewsWidget::updateImage2(QImage Image)
{
	ui->view2_widget->updateImageDisplay(Image, false);
}

void SixViewsWidget::updateImage3(QImage Image)
{
	ui->view3_widget->updateImageDisplay(Image, false);
}

void SixViewsWidget::updateImage4(QImage Image)
{
	ui->view4_widget->updateImageDisplay(Image, false);
}

void SixViewsWidget::updateImage5(QImage Image)
{
	ui->view5_widget->updateImageDisplay(Image, false);
}

void SixViewsWidget::updateImage6(QImage Image)
{
	ui->view6_widget->updateImageDisplay(Image, false);
}

}  // namespace vtk::display
