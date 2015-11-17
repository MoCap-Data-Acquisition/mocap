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
    pointtocsv.h \
    pointtracker.h \
    borderlayout.h \
    Alglib/alglibinternal.h \
    Alglib/alglibmisc.h \
    Alglib/ap.h \
    Alglib/dataanalysis.h \
    Alglib/diffequations.h \
    Alglib/fasttransforms.h \
    Alglib/integration.h \
    Alglib/interpolation.h \
    Alglib/linalg.h \
    Alglib/optimization.h \
    Alglib/solvers.h \
    Alglib/specialfunctions.h \
    Alglib/statistics.h \
    Alglib/stdafx.h
SOURCES = main.cpp \
    player.cpp \
    playercontrols.cpp \
    playlistmodel.cpp \
    videowidget.cpp \
    qcustomplot.cpp \
    mainwindow.cpp \
    plotwindow.cpp \
    pointstruct.cpp \
    pointtocsv.cpp \
    pointtracker.cpp \
    borderlayout.cpp \
    Alglib/alglibinternal.cpp \
    Alglib/alglibmisc.cpp \
    Alglib/ap.cpp \
    Alglib/dataanalysis.cpp \
    Alglib/diffequations.cpp \
    Alglib/fasttransforms.cpp \
    Alglib/integration.cpp \
    Alglib/interpolation.cpp \
    Alglib/linalg.cpp \
    Alglib/optimization.cpp \
    Alglib/solvers.cpp \
    Alglib/specialfunctions.cpp \
    Alglib/statistics.cpp

maemo* {
    DEFINES += PLAYER_NO_COLOROPTIONS
}

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/player
INSTALLS += target

FORMS += \
    mainwindow.ui \
    plotwindow.ui \
    pointtracker.ui
