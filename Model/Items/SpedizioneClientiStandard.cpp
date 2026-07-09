#include "SpedizioneClientiStandard.h"

SpedizioneClientiStandard::SpedizioneClientiStandard(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                                                       QString corriere)
    : Spedizione(idPacco, dest, ind, p, prodotto, immagine)
{
    this->corriere = corriere;
}

QString SpedizioneClientiStandard::getManifestoSpedizione() const{
    return QString("CONSEGNA STANDARD A CLIENTE\n"
                   "Prodotto: %1\n"
                   "Corriere: %2")
           .arg(prodotto)
           .arg(corriere);
}

QJsonObject SpedizioneClientiStandard::toJson() const {
    QJsonObject obj = serializzaComuni("ClientiStandard");
    obj["corriere"]=corriere;
    return obj;
}
