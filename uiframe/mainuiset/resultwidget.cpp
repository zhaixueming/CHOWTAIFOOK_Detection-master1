/****************************************************************************
 *  @file
 *  @brief
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "resultwidget.h"
#include "ui_resultwidget.h"
#include <QStyle>

namespace vimo::display
{
	ResultWidget::ResultWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ResultWidget)
	{
		ui->setupUi(this);
		initComboBox();
	}

	ResultWidget::~ResultWidget()
	{
		delete ui;
	}

	//获取全部信息加载在comboBoxRecord中
	void ResultWidget::initComboBox()
	{
		
	}

	void ResultWidget::refreshcombobox()
	{
		
	}

	void ResultWidget::on_ButtonLoad_clicked()
	{
		
	}

	void ResultWidget::showformula(QString name, QString num)
	{
		
	}

}  // namespace vtk::display
