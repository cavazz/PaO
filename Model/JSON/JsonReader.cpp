#include "JsonReader.h"
#include "JsonFile.h"
#include "JsonConverter.h"
#include <QJsonArray>

std::vector<Spedizione*> JsonReader::caricaSpedizioni(const QString& percorso, bool& ok) {
    std::vector<Spedizione*> spedizioni;

    QJsonDocument documento = JsonFile::leggiFile(percorso, ok);
    if (!ok || !documento.isArray()) {
        ok = false;
        return spedizioni;
    }

    QJsonArray array = documento.array();
    for (const QJsonValue& valore : array) {
        Spedizione* s = JsonConverter::jsonToSpedizione(valore.toObject());
        if (s != nullptr) {
            spedizioni.push_back(s);
        }
    }

    ok = true;
    return spedizioni;
}

bool JsonReader::salvaSpedizioni(const QString& percorso, const std::vector<Spedizione*>& spedizioni) {
    QJsonArray array;
    for (const Spedizione* s : spedizioni) {
        array.append(JsonConverter::spedizioneToJson(s));
    }

    QJsonDocument documento(array);
    return JsonFile::scriviFile(percorso, documento);
}
