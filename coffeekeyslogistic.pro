QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Set the folder for object files (.o)
OBJECTS_DIR = build

TARGET    = CoffeeKeysLogistics
TEMPLATE  = app

INCLUDEPATH += Model/Memory Model/Items Model/JSON Model/XML View

SOURCES += \
    main.cpp \
    Model/Memory/HubLogistica.cpp \
    Model/Items/Spedizione.cpp \
    Model/Items/SpedizioneRifornimentoStock.cpp \
    Model/Items/SpedizioneGroupBuyInbound.cpp \
    Model/Items/SpedizioneResoFabbrica.cpp \
    Model/Items/SpedizioneClientiStandard.cpp \
    Model/Items/SpedizioneClientiEspressa.cpp \
    Model/Items/SpedizioneReviewerSponsor.cpp \
    Model/JSON/JsonConverter.cpp \
    Model/JSON/JsonFile.cpp \
    Model/JSON/JsonReader.cpp \
    Model/XML/XmlPersistenza.cpp \
    View/MainWindow.cpp \
    View/ListaSpedizioniWidget.cpp \
    View/DettaglioSpedizioneWidget.cpp \
    View/FormSpedizioneWidget.cpp

HEADERS += \
    Model/Memory/HubLogistica.h \
    Model/Items/Spedizione.h \
    Model/Items/SpedizioneRifornimentoStock.h \
    Model/Items/SpedizioneGroupBuyInbound.h \
    Model/Items/SpedizioneResoFabbrica.h \
    Model/Items/SpedizioneClientiStandard.h \
    Model/Items/SpedizioneClientiEspressa.h \
    Model/Items/SpedizioneReviewerSponsor.h \
    Model/JSON/JsonConverter.h \
    Model/JSON/JsonFile.h \
    Model/JSON/JsonReader.h \
    Model/XML/XmlPersistenza.h \
    View/MainWindow.h \
    View/ListaSpedizioniWidget.h \
    View/DettaglioSpedizioneWidget.h \
    View/FormSpedizioneWidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
