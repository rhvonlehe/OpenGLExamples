QT = core gui
TARGET = cube
TEMPLATE = app

LIBS += -lopengl32

HEADERS += \
    AbstractGLScene.h \
    SceneGLWindow.h \
    CubeGLScene.h

SOURCES += \
    AbstractGLScene.cpp \
    SceneGLWindow.cpp \
    CubeGLScene.cpp \
    main.cpp

CONFIG += c++11

RESOURCES += \
    texture.qrc

