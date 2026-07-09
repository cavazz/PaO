#ifndef SPEDIZIONEREVIEWERSPONSOR_H
#define SPEDIZIONEREVIEWERSPONSOR_H

#include "Spedizione.h"

class SpedizioneReviewerSponsor : public Spedizione {
public:
    SpedizioneReviewerSponsor(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                               QString nomeReviewer, QString codiceCampagna, double valoreProdottoOmaggio);

    QString getManifestoSpedizione() const override;
    QJsonObject toJson() const override;

private:
    QString nomeReviewer;
    QString codiceCampagna;
    double valoreProdottoOmaggio;
};

#endif // SPEDIZIONEREVIEWERSPONSOR_H
