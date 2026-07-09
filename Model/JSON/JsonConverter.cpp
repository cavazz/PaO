#include "JsonConverter.h"
#include "SpedizioneRifornimentoStock.h"
#include "SpedizioneResoFabbrica.h"
#include "SpedizioneGroupBuyInbound.h"
#include "SpedizioneClientiStandard.h"
#include "SpedizioneClientiEspressa.h"
#include "SpedizioneReviewerSponsor.h"
#include <QDate>

QJsonObject JsonConverter::spedizioneToJson(const Spedizione* spedizione) {
    return spedizione->toJson();
}

Spedizione* JsonConverter::jsonToSpedizione(const QJsonObject& oggetto) {
    QString tipo = oggetto["tipo"].toString();
    QString id = oggetto["id"].toString();
    QString destinatario = oggetto["destinatario"].toString();
    QString indirizzo = oggetto["indirizzo"].toString();
    double peso = oggetto["peso"].toDouble();
    QString prodotto = oggetto["prodotto"].toString();
    QString immagine = oggetto["immagine"].toString();

    if (tipo == "RifornimentoStock") {
        return new SpedizioneRifornimentoStock(id, destinatario, indirizzo, peso, prodotto, immagine,
                                                oggetto["fornitore"].toString(),
                                                oggetto["numeroOrdineAcquisto"].toString(),
                                                oggetto["quantitaColli"].toInt());
    }
    if (tipo == "ResoFabbrica") {
        return new SpedizioneResoFabbrica(id, destinatario, indirizzo, peso, prodotto, immagine,
                                           oggetto["codiceRMA"].toString(),
                                           oggetto["copertoDaGaranzia"].toBool(),
                                           oggetto["motivoReso"].toString());
    }
    if (tipo == "GroupBuyInbound") {
        return new SpedizioneGroupBuyInbound(id, destinatario, indirizzo, peso, prodotto, immagine,
                                              QDate::fromString(oggetto["dataArrivoPrevista"].toString(), Qt::ISODate),
                                              oggetto["idLottoProduzione"].toString(),
                                              oggetto["accontoVersato"].toDouble());
    }
    if(tipo == "ClientiStandard"){
        return new SpedizioneClientiStandard(id, destinatario, indirizzo, peso, prodotto, immagine,
                                              oggetto["corriere"].toString());
    }
    if (tipo == "ClientiEspressa") {
        return new SpedizioneClientiEspressa(id, destinatario, indirizzo, peso, prodotto, immagine,
                                              oggetto["corriere"].toString(),
                                              oggetto["oreConsegnaGarantite"].toInt());
    }
    if (tipo == "ReviewerSponsor") {
        return new SpedizioneReviewerSponsor(id, destinatario, indirizzo, peso, prodotto, immagine,
                                              oggetto["nomeReviewer"].toString(),
                                              oggetto["codiceCampagna"].toString(),
                                              oggetto["valoreProdottoOmaggio"].toDouble());
    }

    return nullptr;
}
