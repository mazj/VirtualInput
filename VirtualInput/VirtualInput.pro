QT       += gui-private gui widgets

CONFIG += plugin

TARGET = VirtualInput
TEMPLATE = lib

DEFINES += VIRTUALINPUT_LIBRARY

SOURCES += \
    #mockupkeyeventdispatcher.cpp
    viinputcontext.cpp \
    viplatforminputcontextplugin.cpp \
    keyboard.cpp \
    numpad.cpp

HEADERS +=\
    #mockupkeyeventdispatcher.h
    virtualinput_global.h \
    viinputcontext.h \
    viplatforminputcontextplugin.h \
    keyboard.h \
    numpad.h

target.path = $$[QT_INSTALL_PLUGINS]/platforminputcontexts

INSTALLS += target

#OTHER_FILES += \
#    InputPanel.qml \
#    KeyModel.qml \
#    KeyButton.qml

#RESOURCES += \
#    mockupresources.qrc

OTHER_FILES += \
    virtualinput.json

FORMS += \
    keyboard.ui \
    numpad.ui
