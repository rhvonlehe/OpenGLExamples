QT = core gui
TARGET = triangle
TEMPLATE = app

LIBS += -lopengl32

HEADERS += \
    simpleglwindow.h

SOURCES += \
    simpleglwindow.cpp \
    main.cpp
