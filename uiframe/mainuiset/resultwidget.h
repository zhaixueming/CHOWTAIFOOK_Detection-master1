/****************************************************************************
 *  @file     
 *  @brief    
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QWidget>
#include <QtDebug>
#include <QFileDialog>
#include "buttonwidget.h"
#include "uiframe/commonuiset/messagedialog/messagedialog.h"

namespace Ui
{
class ResultWidget;
}

namespace vimo::display
{

class ResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResultWidget(QWidget *parent = nullptr);
    ~ResultWidget();
	//初始化下拉框
	void initComboBox();
	//重置下拉框
	void refreshcombobox();
private slots:
	//加载
	void on_ButtonLoad_clicked();
	//显示信息
	void showformula(QString name, QString num);

signals:
	//发送选择信息
	void formulasignal(QString sendpath);

private:
    Ui::ResultWidget *ui;
	ButtonWidget *m_button_widget{ nullptr };
};
}  // namespace vtk::display
#endif  // OPERATIONALCONTROLWIDGET_H
