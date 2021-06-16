QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    internet.cpp \
    main.cpp \
    main_menu.cpp \
    wuziqi.cpp \
    wuziqi_internet.cpp

HEADERS += \
    internet.h \
    main_menu.h \
    wuziqi.h \
    wuziqi_internet.h

FORMS += \
    main_menu.ui \
    wuziqi.ui \
    wuziqi_internet.ui
LIBS += -lpthread libwsock32 libws2_32
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
