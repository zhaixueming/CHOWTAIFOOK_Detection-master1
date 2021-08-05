#include "vimocommon.h"
#include <QProcess>
#include <QTextCodec>
#include <memory>

namespace vimo::common
{
QImage matToQImage(const cv::Mat &mat)
{
    QImage image;
    auto channels = mat.channels();
    if (channels == 3)  // RGB image
    {
        image = QImage((const uchar *)(mat.data), mat.cols, mat.rows, mat.cols * mat.channels(), QImage::Format_RGB888)
                    .rgbSwapped();
    }
    else if (channels == 4)  // RGBA image
    {
        image = QImage((const uchar *)(mat.data), mat.cols, mat.rows, mat.cols * mat.channels(), QImage::Format_RGB32);
    }
    else  // gray image
    {
        image =
            QImage((const uchar *)(mat.data), mat.cols, mat.rows, mat.cols * mat.channels(), QImage::Format_Indexed8);
    }
    return image;
}

std::string utf8ToGbk(const QString &utf8_str)
{
    QTextCodec *gbk_code = QTextCodec::codecForName("GBK");
    QTextCodec *utf8_code = QTextCodec::codecForName("UTF-8");
    QString unicode_str = utf8_code->toUnicode(utf8_str.toLocal8Bit().data());
    return std::string(gbk_code->fromUnicode(unicode_str).data());
}

bool containsChineseSpecial(QString qstr)
{
    if (qstr.contains(QRegExp(QStringLiteral("？|。|，|·|！|￥|……|（|）|【|】|《|》|“|”|‘|’|：|；|、|—"))))
        return true;
    return false;
}

bool containsAllSpecial(QString qstr)
{
    std::string str = qstr.toStdString();
    if (containsSpecial(str))
        return true;
    else
        return containsChineseSpecial(qstr);
}

bool containsSpecial(std::string str)
{
    std::string tmp;
    int badNum = 0;

    int size = str.length();
    if (size <= 0)
        return true;

    std::wstring wstr;
    wstr.assign(str.begin(), str.end());
    wchar_t *wcstr = (wchar_t *)wstr.c_str();

    for (int i = 0; i < size; i++)
    {
        if (iswpunct(wcstr[i]))
        {
            badNum++;
        }
    }

    if (badNum > 0)
    {
        return true;
    }
    else
        return false;
}

bool isIpReachable(const QString &ip, int wait_ms)
{
    QProcess process;
#ifdef Q_OS_WIN
    process.start(QString("ping %1 -n 1 -w %2").arg(ip).arg(wait_ms));
#else
    int second = wait_ms / 1000;
    second = (second == 0) ? 1 : second;
    process.start(QString("ping %1 -c 1 -W %2").arg(ip).arg(second));  // linux ping参数不同
#endif
    process.waitForReadyRead();
    process.waitForFinished();
    auto ret = process.readAll();
#ifdef Q_OS_WIN
    return (ret.indexOf("TTL") != -1);
#else
    return (ret.indexOf("ttl") != -1);
#endif
}

}  // namespace vimo::common
