QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    main.cpp \
    mainwindow.cpp \
    videoplayer.cpp

HEADERS += \
    client.h \
    mainwindow.h \
<<<<<<< HEAD
    player.h
<<<<<<< HEAD
=======
    mainwindow.cpp

HEADERS += \
    client.h \
    mainwindow.h
>>>>>>> parent of 8cebf9e... server now has mydata class, getting rtsp stream
=======
    videoplayer.h
>>>>>>> parent of 92827ac... bad commit, uncompilable
=======
>>>>>>> parent of f1e38ef... revert

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qslog/ -lQsLog2
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qslog/ -lQsLog2d
#else:unix: LIBS += -L$$PWD/../qslog/ -lQsLog2

#INCLUDEPATH += $$PWD/qslog
#DEPENDPATH += $$PWD/qslog
<<<<<<< HEAD

unix|win32: LIBS += -L$$PWD/lib/ -lavcodec

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lavdevice

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lavfilter

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lavformat

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lavutil

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lpostproc

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lSDL2

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lSDL2main

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lswresample

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix|win32: LIBS += -L$$PWD/lib/ -lswscale

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
<<<<<<< HEAD
=======
>>>>>>> parent of 8cebf9e... server now has mydata class, getting rtsp stream
=======
>>>>>>> parent of 92827ac... bad commit, uncompilable
=======
>>>>>>> parent of f1e38ef... revert
