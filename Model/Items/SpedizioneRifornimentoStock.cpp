#include "SpedizioneRifornimentoStock.h"

SpedizioneRifornimentoStock::SpedizioneRifornimentoStock(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                                                           QString fornitore, QString numeroOrdineAcquisto, int quantitaColli)
    : Spedizione(idPacco, dest, ind, p, prodotto, immagine)
{
    this->fornitore = fornitore;
    this->numeroOrdineAcquisto = numeroOrdineAcquisto;
    this->quantitaColli=quantitaColli;
}

QString SpedizioneRifornimentoStock::getManifestoSpedizione() const{
    return QString("RIFORNIMENTO STOCK (INBOUND DA FORNITORE)\n"
                   "Prodotto: %1\n"
                   "Fornitore: %2\n"
                   "Numero Ordine Acquisto: %3\n"
                   "Colli Totali: %4")
           .arg(prodotto)
           .arg(fornitore)
           .arg(numeroOrdineAcquisto)
           .arg(quantitaColli);
}

QJsonObject SpedizioneRifornimentoStock::toJson() const {
    QJsonObject obj = serializzaComuni("RifornimentoStock");
    obj["fornitore"] = fornitore;
    obj["numeroOrdineAcquisto"] = numeroOrdineAcquisto;
    obj["quantitaColli"] = quantitaColli;
    return obj;
}
