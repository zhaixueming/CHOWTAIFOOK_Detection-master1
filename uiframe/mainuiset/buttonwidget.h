/****************************************************************************
 *  @file     buttonwidget.h
 *  @brief    首页功能按钮界面
 *  @author   
 *  @email    
 *  @version
 *  @date     
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include <QWidget>

namespace Ui
{
class ButtonWidget;
}

namespace vimo::display
{

class ButtonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonWidget(QWidget *parent = nullptr);
    ~ButtonWidget();

protected:
    void changeEvent(QEvent *e) override;

signals:
	void banshow(bool bshow);
	/*void materialsignal();
	void ordersignal();
	void camsignal();*/
	void configsignal();
	void adminsignal(int adminctrl);
public:
	void adminload();

	void buttonopen();
	void buttonclose();

private slots:
    void on_login_btn_clicked();
    void on_material_btn_clicked();
    void on_order_btn_clicked();
	void on_cam_btn_clicked();
	void on_parameter_btn_clicked();
	void on_log_btn_clicked();

private:
    void init();
    void initWidgets();
    
private:
    Ui::ButtonWidget *ui;
};
}  // namespace vtk::display
#endif  // OPERATIONALCONTROLWIDGET_H
