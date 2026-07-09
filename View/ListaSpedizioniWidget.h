#ifndef LISTASPEDIZIONIWIDGET_H
#define LISTASPEDIZIONIWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include "Spedizione.h"

class ListaSpedizioniWidget : public QWidget {
    Q_OBJECT

public:
    explicit ListaSpedizioniWidget(QWidget* parent = nullptr);

    void aggiornaElenco(const std::vector<Spedizione*>& spedizioni);
    QString testoRicerca() const;
    void impostaFocusRicerca();

signals:
    void richiestaNuova();
    void richiestaDettaglio(const QString& id);
    void ricercaCambiata(const QString& testo);

private slots:
    void onElementoSelezionato();

private:
    QLineEdit* campoRicerca;
    QListWidget* listaWidget;
    QPushButton* bottoneNuova;
    QLabel* labelRisultati;
};

#endif // LISTASPEDIZIONIWIDGET_H
