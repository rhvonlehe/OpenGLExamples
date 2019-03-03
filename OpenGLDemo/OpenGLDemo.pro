QT = core gui widgets printsupport
CONFIG += c++11

HEADERS += \
    AppGLScene.h \
    PLYReader.h \
    MainWindow.h \
    ScenePoint.h \
    GLHelpers.h \
    SceneContainer.h

SOURCES += \
    AppGLScene.cpp \
    PLYReader.cpp \
    main.cpp \
    MainWindow.cpp \
    SceneContainer.cpp

DISTFILES +=

RESOURCES += \
    Resources.qrc

TRANSLATIONS = opengldemo_sp.ts
