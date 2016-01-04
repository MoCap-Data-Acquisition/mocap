#############################################################################
# VLC-Qt - Qt and libvlc connector library - CMake module
# Copyright (C) 2011 Tadej Novak <tadej@tano.si>
# Original author: Rohit Yadav <rohityadav89@gmail.com>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library. If not, see <http://www.gnu.org/licenses/>.
#############################################################################
# If it's found it sets LIBVLCQT_FOUND to TRUE
# and following variables are set:
#  LIBVLCQT_INCLUDE_DIR
#  LIBVLCQT_LIBRARY

# FIND_PATH and FIND_LIBRARY normally search standard locations
# before the specified paths. To search non-standard paths first,
# FIND_* is invoked first with specified paths and NO_DEFAULT_PATH
# and then again with no specified paths to search the default
# locations. When an earlier FIND_* succeeds, subsequent FIND_*s
# searching for the same item do nothing.

# Include dir
FIND_PATH(LIBVLCQT_INCLUDE_DIR vlc-qt/Instance.h
    "$ENV{LIBVLCQT_INCLUDE_PATH}"
    "$ENV{LIB_DIR}/include"
    "$ENV{LIB_DIR}/include/vlc-qt"
    "/usr/include"
    "/usr/include/vlc-qt"
    "/usr/local/include"
    "/usr/local/include/vlc-qt"
    c:/msys/local/include
    NO_DEFAULT_PATH
)
FIND_PATH(LIBVLCQT_INCLUDE_DIR Instance.h)

# Library
FIND_LIBRARY(LIBVLCQT_CORE_LIBRARY NAMES vlc-qt-core PATHS
    "$ENV{LIBVLCQT_CORE_LIBRARY_PATH}"
    "$ENV{LIB_DIR}/lib"
    c:/msys/local/lib
    NO_DEFAULT_PATH
)
FIND_LIBRARY(LIBVLCQT_CORE_LIBRARY NAMES vlc-qt-core)
FIND_LIBRARY(LIBVLCQT_WIDGETS_LIBRARY NAMES vlc-qt-widgets)
FIND_LIBRARY(LIBVLCQT_QML_LIBRARY NAMES vlc-qt-qml)

IF(LIBVLCQT_INCLUDE_DIR AND LIBVLCQT_CORE_LIBRARY)
    SET(LIBVLCQT_FOUND TRUE)
ENDIF()

IF(LIBVLCQT_FOUND)
    IF(NOT LIBVLCQT_FIND_QUIETLY)
        MESSAGE(STATUS "Found libvlc-qt include-dir path: ${LIBVLCQT_INCLUDE_DIR}")
        MESSAGE(STATUS "Found libvlc-qt library path: ${LIBVLCQT_CORE_LIBRARY}")
    ENDIF(NOT LIBVLCQT_FIND_QUIETLY)
ELSE()
    IF(LIBVLCQT_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find libvlc-qt")
    ENDIF()
ENDIF()
