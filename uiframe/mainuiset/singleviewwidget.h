/****************************************************************************
 *  @file     singleviewwidget.h
 *  @brief    单图像视窗框架类
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef SINGLEVIEWWIDGET_H
#define SINGLEVIEWWIDGET_H

#include "uiframe/mainuiset/imageviews/imageview.h"
#include <QWidget>

namespace Ui
{
class SingleViewWidget;
}

namespace vimo::display
{

class SingleViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleViewWidget(const std::vector<ImageView::ViewInfo> &info_list, QWidget *parent = nullptr);
    ~SingleViewWidget();

	void updateImage(const QImage image);

private:
    Ui::SingleViewWidget *ui;
};
}  // namespace vtk::display
#endif  // SINGLEVIEWWIDGET_H
