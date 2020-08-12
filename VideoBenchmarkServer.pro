QT -= gui
QT += core network
CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS __STDC_LIMIT_MACROS
include(qslog/QsLog.pri)
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
        datasource.cpp \
        main.cpp \
        mydata.cpp \
    restream.cpp \
        tcp.cpp \
        udp.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    datasource.h \
    mydata.h \
    packet.h \
    qslog/QsLog.h \
    qslog/QsLogDest.h \
    restream.h \
    tcp.h \
    udp.h \

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lavcodec
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lavcodec
else:unix: LIBS += -L$$PWD/lib/ -lavcodec

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lavdevice
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lavdevice
else:unix: LIBS += -L$$PWD/lib/ -lavdevice

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lavfilter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lavfilter
else:unix: LIBS += -L$$PWD/lib/ -lavfilter

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lavformat
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lavformat
else:unix: LIBS += -L$$PWD/lib/ -lavformat

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lavutil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lavutil
else:unix: LIBS += -L$$PWD/lib/ -lavutil

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lpostproc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lpostproc
else:unix: LIBS += -L$$PWD/lib/ -lpostproc

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lSDL2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lSDL2
else:unix: LIBS += -L$$PWD/lib/ -lSDL2

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lSDL2main
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lSDL2main
else:unix: LIBS += -L$$PWD/lib/ -lSDL2main

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lswresample
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lswresample
else:unix: LIBS += -L$$PWD/lib/ -lswresample

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lswscale
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lswscale
else:unix: LIBS += -L$$PWD/lib/ -lswscale

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

