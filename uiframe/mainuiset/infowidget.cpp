/****************************************************************************
 *  @file
 *  @brief
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "infowidget.h"
#include "ui_infowidget.h"
#include <QStyle>

namespace vimo::display
{
	InfoWidget::InfoWidget(QWidget *parent) : QWidget(parent), ui(new Ui::InfoWidget)
	{
		ui->setupUi(this);
		
		update();
	}

	InfoWidget::~InfoWidget()
	{
		delete ui;
	}


}  // namespace vtk::display
