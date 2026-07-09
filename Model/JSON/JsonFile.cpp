#include "JsonFile.h"
#include <QFile>
#include <QIODevice>
#include <QJsonParseError>

bool JsonFile::scriviFile(const QString& percorso, const QJsonDocument& documento) {
    QFile file(percorso);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    file.write(documento.toJson());
    file.close();
    return true;
}

QJsonDocument JsonFile::leggiFile(const QString& percorso, bool& ok) {
    QFile file(percorso);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ok = false;
        return QJsonDocument();
    }

    QByteArray dati = file.readAll();
    file.close();

    QJsonParseError errore;
    QJsonDocument documento = QJsonDocument::fromJson(dati, &errore);
    ok = (errore.error == QJsonParseError::NoError);
    return documento;
}
