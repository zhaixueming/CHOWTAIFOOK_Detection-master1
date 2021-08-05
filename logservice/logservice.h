/****************************************************************************
 *  @file     logger.h
 *  @brief    运行日志
 *  @author   xiaoyu.liu
 *  @email    xiaoyu.liu@smartmore.com
 *  @version
 *  @date     2020-12-28
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/

#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <list>

namespace vimo::logservice
{

enum class LogLevel
{
    Error,
    Info,
    Warning
};

enum class LogSource
{
    AI,
    Camera,
    Others
};

struct LogType
{
    LogLevel level;
    LogSource source;
};

class LogFilter
{
public:
    LogFilter()
    {
        m_filter_mode = None;
    }

    LogFilter(LogLevel level)
    {
        m_filter_mode = Level;
        m_type.level = level;
    }

    LogFilter(LogSource source)
    {
        m_filter_mode = Source;
        m_type.source = source;
    }

    bool contains(const LogType &type)
    {
        return m_filter_mode == None || (m_filter_mode == Level && m_type.level == type.level) ||
               (m_filter_mode == Source && m_type.source == type.source);
    }

    QString toString();

private:
    enum
    {
        None,
        Level,
        Source
    } m_filter_mode;
    LogType m_type;
};

struct LogItem
{
    QString ctime;
    LogType type;
    QString content;
};

class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger &getInstance()
    {
        static Logger logger;
        return logger;
    }

    void appendLog(LogType type, QString content);
    void setFilter(LogFilter filter);
    void exportToFile(QString file_path);
    QString getDefaultLogName();

signals:
    void signalAppendLog(const LogItem &item);
    void signalReloadLog(const std::list<LogItem *> &logs);

public:
    Logger() = default;

    LogFilter m_filter;
    std::list<LogItem> m_tlogs;
    std::list<LogItem *> m_clogs;
};

}  // namespace vimo::logservice

Q_DECLARE_METATYPE(vimo::logservice::LogItem);

#endif  // LOGGER_H
