#include "Spedizione.h"

Spedizione::Spedizione(QString idPacco, QString dest, QString ind, double p, QString prod, QString img)
    : id(idPacco), destinatario(dest), indirizzo(ind), peso(p), prodotto(prod), immagine(img)
{}

Spedizione::~Spedizione() {}

QString Spedizione::getId() const{
    return id;
}

QString Spedizione::getDestinatario() const {
    return destinatario;
}

QString Spedizione::getIndirizzo() const{
    return indirizzo;
}

double Spedizione::getPeso() const {
    return peso;
}

QString Spedizione::getProdotto() const{
    return prodotto;
}

QString Spedizione::getImmagine() const {
    return immagine;
}

QJsonObject Spedizione::serializzaComuni(const QString& tipo) const {
    QJsonObject obj;
    obj["tipo"]=tipo;
    obj["id"] = id;
    obj["destinatario"] = destinatario;
    obj["indirizzo"] = indirizzo;
    obj["peso"] = peso;
    obj["prodotto"] = prodotto;
    obj["immagine"] = immagine;
    return obj;
}
