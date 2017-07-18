#-------------------------------------------------
#
# Project created by QtCreator 2017-06-25T20:24:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tplayer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH +=	"C:\\gstreamer\\1.0\\x86_64\\lib\\glib-2.0\\include" \
                "C:\\gstreamer\\1.0\\x86_64\\include\\glib-2.0" \
                "C:\\gstreamer\\1.0\\x86_64\\include\\gstreamer-1.0"

LIBS += -LC:\\gstreamer\\1.0\\x86_64\\lib \
        -LC:\\gstreamer\\1.0\\x86_64\\bin \
        -lgstreamer-1.0 \
        -lgstvideo-1.0	\
        -lglib-2.0 \
        -lgobject-2.0

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tplayer.cpp \
    playlist.cpp

HEADERS += \
        mainwindow.h \
    tplayer.h \
    playlist.h

FORMS += \
        mainwindow.ui \
    playlist.ui
