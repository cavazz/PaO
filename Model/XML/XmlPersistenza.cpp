#include "XmlPersistenza.h"
#include "SpedizioneClientiStandard.h"
#include "SpedizioneClientiEspressa.h"
#include "SpedizioneReviewerSponsor.h"
#include "SpedizioneRifornimentoStock.h"
#include "SpedizioneResoFabbrica.h"
#include "SpedizioneGroupBuyInbound.h"
#include <QFile>
#include <QIODevice>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDate>

static QString valoreToTesto(const QJsonValue& valore) {
    if (valore.isBool()) {
        return valore.toBool() ? "true" : "false";
    }
    if (valore.isDouble()) {
        return QString::number(valore.toDouble());
    }
    return valore.toString();
}

bool XmlPersistenza::salvaSpedizioni(const QString& percorso, const std::vector<Spedizione*>& spedizioni) {
    QFile file(percorso);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("spedizioni");

    for (const Spedizione* s : spedizioni) {
        QJsonObject dati = s->toJson();
        xml.writeStartElement("spedizione");
        for (auto it = dati.constBegin(); it != dati.constEnd(); ++it) {
            xml.writeTextElement(it.key(), valoreToTesto(it.value()));
        }
        xml.writeEndElement();
    }

    xml.writeEndElement();
    xml.writeEndDocument();
    file.close();

    return !xml.hasError();
}

Spedizione* XmlPersistenza::costruisciDaCampi(const QMap<QString, QString>& campi) {
    QString tipo = campi.value("tipo");
    QString id = campi.value("id");
    QString destinatario = campi.value("destinatario");
    QString indirizzo = campi.value("indirizzo");
    double peso = campi.value("peso").toDouble();
    QString prodotto = campi.value("prodotto");
    QString immagine = campi.value("immagine");

    if (tipo == "ClientiStandard") {
        return new SpedizioneClientiStandard(id, destinatario, indirizzo, peso, prodotto, immagine,
                                              campi.value("corriere"));
    }
    if (tipo == "ClientiEspressa") {
        return new SpedizioneClientiEspressa(id, destinatario, indirizzo, peso, prodotto, immagine,
                                              campi.value("corriere"),
                                              campi.value("oreConsegnaGarantite").toInt());
    }
    if (tipo == "ReviewerSponsor") {
        return new SpedizioneReviewerSponsor(id, destinatario, indirizzo, peso, prodotto, immagine,
                                              campi.value("nomeReviewer"),
                                              campi.value("codiceCampagna"),
                                              campi.value("valoreProdottoOmaggio").toDouble());
    }
    if (tipo == "RifornimentoStock") {
        return new SpedizioneRifornimentoStock(id, destinatario, indirizzo, peso, prodotto, immagine,
                                                campi.value("fornitore"),
                                                campi.value("numeroOrdineAcquisto"),
                                                campi.value("quantitaColli").toInt());
    }
    if(tipo == "ResoFabbrica"){
        bool garanzia = campi.value("copertoDaGaranzia").compare("true", Qt::CaseInsensitive)==0;
        return new SpedizioneResoFabbrica(id, destinatario, indirizzo, peso, prodotto, immagine,
                                           campi.value("codiceRMA"), garanzia,
                                           campi.value("motivoReso"));
    }
    if (tipo == "GroupBuyInbound") {
        QDate data = QDate::fromString(campi.value("dataArrivoPrevista"), Qt::ISODate);
        return new SpedizioneGroupBuyInbound(id, destinatario, indirizzo, peso, prodotto, immagine,
                                              data, campi.value("idLottoProduzione"),
                                              campi.value("accontoVersato").toDouble());
    }

    return nullptr;
}

std::vector<Spedizione*> XmlPersistenza::caricaSpedizioni(const QString& percorso, bool& ok) {
    std::vector<Spedizione*> spedizioni;

    QFile file(percorso);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ok = false;
        return spedizioni;
    }

    QXmlStreamReader xml(&file);

    while (xml.readNextStartElement()) {
        if (xml.name() != QString("spedizioni")) {
            xml.skipCurrentElement();
            continue;
        }

        while (xml.readNextStartElement()) {
            if (xml.name() != QString("spedizione")) {
                xml.skipCurrentElement();
                continue;
            }

            QMap<QString, QString> campi;
            while (xml.readNextStartElement()) {
                campi[xml.name().toString()] = xml.readElementText();
            }

            Spedizione* s = costruisciDaCampi(campi);
            if (s != nullptr) {
                spedizioni.push_back(s);
            }
        }
    }

    file.close();
    ok = !xml.hasError();
    return spedizioni;
}
