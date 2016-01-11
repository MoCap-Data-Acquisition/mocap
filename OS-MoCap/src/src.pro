#
# Open Source MoCap - Dynamics Trajectory Data Acquisition System
#


TARGET      = OS-MoCap
TEMPLATE    = app
CONFIG 	   += c++11

QT         += widgets \
              printsupport

HEADERS = player.h \
          playercontrols.h \
    	  videowidget.h \
      	  qcustomplot.h \
    	  mainwindow.h \
    	  plotwindow.h \
    	  pointstruct.h \
    	  pointtocsv.h \
    	  pointtracker.h \
    	  GraphicsVlcItem.h \
    	  displayplot.h \
          optionsmenu.h \
          help.h

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
    	  displayplot.cpp \
    optionsmenu.cpp \
    help.cpp

FORMS += mainwindow.ui \
    	 plotwindow.ui \
    	 pointtracker.ui \
         optionsmenu.ui \
         help.ui

maemo* {
    DEFINES += PLAYER_NO_COLOROPTIONS
}

# Linux
unix:!macx {
    LIBS        += -lVLCQtCore -lVLCQtWidgets
    INCLUDEPATH += ./../../vlc-qt-build/include
    INCLUDEPATH += ./../../vlc-qt-build/src
}

# OSX
macx {
    QMAKE_CXXFLAGS += -F/Library/Frameworks
    QMAKE_LFLAGS += -F/Library/Frameworks
    LIBS += -framework VLCQtCore -framework VLCQtWidgets

    QMAKE_RPATHDIR += /usr/local/opt/qt5/lib/
    QMAKE_RPATHDIR += @executable_path/../Frameworks
    ICON = ../../icon/icon.icns
}

# Windows (MINGW)
win32 {
    LIBS += -L$$PWD/../lib/msvc/vlcqt/bin/ -L$$PWD/../lib/msvc/vlcqt/lib/
    CONFIG(release, debug|release): LIBS += -lVLCQtCore -lVLCQtWidgets
    CONFIG(debug, debug|release): LIBS += -lVLCQtCored -lVLCQtWidgetsd

    INCLUDEPATH += $$PWD/../lib/msvc/vlcqt/include
    DEPENDPATH += $$PWD/../lib/msvc/Downloads/vlcqt/include

    RC_FILE = mocap.rc
}
