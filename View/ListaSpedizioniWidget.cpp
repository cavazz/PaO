#include "ListaSpedizioniWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ListaSpedizioniWidget::ListaSpedizioniWidget(QWidget* parent)
    : QWidget(parent)
{
    campoRicerca = new QLineEdit(this);
    campoRicerca->setPlaceholderText("Cerca per id, prodotto, destinatario o indirizzo...");
    campoRicerca->setClearButtonEnabled(true);

    listaWidget = new QListWidget(this);

    bottoneNuova = new QPushButton("Nuova Spedizione", this);

    labelRisultati = new QLabel(this);

    QHBoxLayout* layoutRicerca = new QHBoxLayout();
    layoutRicerca->addWidget(campoRicerca);
    layoutRicerca->addWidget(bottoneNuova);

    QVBoxLayout* layoutPrincipale = new QVBoxLayout(this);
    layoutPrincipale->addLayout(layoutRicerca);
    layoutPrincipale->addWidget(listaWidget);
    layoutPrincipale->addWidget(labelRisultati);

    connect(campoRicerca, &QLineEdit::textChanged, this, &ListaSpedizioniWidget::ricercaCambiata);
    connect(bottoneNuova, &QPushButton::clicked, this, &ListaSpedizioniWidget::richiestaNuova);
    connect(listaWidget, &QListWidget::itemDoubleClicked, this, &ListaSpedizioniWidget::onElementoSelezionato);
}

void ListaSpedizioniWidget::aggiornaElenco(const std::vector<Spedizione*>& spedizioni) {
    listaWidget->clear();

    for (const Spedizione* s : spedizioni) {
        QString tipo = s->toJson().value("tipo").toString();
        QString testo = QString("%1  [%2]\n%3 - %4 (%5)")
                             .arg(s->getId(), tipo, s->getDestinatario(), s->getIndirizzo(), s->getProdotto());

        QListWidgetItem* item = new QListWidgetItem(testo, listaWidget);
        item->setData(Qt::UserRole, s->getId());
    }

    labelRisultati->setText(QString("%1 spedizion%2 trovat%3")
                                 .arg(spedizioni.size())
                                 .arg(spedizioni.size() == 1 ? "e" : "i")
                                 .arg(spedizioni.size() == 1 ? "a" : "e"));
}

QString ListaSpedizioniWidget::testoRicerca() const {
    return campoRicerca->text();
}

void ListaSpedizioniWidget::impostaFocusRicerca() {
    campoRicerca->setFocus();
    campoRicerca->selectAll();
}

void ListaSpedizioniWidget::onElementoSelezionato() {
    QListWidgetItem* item = listaWidget->currentItem();
    if(item == nullptr){
        return;
    }
    emit richiestaDettaglio(item->data(Qt::UserRole).toString());
}
