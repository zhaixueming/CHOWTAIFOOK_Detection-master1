/****************************************************************************
 *  @file     vimocommon.h
 *  @brief    vimo通用函数实现文件
 *  @author   junjie.zeng
 *  @email    junjie.zeng@smartmore.com
 *  @version
 *  @date     2020.11.13
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/

#pragma once
//#include "applogger.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QSettings>
#include <QUuid>
#include <memory>
#include <opencv2/opencv.hpp>

namespace vimo::common
{
    enum class CameraState
    {
        disconnect = 0,  //相机断开状态
        closed,          //相机关闭状态
        opening          //相机打开状态
    };

    enum class AlgoType
    {
        noType = 0,
        segmentationType,    // 分割类型
        detectionType,       // 检测类型
        classificationType,  // 分类类型
        ocrType              // OCR类型
    };

    enum class ResultStatusType
    {
        notProcessed = -1,
        notAvailable = 0,
        ok = 1,
        ng = 2,
    };

    class Message : public QObject
    {
        Q_OBJECT
    public:
        enum MessageType
        {
            info = 0,
            warning,
            error
        };

        static Message &getInstance()
        {
            static Message s_message;
            return s_message;
        }
        static void postInfoMessage(const QString &title, const QString &msg)
        {
            emit getInstance().signalPostMessage(title, msg, MessageType::info);
        }

        static void postWarningMessage(const QString &title, const QString &msg)
        {
            emit getInstance().signalPostMessage(title, msg, MessageType::warning);
        }

        static void postErrorMessage(const QString &title, const QString &msg)
        {
            emit getInstance().signalPostMessage(title, msg, MessageType::error);
        }

    signals:
        void signalPostMessage(const QString &title, const QString &msg, vimo::common::Message::MessageType type);

    private:
        Message()
        {
            qRegisterMetaType<vimo::common::Message::MessageType>("vimo::common::Message::MessageType");
        }
    };

    class ImageListForwarder : public QObject
    {
        Q_OBJECT
    public:
        struct ImageInfo
        {
            QString image_path;
            QUuid image_uuid;
        };
        static ImageListForwarder &getInstance()
        {
            static ImageListForwarder s_forwarder;
            return s_forwarder;
        }

    signals:
        void signalPostImageListInfo(const QUuid &view_uuid, const QList<ImageInfo> &image_info_list);

    private:
        ImageListForwarder() = default;
    };

    class CameraStatusGetter : public QObject
    {
        Q_OBJECT
    public:
        static CameraStatusGetter &getInstance()
        {
            static CameraStatusGetter s_getter;
            return s_getter;
        }

    signals:
        bool signalGetCameraStatus(const QString &camera_name);

    private:
        CameraStatusGetter() = default;
    };

    using AlgoHandle = int;

    bool isIpReachable(const QString &ip, int wait_ms);

    /**
     * @brief matToQImage  cv::mat格式图片转QImage格式图片
     * @param mat          输入cv::mat格式图片
     * @return             输出QImage格式图片
     */
    QImage matToQImage(const cv::Mat &mat);

    /**
     * @brief utfToGbk     utf8编码转gbk编码
     * @param              输入utf8编码的QString
     * @return             输出gbk编码的std:string
     */
    std::string utf8ToGbk(const QString &);

    /**
     * @brief containsChineseSpecial     检查字符串是否含有中文特殊字符
     * @param              输入 QString
     * @return             输出 bool
     */
    bool containsChineseSpecial(QString);

    /**
     * @brief containsSpecial     检查字符串是否含有特殊字符（不包括中文字符）
     * @param              输入 std::string
     * @return             输出 bool
     */
    bool containsSpecial(std::string);

    /**
     * @brief containsAllSpecial     检查字符串是否含有特殊字符（包括中文字符）
     * @param              输入 QString
     * @return             输出 bool
     */
    bool containsAllSpecial(QString);

}  // namespace vimo::common
Q_DECLARE_METATYPE(vimo::common::CameraState);
