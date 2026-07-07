#include "HubLogistica.h"

// Costruttore: inizializza il manager
HubLogistica::HubLogistica() {}

// Distruttore: pulisce la memoria occupata dai pacchi
HubLogistica::~HubLogistica() {
    for (Spedizione* s : elencoSpedizioni) {
        delete s; // Libera la memoria di ogni singolo oggetto spedizione
    }
    elencoSpedizioni.clear(); // Pulisce il vettore
}

// Aggiungi: programmato in modo difensivo
bool HubLogistica::aggiungiSpedizione(Spedizione* spedizione) {
    if (spedizione == nullptr) return false;
    
    // Controllo se l'ID esiste già per evitare duplicati
    if (cercaSpedizione(spedizione->getId()) != nullptr) {
        return false;
    }

    elencoSpedizioni.push_back(spedizione);
    return true;
}

// Cerca: restituisce il puntatore o nullptr se non trovato
Spedizione* HubLogistica::cercaSpedizione(const QString& id) const {
    for (Spedizione* s : elencoSpedizioni) {
        if (s->getId() == id) {
            return s;
        }
    }
    return nullptr;
}

// Getter: restituisce il riferimento costante (molto efficiente)
const std::vector<Spedizione*>& HubLogistica::getElencoSpedizioni() const {
    return elencoSpedizioni;
}