#ifndef DETTAGLIOSPEDIZIONEWIDGET_H
#define DETTAGLIOSPEDIZIONEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include "Spedizione.h"

class DettaglioSpedizioneWidget : public QWidget {
    Q_OBJECT

public:
    explicit DettaglioSpedizioneWidget(QWidget* parent = nullptr);

    void mostraSpedizione(const Spedizione* spedizione);

signals:
    void richiestaModifica(const QString& id);
    void richiestaEliminazione(const QString& id);
    void richiestaIndietro();

private:
    QLabel* labelIntestazione;
    QLabel* labelImmagine;
    QTextEdit* testoManifesto;
    QPushButton* bottoneModifica;
    QPushButton* bottoneElimina;
    QPushButton* bottoneIndietro;

    QString idCorrente;
};

#endif // DETTAGLIOSPEDIZIONEWIDGET_H
