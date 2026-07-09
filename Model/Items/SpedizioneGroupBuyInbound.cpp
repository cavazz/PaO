#include "SpedizioneGroupBuyInbound.h"

SpedizioneGroupBuyInbound::SpedizioneGroupBuyInbound(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                                                     QDate data, QString lotto, double acconto)
    : Spedizione(idPacco, dest, ind, p, prodotto, immagine)
{
    dataArrivoPrevista = data;
    idLottoProduzione = lotto;
    accontoVersato=acconto;
}

QString SpedizioneGroupBuyInbound::getManifestoSpedizione() const {
    return QString("LOGISTICA GROUP BUY (PRE-ORDINE)\n"
                   "Prodotto: %1\n"
                   "ID Lotto: %2\n"
                   "Data Arrivo Prevista: %3\n"
                   "Totale Acconti Versati: %4 €")
           .arg(prodotto)
           .arg(idLottoProduzione)
           .arg(dataArrivoPrevista.toString("dd/MM/yyyy"))
           .arg(accontoVersato);
}

QJsonObject SpedizioneGroupBuyInbound::toJson() const{
    QJsonObject obj = serializzaComuni("GroupBuyInbound");
    obj["dataArrivoPrevista"] = dataArrivoPrevista.toString(Qt::ISODate);
    obj["idLottoProduzione"] = idLottoProduzione;
    obj["accontoVersato"] = accontoVersato;
    return obj;
}
