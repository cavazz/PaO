#include "SpedizioneReviewerSponsor.h"

SpedizioneReviewerSponsor::SpedizioneReviewerSponsor(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                                                       QString nomeReviewer, QString codiceCampagna, double valoreProdottoOmaggio)
    : Spedizione(idPacco, dest, ind, p, prodotto, immagine)
{
    this->nomeReviewer = nomeReviewer;
    this->codiceCampagna = codiceCampagna;
    this->valoreProdottoOmaggio=valoreProdottoOmaggio;
}

QString SpedizioneReviewerSponsor::getManifestoSpedizione() const {
    return QString("OMAGGIO REVIEWER/SPONSOR (MARKETING)\n"
                   "Prodotto: %1\n"
                   "Reviewer: %2\n"
                   "Codice Campagna: %3\n"
                   "Valore Prodotto Omaggio: %4 €")
           .arg(prodotto)
           .arg(nomeReviewer)
           .arg(codiceCampagna)
           .arg(valoreProdottoOmaggio);
}

QJsonObject SpedizioneReviewerSponsor::toJson() const{
    QJsonObject obj = serializzaComuni("ReviewerSponsor");
    obj["nomeReviewer"] = nomeReviewer;
    obj["codiceCampagna"] = codiceCampagna;
    obj["valoreProdottoOmaggio"] = valoreProdottoOmaggio;
    return obj;
}
