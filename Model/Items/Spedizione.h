#ifndef SPEDIZIONE_H
#define SPEDIZIONE_H

#include <QString>
#include <QJsonObject>

class Spedizione {
public:
    Spedizione(QString idPacco, QString destinatario, QString indirizzo, double peso, QString prodotto, QString immagine);
    virtual ~Spedizione();

    QString getId() const;
    QString getDestinatario() const;
    QString getIndirizzo() const;
    double getPeso() const;
    QString getProdotto() const;
    QString getImmagine() const;

    virtual QString getManifestoSpedizione() const = 0;
    virtual QJsonObject toJson() const = 0;

protected:
    QJsonObject serializzaComuni(const QString& tipo) const;

    QString id;
    QString destinatario;
    QString indirizzo;
    double peso;
    QString prodotto;
    QString immagine;
};

#endif // SPEDIZIONE_H
