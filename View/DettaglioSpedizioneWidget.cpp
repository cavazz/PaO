#include "DettaglioSpedizioneWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QPixmap>

DettaglioSpedizioneWidget::DettaglioSpedizioneWidget(QWidget* parent)
    : QWidget(parent)
{
    labelIntestazione = new QLabel(this);
    QFont fontIntestazione = labelIntestazione->font();
    fontIntestazione.setPointSize(fontIntestazione.pointSize() + 2);
    fontIntestazione.setBold(true);
    labelIntestazione->setFont(fontIntestazione);

    labelImmagine = new QLabel(this);
    labelImmagine->setFixedSize(150, 150);
    labelImmagine->setAlignment(Qt::AlignCenter);

    testoManifesto = new QTextEdit(this);
    testoManifesto->setReadOnly(true);

    bottoneModifica = new QPushButton("Modifica", this);
    bottoneElimina = new QPushButton("Elimina", this);
    bottoneIndietro = new QPushButton("Indietro", this);

    QHBoxLayout* layoutBottoni = new QHBoxLayout();
    layoutBottoni->addWidget(bottoneIndietro);
    layoutBottoni->addStretch();
    layoutBottoni->addWidget(bottoneModifica);
    layoutBottoni->addWidget(bottoneElimina);

    QHBoxLayout* layoutContenuto = new QHBoxLayout();
    layoutContenuto->addWidget(labelImmagine);
    layoutContenuto->addWidget(testoManifesto);

    QVBoxLayout* layoutPrincipale = new QVBoxLayout(this);
    layoutPrincipale->addWidget(labelIntestazione);
    layoutPrincipale->addLayout(layoutContenuto);
    layoutPrincipale->addLayout(layoutBottoni);

    connect(bottoneModifica, &QPushButton::clicked, this, [this]() {
        emit richiestaModifica(idCorrente);
    });
    connect(bottoneElimina, &QPushButton::clicked, this, [this]() {
        emit richiestaEliminazione(idCorrente);
    });
    connect(bottoneIndietro, &QPushButton::clicked, this, &DettaglioSpedizioneWidget::richiestaIndietro);
}

void DettaglioSpedizioneWidget::mostraSpedizione(const Spedizione* spedizione) {
    if (spedizione == nullptr) {
        idCorrente.clear();
        labelIntestazione->setText("");
        labelImmagine->clear();
        testoManifesto->setPlainText("");
        return;
    }

    idCorrente = spedizione->getId();
    labelIntestazione->setText(QString("%1 - %2").arg(spedizione->getId(), spedizione->getProdotto()));

    QString percorsoImmagine = spedizione->getImmagine();
    if(percorsoImmagine.isEmpty()){
        labelImmagine->clear();
    } else {
        QPixmap immagine(percorsoImmagine);
        if(immagine.isNull()){
            labelImmagine->setText("Immagine\nnon trovata");
        } else {
            labelImmagine->setPixmap(immagine.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

    QString intestazioneDettagli = QString("Destinatario: %1\nIndirizzo: %2\nPeso: %3 kg\n\n")
                                        .arg(spedizione->getDestinatario())
                                        .arg(spedizione->getIndirizzo())
                                        .arg(spedizione->getPeso());

    testoManifesto->setPlainText(intestazioneDettagli + spedizione->getManifestoSpedizione());
}
