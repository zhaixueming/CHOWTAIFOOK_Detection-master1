/****************************************************************************
 *  @file     datawidget.h
 *  @brief    列表类
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>

namespace Ui
{
class DataWidget;
}

namespace vimo::display
{

class DataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataWidget(const QString &title = "", QWidget *parent = nullptr);
    ~DataWidget();
    void setTitle(QString);
    void setHeader(QStringList);

private:
    void init();
    void initWidgets();
    void initConnects();

private:
    Ui::DataWidget *ui;
    QString m_title;
};
}  // namespace vimo::display
#endif  // LOGWIDGET_H
