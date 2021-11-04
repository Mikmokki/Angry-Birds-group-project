QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
LIBS += -L"..\SFML-2.5.1\lib" #change this
LIBS += -L"..\SFML-2.5.1\bin" #change this

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

SOURCES += \
    gameview.cpp \
    sfml_widget.cpp \
    main.cpp \
    mainmenu.cpp

HEADERS += \
    gameview.h \
    sfml_widget.h \
    mycanvas.h \
    mainmenu.h

FORMS += \
    gameview.ui \
    mainmenu.ui

INCLUDEPATH += "..\SFML-2.5.1\include"
DEPENDPATH += "..\SFML-2.5.1\include"



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
