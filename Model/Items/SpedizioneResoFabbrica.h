#ifndef SPEDIZIONERESOFABBRICA_H
#define SPEDIZIONERESOFABBRICA_H

#include "Spedizione.h"

class SpedizioneResoFabbrica : public Spedizione {
public:
    SpedizioneResoFabbrica(QString idPacco, QString dest, QString ind, double p, QString prodotto, QString immagine,
                            QString rma, bool garanzia, QString motivoReso);

    QString getManifestoSpedizione() const override;
    QJsonObject toJson() const override;

private:
    QString codiceRMA;
    bool copertoDaGaranzia;
    QString motivoReso;
};

#endif // SPEDIZIONERESOFABBRICA_H
