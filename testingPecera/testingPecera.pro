QT += testlib
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES += \
        GameScene.cpp \
        tst_testcase.cpp \
        game.cpp \
        view.cpp

HEADERS += \
    GameScene.h \
    game.h \
    view.h


RESOURCES += \
    resource.qrc
