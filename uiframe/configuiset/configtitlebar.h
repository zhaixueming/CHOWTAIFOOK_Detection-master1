/****************************************************************************
 *  @file     configtitlebar.h
 *  @brief    设置窗口标题栏类
 *  @author
 *  @email
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#pragma once
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

namespace vimo::display
{

class ConfigTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigTitleBar(QWidget *parent = 0);

    //设置标题栏背景色
    void setBackgroundColor(int r, int g, int b);
    //设置标题栏图标
    void setTitleIcon(QString filePath, QSize IconSize = QSize(25, 25));
    //设置标题栏内容
    void setTitleContent(QString titleContent);
    //设置标题栏长度
    void setTitleWidth(int width);
    // 设置窗口边框宽度;
    void setWindowBorderWidth(int borderWidth);

signals:
    void signalClose();

private:
    void paintEvent(QPaintEvent *event);

    //控件初始化
    void init();

public:
    QLabel *m_pIcon{nullptr};          // 标题栏图标;
    QLabel *m_pTitleContent{nullptr};  // 标题栏内容;

    // 标题栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

    // 移动窗口的变量;
    bool m_isPressed;
    QPoint m_startMovePos;

    // 标题栏内容;
    QString m_titleContent;

    // 窗口边框宽度;
    int m_windowBorderWidth;
};
}  // namespace vimo::display
