#include "SpedizioneClientiEspressa.h"

SpedizioneClientiEspressa::SpedizioneClientiEspressa(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                                                       QString corriere, int oreConsegnaGarantite)
    : Spedizione(idPacco, dest, ind, p, prodotto, immagine)
{
    this->corriere = corriere;
    this->oreConsegnaGarantite=oreConsegnaGarantite;
}

QString SpedizioneClientiEspressa::getManifestoSpedizione() const {
    return QString("CONSEGNA ESPRESSA A CLIENTE\n"
                   "Prodotto: %1\n"
                   "Corriere: %2\n"
                   "Consegna Garantita Entro: %3 ore")
           .arg(prodotto)
           .arg(corriere)
           .arg(oreConsegnaGarantite);
}

QJsonObject SpedizioneClientiEspressa::toJson() const{
    QJsonObject obj = serializzaComuni("ClientiEspressa");
    obj["corriere"] = corriere;
    obj["oreConsegnaGarantite"] = oreConsegnaGarantite;
    return obj;
}
