QT = core gui widgets
CONFIG += c++11

LIBS += opengl32.lib User32.lib

DEFINES += QT_USE_NATIVE_WINDOWS=1

HEADERS += \
    AppGLScene.h \
    PLYReader.h \
    MainWindow.h \
    ScenePoint.h \
    GLHelpers.h

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    AppGLScene.cpp \
    PLYReader.cpp

DISTFILES +=

RESOURCES += \
    Resources.qrc
