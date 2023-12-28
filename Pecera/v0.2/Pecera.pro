QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 cmdline


SOURCES += \
        Acuario.cpp \
        GameScene.cpp \
        Pez.cpp \
        game.cpp \
        main.cpp \
        view.cpp

HEADERS += \
    Acuario.h \
    GameScene.h \
    Pez.h \
    game.h \
    view.h


RESOURCES += \
    resource.qrc
