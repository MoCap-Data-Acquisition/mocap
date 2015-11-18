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
      widgets

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
    borderlayout.h \
    GraphicsVlcItem.h
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
    borderlayout.cpp \
    GraphicsVlcItem.cpp

maemo* {
    DEFINES += PLAYER_NO_COLOROPTIONS
}

unix:!macx {
    LIBS       += -lVLCQtCore -lVLCQtWidgets
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
    pointtracker.ui

win32 {
    CONFIG(release, debug|release): LIBS += -L$$PWD/../../Downloads/vlcqt/bin/ -llibVLCQtCore -llibVLCQtWidgets
    CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Downloads/vlcqt/bin/ -llibVLCQtCored -llibVLCQtWidgetsd

    INCLUDEPATH += $$PWD/../../Downloads/vlcqt/include
    DEPENDPATH += $$PWD/../../Downloads/vlcqt/include
}
