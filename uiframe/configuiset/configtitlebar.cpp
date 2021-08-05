/****************************************************************************
 *  @file     configtitlebar.cpp
 *  @brief    设置窗口标题栏类
 *  @author
 *  @email
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "configtitlebar.h"
#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QFile>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QToolButton>

namespace vimo::display
{

#define BUTTON_HEIGHT 20  // 按钮高度;
#define BUTTON_WIDTH 20  // 按钮宽度;
#define TITLE_HEIGHT 30  // 标题栏高度;

ConfigTitleBar::ConfigTitleBar(QWidget *parent)
    : QWidget(parent), m_colorR(153), m_colorG(153), m_colorB(153), m_isPressed(false), m_windowBorderWidth(0)
{
    init();
}

void ConfigTitleBar::init()
{
    m_pIcon = new QLabel;
    m_pTitleContent = new QLabel;

    m_pTitleContent->setObjectName("TitleContent");
    m_pTitleContent->setAlignment(Qt::AlignCenter);
    m_pTitleContent->setStyleSheet("color: rgba(0,0,0,0.8);");
    m_pTitleContent->setText(tr("Settings"));
    QFont font("PingFang SC Medium");
    font.setPixelSize(16);
    m_pTitleContent->setFont(font);
    m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QToolButton *close_button = new QToolButton;
    close_button->setFixedSize(16, 16);
    close_button->setStyleSheet("border: 0px; background: url(\":/uiframe/images/config/close.svg\");");
    close_button->setCursor(Qt::PointingHandCursor);
    connect(close_button, &QToolButton::clicked, this, &ConfigTitleBar::signalClose);

    QHBoxLayout *mylayout = new QHBoxLayout(this);
    mylayout->addWidget(m_pTitleContent);
    mylayout->addWidget(close_button);
    mylayout->setSpacing(0);
    mylayout->setContentsMargins(26, 0, 10, 0);

    this->setFixedWidth(1100);
    this->setFixedHeight(TITLE_HEIGHT);
    this->setWindowFlags(Qt::FramelessWindowHint);

    setBackgroundColor(233, 238, 242);
}

void ConfigTitleBar::setBackgroundColor(int r, int g, int b)
{
    // 标题栏背景色;
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;

    update();
}

void ConfigTitleBar::setTitleIcon(QString filePath, QSize IconSize)
{
    QPixmap titleIcon(filePath);
    m_pIcon->setPixmap(titleIcon.scaled(IconSize));
}

void ConfigTitleBar::setTitleContent(QString titleContent)
{
    m_pTitleContent->setText(titleContent);
    m_titleContent = titleContent;
}

void ConfigTitleBar::setTitleWidth(int width)
{
    this->setFixedWidth(width);
}

void ConfigTitleBar::setWindowBorderWidth(int borderWidth)
{
    m_windowBorderWidth = borderWidth;
}

void ConfigTitleBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));
    if (this->width() != (this->parentWidget()->width() - m_windowBorderWidth))
    {
        this->setFixedWidth(this->parentWidget()->width() - m_windowBorderWidth);
    }

    QWidget::paintEvent(event);
}

}  // namespace vimo::display
