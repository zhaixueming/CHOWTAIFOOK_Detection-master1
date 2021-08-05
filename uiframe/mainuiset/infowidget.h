/****************************************************************************
 *  @file     
 *  @brief    
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include <QtDebug>
#include <QImage>
#include <QFileDialog>
#include <QImageReader>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QCoreApplication>

namespace Ui
{
class InfoWidget;
}

namespace vimo::display
{

class InfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InfoWidget(QWidget *parent = nullptr);
    ~InfoWidget();

	
signals:
	void indexsignal(int index);

private:
    Ui::InfoWidget *ui;

};
}  // namespace vtk::display
#endif  // OPERATIONALCONTROLWIDGET_H
