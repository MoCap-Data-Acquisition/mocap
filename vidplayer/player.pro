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
    playlistmodel.h \
    videowidget.h \
    qcustomplot.h \
    mainwindow.h \
    plotwindow.h \
    pointstruct.h \
    pointtocsv.h
SOURCES = main.cpp \
    player.cpp \
    playercontrols.cpp \
    playlistmodel.cpp \
    videowidget.cpp \
    qcustomplot.cpp \
    mainwindow.cpp \
    plotwindow.cpp \
    pointstruct.cpp \
    pointtocsv.cpp

maemo* {
    DEFINES += PLAYER_NO_COLOROPTIONS
}

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/player
INSTALLS += target

FORMS += \
    mainwindow.ui \
    plotwindow.ui
