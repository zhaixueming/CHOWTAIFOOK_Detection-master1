/****************************************************************************
 *  @file     imageview.h
 *  @brief    图像视窗类
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QUuid>
#include <QWidget>
#include <opencv2/opencv.hpp>

namespace Ui
{
    class ImageView;
}

namespace vimo::display
{
    class ViewToolBar;
    class ViewStatusBar;

    class ImageView : public QWidget
    {
        Q_OBJECT

    public:
        struct ViewInfo
        {
            QUuid view_uuid;
            QString view_name;
        };
        explicit ImageView(QWidget *parent = nullptr);
        ~ImageView();

        void setViewInfo(const ViewInfo &info);
        const ViewInfo &getViewInfo() const;

        void updateViewStatusDisplay(const ViewInfo &info);
        void updateImageDisplay(const QImage image, bool revert);

    signals:
        void signalUpdateThumbnail(const cv::Mat &image);

    protected:
        void keyPressEvent(QKeyEvent *e) override;

    private:
        void init();
        void initWidgets();
        void initConnects();

    private:
        Ui::ImageView *ui;
        ViewToolBar *m_view_tool_bar{nullptr};
        ViewStatusBar *m_view_status_bar{nullptr};
        ViewInfo m_view_info;
        bool m_is_ai_image{true};
        cv::Mat m_ai_image;
        cv::Mat m_src_image;
    };
}  // namespace vimo::display
Q_DECLARE_METATYPE(vimo::display::ImageView::ViewInfo);
#endif  // IMAGEVIEW_H
