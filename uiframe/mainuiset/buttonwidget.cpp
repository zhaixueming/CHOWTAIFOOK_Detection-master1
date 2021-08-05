/****************************************************************************
 *  @file     buttonwidget.cpp
 *  @brief    首页功能按钮界面
 *  @author   
 *  @email    
 *  @version
 *  @date     
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "buttonwidget.h"
#include "ui_buttonwidget.h"
#include "uiframe/configuiset/adminlogindialog.h"
//#include "uiframe/configuiset/materialsetdialog.h"
//#include "uiframe/configuiset/ordersetdialog.h"
//#include "uiframe/configuiset/camsetdialog.h"
#include "uiframe/configuiset/configdialog.h"
#include "uiframe/configuiset/logdialog.h"
#include <QStyle>

namespace vimo::display
{
	ButtonWidget::ButtonWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ButtonWidget)
	{
		init();
	}

	ButtonWidget::~ButtonWidget()
	{
		delete ui;
	}

	void ButtonWidget::init()
	{
		initWidgets();		
	}

	void ButtonWidget::initWidgets()
	{
		ui->setupUi(this);
	}
	void ButtonWidget::on_login_btn_clicked()
	{
		adminLoginDialog adminDlg;
		adminDlg.exec();
		int adminctrl = adminDlg.adminctrl;
		emit this->adminsignal(adminctrl);
	}

	void ButtonWidget::on_material_btn_clicked()
	{					
		//emit this->materialsignal();
	}

	void ButtonWidget::on_order_btn_clicked()
	{		
		/*OrderSetDialog ordersetdialog;
		ordersetdialog.exec();	
		emit this->ordersignal();		*/
	}

	void ButtonWidget::on_cam_btn_clicked()
	{
		emit this->banshow(false);
		//emit this->camsignal();
	}

	void ButtonWidget::on_parameter_btn_clicked()
	{
		ConfigDialog config_dialog;
		config_dialog.exec();
		emit this->configsignal();
	}

	void ButtonWidget::on_log_btn_clicked()
	{
		LogDialog logdialog;
		logdialog.exec();
	}

	void ButtonWidget::adminload()
	{
		on_login_btn_clicked();
	}

	void ButtonWidget::buttonopen()
	{
		/*ui->material_btn->setEnabled(true);
		ui->material_btn->setDisabled(false);
		ui->material_btn->setStyleSheet("background: #006DB2;");

		ui->order_btn->setEnabled(true);
		ui->order_btn->setDisabled(false);
		ui->order_btn->setStyleSheet("background: #006DB2;");*/

		ui->cam_btn->setEnabled(true);
		ui->cam_btn->setDisabled(false);
		ui->cam_btn->setStyleSheet("background: #006DB2;");

		ui->parameter_btn->setEnabled(true);
		ui->parameter_btn->setDisabled(false);
		ui->parameter_btn->setStyleSheet("background: #006DB2;");
	}

	void ButtonWidget::buttonclose()
	{
		/*ui->material_btn->setEnabled(false);
		ui->material_btn->setDisabled(true);
		ui->material_btn->setStyleSheet("background: #808A87;");

		ui->order_btn->setEnabled(false);
		ui->order_btn->setDisabled(true);
		ui->order_btn->setStyleSheet("background: #808A87;");*/

		ui->cam_btn->setEnabled(false);
		ui->cam_btn->setDisabled(true);
		ui->cam_btn->setStyleSheet("background: #808A87;");

		ui->parameter_btn->setEnabled(false);
		ui->parameter_btn->setDisabled(true);
		ui->parameter_btn->setStyleSheet("background: #808A87;");

	}

	void ButtonWidget::changeEvent(QEvent *e)  //重写的事件处理方法
	{
		QWidget::changeEvent(e);  //让基类执行事件处理方法
		switch (e->type())
		{
		case QEvent::LanguageChange:  //如果是语言改变事件
			if (ui)
			{
				ui->retranslateUi(this);  //更新UI的语言			
			}
			break;
		default:
			break;
		}
	}

}  // namespace vtk::display
