#ifndef SPEDIZIONECLIENTISTANDARD_H
#define SPEDIZIONECLIENTISTANDARD_H

#include "Spedizione.h"

class SpedizioneClientiStandard : public Spedizione {
public:
    SpedizioneClientiStandard(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                               QString corriere);

    QString getManifestoSpedizione() const override;
    QJsonObject toJson() const override;

private:
    QString corriere;
};

#endif // SPEDIZIONECLIENTISTANDARD_H
