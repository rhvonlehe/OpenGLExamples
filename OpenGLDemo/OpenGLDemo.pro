QT = core gui widgets printsupport
CONFIG += c++11

HEADERS += \
    AppGLScene.h \
    PLYReader.h \
    MainWindow.h \
    ScenePoint.h \
    GLHelpers.h

SOURCES += \
    AppGLScene.cpp \
    PLYReader.cpp \
    main.cpp \
    MainWindow.cpp

DISTFILES +=

RESOURCES += \
    Resources.qrc

TRANSLATIONS = opengldemo_sp.ts
