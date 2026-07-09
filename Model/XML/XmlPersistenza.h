#ifndef XMLPERSISTENZA_H
#define XMLPERSISTENZA_H

#include <vector>
#include <QString>
#include <QMap>
#include "Spedizione.h"

class XmlPersistenza {
public:
    static bool salvaSpedizioni(const QString& percorso, const std::vector<Spedizione*>& spedizioni);
    static std::vector<Spedizione*> caricaSpedizioni(const QString& percorso, bool& ok);

private:
    static Spedizione* costruisciDaCampi(const QMap<QString, QString>& campi);
};

#endif // XMLPERSISTENZA_H
