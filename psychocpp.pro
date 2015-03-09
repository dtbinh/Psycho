TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    board.cpp \
    marble.cpp \
    myvectoroftree.cpp \
    node.cpp \
    path.cpp \
    player.cpp \
    tree.cpp \
    util.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    board.h \
    marble.h \
    myvectoroftree.h \
    node.h \
    path.h \
    player.h \
    tree.h \
    util.h

