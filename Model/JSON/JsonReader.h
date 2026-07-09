#ifndef JSONREADER_H
#define JSONREADER_H

#include <vector>
#include <QString>
#include "Spedizione.h"

class JsonReader {
public:
    static std::vector<Spedizione*> caricaSpedizioni(const QString& percorso, bool& ok);
    static bool salvaSpedizioni(const QString& percorso, const std::vector<Spedizione*>& spedizioni);
};

#endif // JSONREADER_H
