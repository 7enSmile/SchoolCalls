QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    src/model/dbmanager.cpp \
    src/view/mainwindow.cpp\
    src/view/tabledelegate.cpp \
    src/viewmodel/call.cpp \
    src/viewmodel/callsmanager.cpp


HEADERS += include/view/mainwindow.h \
    include/model/dbmanager.h \
    include/view/tabledelegate.h \
    include/viewmodel/call.h \
    include/viewmodel/callsmanager.h


FORMS += ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RC_ICONS = icon/icon.ico

RESOURCES += \
    res.qrc
