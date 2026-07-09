#include "SpedizioneResoFabbrica.h"

SpedizioneResoFabbrica::SpedizioneResoFabbrica(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                                               QString rma, bool garanzia, QString motivoReso)
    : Spedizione(idPacco, dest, ind, p, prodotto, immagine)
{
    codiceRMA = rma;
    copertoDaGaranzia = garanzia;
    this->motivoReso = motivoReso;
}

QString SpedizioneResoFabbrica::getManifestoSpedizione() const {
    QString testoGaranzia = copertoDaGaranzia ? "Sì" : "No";

    return QString("RESO MERCE DIFETTOSA (OUTBOUND VERSO ASIA)\n"
                   "Prodotto: %1\n"
                   "Codice RMA: %2\n"
                   "Coperto da Garanzia: %3\n"
                   "Motivo Reso: %4")
           .arg(prodotto)
           .arg(codiceRMA)
           .arg(testoGaranzia)
           .arg(motivoReso);
}

QJsonObject SpedizioneResoFabbrica::toJson() const{
    QJsonObject obj = serializzaComuni("ResoFabbrica");
    obj["codiceRMA"]=codiceRMA;
    obj["copertoDaGaranzia"] = copertoDaGaranzia;
    obj["motivoReso"] = motivoReso;
    return obj;
}
