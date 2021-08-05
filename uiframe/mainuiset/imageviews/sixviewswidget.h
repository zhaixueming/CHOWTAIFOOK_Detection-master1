/****************************************************************************
 *  @file     sixviewswidget.h
 *  @brief    六图像视窗框架类
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef SIXVIEWSWIDGET_H
#define SIXVIEWSWIDGET_H

#include "imageview.h"
#include <QWidget>

namespace Ui
{
class SixViewsWidget;
}

namespace vimo::display
{

class SixViewsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SixViewsWidget(const std::vector<ImageView::ViewInfo> &info_list, QWidget *parent = nullptr);
    ~SixViewsWidget();

	void updateImage1(QImage Image);
	void updateImage2(QImage Image);
	void updateImage3(QImage Image);
	void updateImage4(QImage Image);
	void updateImage5(QImage Image);
	void updateImage6(QImage Image);

private:
    Ui::SixViewsWidget *ui;
};
}  // namespace vtk::display
#endif  // FOURVIEWSWIDGET_H
