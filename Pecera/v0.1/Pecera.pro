QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 cmdline


SOURCES += \
        GameScene.cpp \
        game.cpp \
        main.cpp \
        view.cpp

HEADERS += \
    GameScene.h \
    game.h \
    view.h


RESOURCES += \
    resource.qrc
