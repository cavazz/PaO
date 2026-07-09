#ifndef JSONFILE_H
#define JSONFILE_H

#include <QString>
#include <QJsonDocument>

class JsonFile {
public:
    static bool scriviFile(const QString& percorso, const QJsonDocument& documento);
    static QJsonDocument leggiFile(const QString& percorso, bool& ok);
};

#endif // JSONFILE_H
