#include "uiframe/mainuiset/mainframe.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // ===================== 界面样式 =====================
    QFile styleFile("://uiframe/style/stylesheet.qss");
    styleFile.open(QFile::ReadOnly);
    QString style = QString::fromUtf8(styleFile.readAll());
    app.setStyleSheet(style);
    styleFile.close();
    // ========================================================

    vimo::display::MainFrame w;

    // ===================== 支持中文、英文 =====================
    QTranslator translator;
    int lang = 0;
    if (lang)
        translator.load("://uiframe/translations/smore_vimo_en.qm");
    else
        translator.load("://uiframe/translations/smore_vimo_zh-cn.qm");
    qApp->installTranslator(&translator);
    w.setTranslator(&translator);
    // ========================================================

    // ===================== 设置图标 =====================
    qApp->setWindowIcon(QIcon("://uiframe/images/logo.ico"));
    // ========================================================

    w.show();
    auto result = app.exec();
    return result;
}
