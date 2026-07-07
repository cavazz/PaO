#include "SpedizioneGroupBuyInbound.h"

// 1. IL COSTRUTTORE
SpedizioneGroupBuyInbound::SpedizioneGroupBuyInbound(QString idPacco, QString dest, QString ind, double p, 
                                                     QDate data, QString lotto, double acconto)
    : Spedizione(idPacco, dest, ind, p) // Passiamo i dati comuni alla classe base
{
    // Salviamo i dati specifici del Group Buy
    dataArrivoPrevista = data;
    idLottoProduzione = lotto;
    accontoVersato = acconto;
}

// 2. POLIMORFISMO: Calcolo del costo
// Essendo un Group Buy, applichiamo una tariffa agevolata sul peso
double SpedizioneGroupBuyInbound::calcolaCostoSpedizione() const {
    double tariffaAgevolataAlKg = 2.50;
    return getPeso() * tariffaAgevolataAlKg;
}

// 3. POLIMORFISMO: Il Manifesto testuale
// Usiamo il metodo .toString("dd/MM/yyyy") di QDate per mostrare la data in formato italiano (giorno/mese/anno)
QString SpedizioneGroupBuyInbound::getManifestoSpedizione() const {
    return QString("LOGISTICA GROUP BUY (PRE-ORDINE)\n"
                   "ID Lotto: %1\n"
                   "Data Arrivo Prevista: %2\n"
                   "Totale Acconti Versati: %3 €")
           .arg(idLottoProduzione)
           .arg(dataArrivoPrevista.toString("dd/MM/yyyy")) // Converte la data in testo leggibile
           .arg(accontoVersato);
}