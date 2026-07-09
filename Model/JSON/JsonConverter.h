#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <QJsonObject>
#include "Spedizione.h"

class JsonConverter {
public:
    static QJsonObject spedizioneToJson(const Spedizione* spedizione);
    static Spedizione* jsonToSpedizione(const QJsonObject& oggetto);
};

#endif // JSONCONVERTER_H
