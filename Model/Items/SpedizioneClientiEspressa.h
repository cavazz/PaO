#ifndef SPEDIZIONECLIENTIESPRESSA_H
#define SPEDIZIONECLIENTIESPRESSA_H

#include "Spedizione.h"

class SpedizioneClientiEspressa : public Spedizione {
public:
    SpedizioneClientiEspressa(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                               QString corriere, int oreConsegnaGarantite);

    QString getManifestoSpedizione() const override;
    QJsonObject toJson() const override;

private:
    QString corriere;
    int oreConsegnaGarantite;
};

#endif // SPEDIZIONECLIENTIESPRESSA_H
