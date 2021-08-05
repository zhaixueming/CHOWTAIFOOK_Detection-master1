/****************************************************************************
 *  @file     statisticswidget.cpp
 *  @brief    统计显示窗口类
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "statisticswidget.h"
#include "ui_statisticswidget.h"

namespace vimo::display
{
	StatisticsWidget::StatisticsWidget(QWidget *parent) : QWidget(parent), ui(new Ui::StatisticsWidget)
	{
		init();
	}

	StatisticsWidget::~StatisticsWidget()
	{
		delete ui;
	}

	void StatisticsWidget::init()
	{
		initWidgets();
		initConnects();
	}

	void StatisticsWidget::initWidgets()
	{
		ui->setupUi(this);
		resetStatisticsResult();
	}

	void StatisticsWidget::initConnects()
	{
	}

	//统计初始化
	void StatisticsWidget::resetStatisticsResult()
	{
		ui->counts_lab->setText(QString::number(m_ok_counts));
		ui->done_lab->setText(QString::number(m_ng_counts));
		ui->percent_lab->setText(QString::number(m_pass_percent, 'f', 2) + "%");
	}

	//更新数据
	void StatisticsWidget::updatecount(int count)
	{
		counts = count;
		ui->counts_lab->setText(QString::number(count));
	}

	//更新数据
	void StatisticsWidget::updateorder(int order)
	{
		order_counts = order;
		ui->done_lab->setText(QString::number(order));
		update_pass_percent = (float)order_counts / (float)counts;
		ui->percent_lab->setText(QString::number(update_pass_percent * 100, 'f', 2) + "%");
	}

	//更新数据
	void StatisticsWidget::updateResult()
	{
		order_counts++;
		ui->done_lab->setText(QString::number(order_counts));
		update_pass_percent = (float)order_counts / (float)counts;
		ui->percent_lab->setText(QString::number(update_pass_percent * 100, 'f', 2) + "%");
	}

	void StatisticsWidget::changeEvent(QEvent *e)  //重写的事件处理方法
	{
		QWidget::changeEvent(e);  //让基类执行事件处理方法
		switch (e->type())
		{
		case QEvent::LanguageChange:  //如果是语言改变事件
			if (ui)
				ui->retranslateUi(this);  //更新UI的语言
			break;
		default:
			break;
		}
	}
}  // namespace vimo::display
