#include "HubLogistica.h"

HubLogistica::HubLogistica() {}

HubLogistica::~HubLogistica() {
    svuota();
}

void HubLogistica::svuota() {
    for (Spedizione* s : elencoSpedizioni) {
        delete s;
    }
    elencoSpedizioni.clear();
}

bool HubLogistica::aggiungiSpedizione(Spedizione* spedizione) {
    if (spedizione == nullptr) return false;

    if(cercaSpedizione(spedizione->getId()) != nullptr){
        return false;
    }

    elencoSpedizioni.push_back(spedizione);
    return true;
}

bool HubLogistica::rimuoviSpedizione(const QString& id) {
    for (auto it = elencoSpedizioni.begin(); it != elencoSpedizioni.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            elencoSpedizioni.erase(it);
            return true;
        }
    }
    return false;
}

Spedizione* HubLogistica::cercaSpedizione(const QString& id) const {
    for (Spedizione* s : elencoSpedizioni) {
        if (s->getId() == id) {
            return s;
        }
    }
    return nullptr;
}

const std::vector<Spedizione*>& HubLogistica::getElencoSpedizioni() const{
    return elencoSpedizioni;
}
