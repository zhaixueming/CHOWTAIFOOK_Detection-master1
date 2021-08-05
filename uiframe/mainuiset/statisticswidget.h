/****************************************************************************
 *  @file     statisticswidget.h
 *  @brief    统计显示窗口类
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>

namespace Ui
{
    class StatisticsWidget;
}

namespace vimo::display
{

class StatisticsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWidget(QWidget *parent = nullptr);
    ~StatisticsWidget();

private:
    void init();
    void initWidgets();
    void initConnects();  
	void resetStatisticsResult();
    void changeEvent(QEvent *e);

public:
	void updatecount(int count);
	void updateorder(int order);
	void updateResult();
	
private:
    Ui::StatisticsWidget *ui;
    size_t m_total_counts{0};
    size_t m_ng_counts{0};
    size_t m_ok_counts{0};
    float m_pass_percent{0.0000f};

	int order_counts = 0;
	//int update_counts = 0;
	int counts = 0;
	float update_pass_percent = 0;
};
}  // namespace vimo::display
#endif  // STATISTICSWIDGET_H
