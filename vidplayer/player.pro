#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T18:45:22
#
#-------------------------------------------------
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TEMPLATE = app
TARGET = player

CONFIG += c++11

QT += network \
      xml \
      multimedia \
      multimediawidgets \
      widgets \
      webkit \
      webkitwidgets

HEADERS = \
    player.h \
    playercontrols.h \
    videowidget.h \
    qcustomplot.h \
    mainwindow.h \
    plotwindow.h \
    pointstruct.h \
    pointtocsv.h \
    pointtracker.h \
    GraphicsVlcItem.h \
    helpmenu.h
SOURCES = main.cpp \
    player.cpp \
    playercontrols.cpp \
    videowidget.cpp \
    qcustomplot.cpp \
    mainwindow.cpp \
    plotwindow.cpp \
    pointstruct.cpp \
    pointtocsv.cpp \
    pointtracker.cpp \
    GraphicsVlcItem.cpp \
    helpmenu.cpp

maemo* {
    DEFINES += PLAYER_NO_COLOROPTIONS
}

unix:!macx {
    LIBS       += -lVLCQtCore -lVLCQtWidgets
    INCLUDEPATH += ~/Documents/programming/C++/vlc-qt-build/include
    INCLUDEPATH += ~/Documents/programming/C++/vlc-qt-build/src
}

macx {
    QMAKE_CXXFLAGS += -F/Library/Frameworks
    QMAKE_LFLAGS += -F/Library/Frameworks
    LIBS += -framework VLCQtCore -framework VLCQtWidgets

    QMAKE_RPATHDIR += /usr/local/lib
}

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/player
INSTALLS += target

FORMS += \
    mainwindow.ui \
    plotwindow.ui \
    pointtracker.ui \
    helpmenu.ui

win32 {
    CONFIG(release, debug|release): LIBS += -L$$PWD/../../Downloads/vlcqt/bin/ -llibVLCQtCore -llibVLCQtWidgets
    CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Downloads/vlcqt/bin/ -llibVLCQtCored -llibVLCQtWidgetsd

    INCLUDEPATH += $$PWD/../../Downloads/vlcqt/include
    DEPENDPATH += $$PWD/../../Downloads/vlcqt/include
}
