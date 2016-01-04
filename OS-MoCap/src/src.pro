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
    LIBS       += -lVLCQtCore -lVLCQtWidgets
    INCLUDEPATH += ~/Documents/programming/C++/vlc-qt-build/include
    INCLUDEPATH += ~/Documents/programming/C++/vlc-qt-build/src
}

# OSX
macx {
    QMAKE_CXXFLAGS += -F/Library/Frameworks
    QMAKE_LFLAGS += -F/Library/Frameworks
    LIBS += -framework VLCQtCore -framework VLCQtWidgets

    QMAKE_RPATHDIR += /usr/local/opt/qt5/lib/
    QMAKE_RPATHDIR += @executable_path/../Frameworks
}

# Windows (MINGW)
win32 {
    CONFIG(release, debug|release): LIBS += -L$$PWD/../../Downloads/vlcqt/bin/ -llibVLCQtCore -llibVLCQtWidgets
    CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Downloads/vlcqt/bin/ -llibVLCQtCored -llibVLCQtWidgetsd

    INCLUDEPATH += $$PWD/../../Downloads/vlcqt/include
    DEPENDPATH += $$PWD/../../Downloads/vlcqt/include
}
