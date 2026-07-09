#ifndef HUBLOGISTICA_H
#define HUBLOGISTICA_H

#include <vector>
#include <QString>
#include "Spedizione.h"

class HubLogistica {
public:
    HubLogistica();
    ~HubLogistica();

    bool aggiungiSpedizione(Spedizione* spedizione);
    bool rimuoviSpedizione(const QString& id);
    Spedizione* cercaSpedizione(const QString& id) const;
    const std::vector<Spedizione*>& getElencoSpedizioni() const;
    void svuota();

private:
    std::vector<Spedizione*> elencoSpedizioni;
};

#endif // HUBLOGISTICA_H
