# ----------------------------------------------------
# File di progetto per Coffee Keys Logistics
# ----------------------------------------------------

# 1. MODULI QT RICHIESTI
# Togliamo 'gui' e 'widgets' e lasciamo solo core per farlo girare in console
QT       += core

CONFIG   += c++17 console
CONFIG   -= app_bundle

# Questo dice a Qt dove cercare i file quando usate gli #include negli altri file
INCLUDEPATH += Model/Memory Model/Items Model/JSON

# Set the folder for object files (.o)
OBJECTS_DIR = build

# Nome dell'eseguibile finale
TARGET    = CoffeeKeysLogistics
TEMPLATE  = app

# 2. I FILE SORGENTI DEL PROGETTO (.cpp) REALI
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
    Model/JSON/JsonReader.cpp

# 3. I FILE HEADER DEL PROGETTO (.h) REALI
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
    Model/JSON/JsonReader.h