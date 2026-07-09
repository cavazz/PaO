#ifndef SPEDIZIONEGROUPBUYINBOUND_H
#define SPEDIZIONEGROUPBUYINBOUND_H

#include <QDate>
#include "Spedizione.h"

class SpedizioneGroupBuyInbound : public Spedizione {
public:
    SpedizioneGroupBuyInbound(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                               QDate data, QString lotto, double acconto);

    QString getManifestoSpedizione() const override;
    QJsonObject toJson() const override;

private:
    QDate dataArrivoPrevista;
    QString idLottoProduzione;
    double accontoVersato;
};

#endif // SPEDIZIONEGROUPBUYINBOUND_H
