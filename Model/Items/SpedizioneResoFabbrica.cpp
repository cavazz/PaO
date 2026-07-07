#include "SpedizioneResoFabbrica.h"

// 1. IL COSTRUTTORE
SpedizioneResoFabbrica::SpedizioneResoFabbrica(QString idPacco, QString dest, QString ind, double p, 
                                               QString rma, bool garanzia, double costoDogana)
    : Spedizione(idPacco, dest, ind, p) 
{
    codiceRMA = rma;
    copertoDaGaranzia = garanzia;
    costoSpedizioneDoganaRitorno = costoDogana;
}

// 2. POLIMORFISMO: Calcolo del costo
double SpedizioneResoFabbrica::calcolaCostoSpedizione() const {
    // Se è coperto da garanzia (cioè se copertoDaGaranzia è "true")
    if (copertoDaGaranzia) {
        return 0.0; // Spedizione gratuita
    }
    // Altrimenti (se è "false"), si paga la dogana di ritorno
    return costoSpedizioneDoganaRitorno;
}

// 3. POLIMORFISMO: Il Manifesto testuale
QString SpedizioneResoFabbrica::getManifestoSpedizione() const {
    // Trasformiamo il "true/false" in un testo leggibile per l'utente (Sì/No)
    QString testoGaranzia = copertoDaGaranzia ? "Sì" : "No";

    return QString("RESO MERCE DIFETTOSA (OUTBOUND VERSO ASIA)\n"
                   "Codice RMA: %1\n"
                   "Coperto da Garanzia: %2\n"
                   "Costo Stimato Ritorno: %3 €")
           .arg(codiceRMA)
           .arg(testoGaranzia)
           .arg(calcolaCostoSpedizione()); // Richiamiamo il nostro stesso metodo per mostrare il costo finale!
}