#ifndef SPEDIZIONERIFORNIMENTOSTOCK_H
#define SPEDIZIONERIFORNIMENTOSTOCK_H

#include "Spedizione.h"

class SpedizioneRifornimentoStock : public Spedizione {
public:
    SpedizioneRifornimentoStock(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                                 QString fornitore, QString numeroOrdineAcquisto, int quantitaColli);

    QString getManifestoSpedizione() const override;
    QJsonObject toJson() const override;

private:
    QString fornitore;
    QString numeroOrdineAcquisto;
    int quantitaColli;
};

#endif // SPEDIZIONERIFORNIMENTOSTOCK_H
