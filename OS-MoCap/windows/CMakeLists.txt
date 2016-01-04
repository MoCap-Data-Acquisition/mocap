#
# Open Source MoCap - Dynamics Trajectory Data Acquisition System
# 
# This build script was originally written by Tadej Novak and modified by the
# MoCap Software Engineering Team to fit our needs.
#
# Windows Extra

IF(MINGW OR MSVC)
    CONFIGURE_FILE(
        ${CMAKE_SOURCE_DIR}/windows/Project.rc.in
        ${CMAKE_BINARY_DIR}/windows/Project.rc
    )
ENDIF()

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    SET(VLCQtPostfix "d")
ENDIF()
IF(MINGW)
    SET(VLCQtPrefix "lib")
ENDIF()

SET(VLCQtLibs
    ${VLCQtCoreLocation}/bin/${VLCQtPrefix}VLCQtCore${VLCQtPostfix}.dll
    ${VLCQtWidgetsLocation}/bin/${VLCQtPrefix}VLCQtWidgets${VLCQtPostfix}.dll
    ${VLCQtCoreLocation}/bin/libvlc.dll
    ${VLCQtCoreLocation}/bin/libvlccore.dll
)

SET(VLCQtPlugins ${VLCQtCoreLocation}/bin/plugins)

FILE(GLOB VLCGcc "${VLCQtCoreLocation}/bin/libgcc_s_*-1.dll")
IF(VLCGcc)
    SET(ExtraLibs
        ${VLCGcc}
    )
ENDIF()

FILE(GLOB VLCStd "${VLCQtCoreLocation}/bin/libstdc++-6.dll")
IF(VLCStd)
    SET(ExtraLibs
        ${ExtraLibs}
        ${VLCQtCoreLocation}/bin/libstdc++-6.dll
        ${VLCQtCoreLocation}/bin/libwinpthread-1.dll
    )
ENDIF()

ADD_CUSTOM_TARGET(windows
    "${QT_BIN_DIR}/windeployqt.exe" "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_BIN_DIR}/${PROJECT_NAME}.exe")


################
# Installation #
################

# Hopefully this will do magic for the users, otherwise they will need to do a
# lot of annoying stuff to get everything built and working properly on
# Windows.
INSTALL(FILES ${VLCQtLibs} DESTINATION "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_BIN_DIR}")
INSTALL(DIRECTORY ${VLCQtPlugins} DESTINATION "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_BIN_DIR}")

IF(VLCGcc OR VLCStd)
    INSTALL(FILES ${ExtraLibs} DESTINATION "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_BIN_DIR}")
ENDIF()
