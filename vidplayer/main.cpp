#include "player.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFileInfo>

int main(int argc, char *argv[])
{
#ifdef Q_OS_DARWIN
    QApplication::addLibraryPath(QFileInfo(argv[0]).absoluteDir().absolutePath() + "/../PlugIns");
#endif
    qDebug() << QApplication::libraryPaths();
    QApplication app(argc, argv);
    MainWindow w;
//    w.setWindowFlags(Qt::CustomizeWindowHint
//                     | Qt::WindowCloseButtonHint);
    w.showMaximized();
//    w.show();
    //Player player;

//#if defined(Q_WS_SIMULATOR)
//    player.setAttribute(Qt::WA_LockLandscapeOrientation);
//    player.showMaximized();
//#else
//    player.show();return app.exec();
//#endif
    return app.exec();
}
