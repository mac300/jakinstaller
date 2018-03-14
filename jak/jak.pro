#-------------------------------------------------
# Project created by QtCreator 2013-09-03T10:32:27
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jak
TEMPLATE = app

#-------------------------------------------------
# Plik wykonywalny (ubuntu mate)
#-------------------------------------------------
#unix {
#    QMAKE_LFLAGS += -no-pie
#}

#-------------------------------------------------
# Wybór katalogu wynikowego
#-------------------------------------------------
CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/../../JakDebug
} else {
    DESTDIR = $$OUT_PWD/../../JakRelease
}

#-------------------------------------------------
# Kopiowanie pliku bazy danych
#-------------------------------------------------
    win32 {
        COPY_FROM_PATH = $$shell_path($$PWD/isotopes)
        COPY_TO_PATH = $$shell_path($$DESTDIR/isotopes)
    }
    else {
        COPY_FROM_PATH = $$PWD/isotopes
        COPY_TO_PATH = $$DESTDIR/isotopes
    }
    copydata.commands = $(COPY_DIR) $$COPY_FROM_PATH $$COPY_TO_PATH
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata

#-------------------------------------------------
# Oddzielne katalogi dla typów plików
#-------------------------------------------------
MOC_DIR = ../common/build/moc
RCC_DIR = ../common/build/rcc
UI_DIR = ../common/build/ui
unix:OBJECTS_DIR = ../common/build/o/unix
win32:OBJECTS_DIR = ../common/build/o/win32
macx:OBJECTS_DIR = ../common/build/o/mac

#-------------------------------------------------
# Uruchomienie win deploy
#-------------------------------------------------
win32 {
    QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$DESTDIR
}

#-------------------------------------------------
# Uruchomienie linuxdeployqt (linux)
#-------------------------------------------------
unix {
    QMAKE_POST_LINK = mkdir $$OUT_PWD/../../tmp
    QMAKE_POST_LINK += && cp -f $$PWD/addons/* $$OUT_PWD/../../tmp
    QMAKE_POST_LINK += && mv -f $$DESTDIR/$$TARGET $$OUT_PWD/../../tmp
    QMAKE_POST_LINK += && $$(QTDIR)/bin/linuxdeployqt $$OUT_PWD/../../tmp/$$TARGET -no-translations -no-copy-copyright-files -appimage
    QMAKE_POST_LINK += && mv -f $$OUT_PWD/*.AppImage $$DESTDIR/$$TARGET
    QMAKE_POST_LINK += && rm -R $$OUT_PWD/../../tmp
}

#-------------------------------------------------
# Pliki projektu
#-------------------------------------------------
SOURCES += main.cpp\
    mainwindow.cpp \
    mainwidget.cpp \
    isotopeaction.cpp \
    isotopesdiagramview.cpp \
    isotopesview.cpp \
    isotopesgraphview.cpp \
    isotopediagramitem.cpp \
    isotopewidget.cpp \
    selectedisotopelabel.cpp

HEADERS  += mainwindow.h \
    mainwidget.h \
    isotopeaction.h \
    isotopesdiagramview.h \
    isotopesview.h \
    isotopesgraphview.h \
    isotopediagramitem.h \
    isotopewidget.h \
    selectedisotopelabel.h

RESOURCES += \
    MyResources.qrc

DISTFILES += \
    isotopes/isotopes.db \
    images/folder.png \
    images/left.png \
    images/logo.png \
    images/right.png \
    images/export.png \
    images/exit.png \
    addons/jak.desktop \
    addons/jak_logo.png
