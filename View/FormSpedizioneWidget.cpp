#include "FormSpedizioneWidget.h"
#include "SpedizioneClientiStandard.h"
#include "SpedizioneClientiEspressa.h"
#include "SpedizioneReviewerSponsor.h"
#include "SpedizioneRifornimentoStock.h"
#include "SpedizioneResoFabbrica.h"
#include "SpedizioneGroupBuyInbound.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFont>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QFile>

FormSpedizioneWidget::FormSpedizioneWidget(QWidget* parent)
    : QWidget(parent), modificaAttiva(false)
{
    labelTitolo = new QLabel(this);
    QFont fontTitolo = labelTitolo->font();
    fontTitolo.setPointSize(fontTitolo.pointSize() + 2);
    fontTitolo.setBold(true);
    labelTitolo->setFont(fontTitolo);

    campoId = new QLineEdit(this);
    campoProdotto = new QLineEdit(this);
    campoDestinatario = new QLineEdit(this);
    campoIndirizzo = new QLineEdit(this);

    campoPeso = new QDoubleSpinBox(this);
    campoPeso->setRange(0.0, 100000.0);
    campoPeso->setDecimals(2);
    campoPeso->setSuffix(" kg");

    bottoneImmagine = new QPushButton("Sfoglia...", this);
    connect(bottoneImmagine, &QPushButton::clicked, this, &FormSpedizioneWidget::immagineSelezionata);

    comboTipo = new QComboBox(this);
    comboTipo->addItem("Cliente Standard", "ClientiStandard");
    comboTipo->addItem("Cliente Espressa", "ClientiEspressa");
    comboTipo->addItem("Reviewer / Sponsor", "ReviewerSponsor");
    comboTipo->addItem("Rifornimento Stock", "RifornimentoStock");
    comboTipo->addItem("Reso Fabbrica", "ResoFabbrica");
    comboTipo->addItem("Group Buy Inbound", "GroupBuyInbound");

    QFormLayout* layoutComuni = new QFormLayout();
    layoutComuni->addRow("ID Pacco:", campoId);
    layoutComuni->addRow("Prodotto:", campoProdotto);
    layoutComuni->addRow("Destinatario:", campoDestinatario);
    layoutComuni->addRow("Indirizzo:", campoIndirizzo);
    layoutComuni->addRow("Peso:", campoPeso);
    layoutComuni->addRow("Immagine:", bottoneImmagine);
    layoutComuni->addRow("Tipo Spedizione:", comboTipo);

    creaPaginheSpecifiche();

    QGroupBox* boxSpecifico = new QGroupBox("Dettagli Specifici", this);
    QVBoxLayout* layoutBoxSpecifico = new QVBoxLayout(boxSpecifico);
    layoutBoxSpecifico->addWidget(paginePersonalizzate);

    bottoneSalva = new QPushButton("Salva", this);
    bottoneAnnulla = new QPushButton("Annulla", this);

    QHBoxLayout* layoutBottoni = new QHBoxLayout();
    layoutBottoni->addStretch();
    layoutBottoni->addWidget(bottoneAnnulla);
    layoutBottoni->addWidget(bottoneSalva);

    QVBoxLayout* layoutPrincipale = new QVBoxLayout(this);
    layoutPrincipale->addWidget(labelTitolo);
    layoutPrincipale->addLayout(layoutComuni);
    layoutPrincipale->addWidget(boxSpecifico);
    layoutPrincipale->addStretch();
    layoutPrincipale->addLayout(layoutBottoni);

    connect(comboTipo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FormSpedizioneWidget::onTipoCambiato);
    connect(bottoneSalva, &QPushButton::clicked, this, &FormSpedizioneWidget::salvaCliccato);
    connect(bottoneAnnulla, &QPushButton::clicked, this, &FormSpedizioneWidget::annullaCliccato);
}

void FormSpedizioneWidget::creaPaginheSpecifiche() {
    paginePersonalizzate = new QStackedWidget(this);

    QWidget* paginaStd = new QWidget();
    campoCorriereStd = new QLineEdit(paginaStd);
    QFormLayout* layoutStd = new QFormLayout(paginaStd);
    layoutStd->addRow("Corriere:", campoCorriereStd);
    paginePersonalizzate->addWidget(paginaStd);

    QWidget* paginaEsp = new QWidget();
    campoCorriereEsp = new QLineEdit(paginaEsp);
    campoOreEsp = new QSpinBox(paginaEsp);
    campoOreEsp->setRange(1, 999);
    campoOreEsp->setSuffix(" ore");
    QFormLayout* layoutEsp = new QFormLayout(paginaEsp);
    layoutEsp->addRow("Corriere:", campoCorriereEsp);
    layoutEsp->addRow("Consegna Garantita Entro:", campoOreEsp);
    paginePersonalizzate->addWidget(paginaEsp);

    QWidget* paginaReviewer = new QWidget();
    campoReviewer = new QLineEdit(paginaReviewer);
    campoCampagna = new QLineEdit(paginaReviewer);
    campoValoreOmaggio = new QDoubleSpinBox(paginaReviewer);
    campoValoreOmaggio->setRange(0.0, 100000.0);
    campoValoreOmaggio->setSuffix(" €");
    QFormLayout* layoutReviewer = new QFormLayout(paginaReviewer);
    layoutReviewer->addRow("Nome Reviewer:", campoReviewer);
    layoutReviewer->addRow("Codice Campagna:", campoCampagna);
    layoutReviewer->addRow("Valore Prodotto Omaggio:", campoValoreOmaggio);
    paginePersonalizzate->addWidget(paginaReviewer);

    QWidget* paginaStock = new QWidget();
    campoFornitore = new QLineEdit(paginaStock);
    campoOrdineAcquisto = new QLineEdit(paginaStock);
    campoQuantitaColli = new QSpinBox(paginaStock);
    campoQuantitaColli->setRange(1, 99999);
    QFormLayout* layoutStock = new QFormLayout(paginaStock);
    layoutStock->addRow("Fornitore:", campoFornitore);
    layoutStock->addRow("Numero Ordine Acquisto:", campoOrdineAcquisto);
    layoutStock->addRow("Quantità Colli:", campoQuantitaColli);
    paginePersonalizzate->addWidget(paginaStock);

    QWidget* paginaReso = new QWidget();
    campoRMA = new QLineEdit(paginaReso);
    campoGaranzia = new QCheckBox("Coperta da garanzia", paginaReso);
    campoMotivoReso = new QLineEdit(paginaReso);
    QFormLayout* layoutReso = new QFormLayout(paginaReso);
    layoutReso->addRow("Codice RMA:", campoRMA);
    layoutReso->addRow(campoGaranzia);
    layoutReso->addRow("Motivo Reso:", campoMotivoReso);
    paginePersonalizzate->addWidget(paginaReso);

    QWidget* paginaGroupBuy = new QWidget();
    campoDataArrivo = new QDateEdit(paginaGroupBuy);
    campoDataArrivo->setCalendarPopup(true);
    campoDataArrivo->setDate(QDate::currentDate());
    campoLotto = new QLineEdit(paginaGroupBuy);
    campoAcconto = new QDoubleSpinBox(paginaGroupBuy);
    campoAcconto->setRange(0.0, 1000000.0);
    campoAcconto->setSuffix(" €");
    QFormLayout* layoutGroupBuy = new QFormLayout(paginaGroupBuy);
    layoutGroupBuy->addRow("Data Arrivo Prevista:", campoDataArrivo);
    layoutGroupBuy->addRow("ID Lotto Produzione:", campoLotto);
    layoutGroupBuy->addRow("Acconto Versato:", campoAcconto);
    paginePersonalizzate->addWidget(paginaGroupBuy);
}

void FormSpedizioneWidget::onTipoCambiato(int indice) {
    paginePersonalizzate->setCurrentIndex(indice);
}

void FormSpedizioneWidget::immagineSelezionata() {
    QString filePath = QFileDialog::getOpenFileName(this, "Seleziona Immagine", QString(),
                                                     "Immagini (*.png *.jpg *.jpeg *.bmp)");
    if(filePath.isEmpty()){
        return;
    }

    QDir dir;
    if(!dir.exists("Resources")){
        dir.mkpath("Resources");
    }

    // copio il file dentro Resources, così anche se sposto o cancello l'originale l'immagine resta
    QString nomeFile = QFileInfo(filePath).fileName();
    QString percorsoDestinazione = "Resources/" + nomeFile;

    if (!QFile::exists(percorsoDestinazione)) {
        if (!QFile::copy(filePath, percorsoDestinazione)) {
            QMessageBox::warning(this, "Errore", "Impossibile copiare l'immagine selezionata.");
            return;
        }
    }

    percorsoImmagineSelezionata = percorsoDestinazione;
    bottoneImmagine->setText(nomeFile);
}

void FormSpedizioneWidget::impostaModalitaCreazione() {
    labelTitolo->setText("Nuova Spedizione");

    campoId->clear();
    campoProdotto->clear();
    campoDestinatario->clear();
    campoIndirizzo->clear();
    campoPeso->setValue(0.0);
    percorsoImmagineSelezionata.clear();
    bottoneImmagine->setText("Sfoglia...");

    comboTipo->setEnabled(true);
    comboTipo->setCurrentIndex(0);
    paginePersonalizzate->setCurrentIndex(0);

    campoCorriereStd->clear();
    campoCorriereEsp->clear();
    campoOreEsp->setValue(24);
    campoReviewer->clear();
    campoCampagna->clear();
    campoValoreOmaggio->setValue(0.0);
    campoFornitore->clear();
    campoOrdineAcquisto->clear();
    campoQuantitaColli->setValue(1);
    campoRMA->clear();
    campoGaranzia->setChecked(false);
    campoMotivoReso->clear();
    campoDataArrivo->setDate(QDate::currentDate());
    campoLotto->clear();
    campoAcconto->setValue(0.0);

    idOriginale.clear();
    modificaAttiva = false;
}

void FormSpedizioneWidget::impostaModalitaModifica(const QJsonObject& dati) {
    labelTitolo->setText("Modifica Spedizione");

    QString tipo = dati.value("tipo").toString();

    campoId->setText(dati.value("id").toString());
    campoProdotto->setText(dati.value("prodotto").toString());
    campoDestinatario->setText(dati.value("destinatario").toString());
    campoIndirizzo->setText(dati.value("indirizzo").toString());
    campoPeso->setValue(dati.value("peso").toDouble());

    percorsoImmagineSelezionata = dati.value("immagine").toString();
    bottoneImmagine->setText(percorsoImmagineSelezionata.isEmpty()
                                  ? "Sfoglia..."
                                  : QFileInfo(percorsoImmagineSelezionata).fileName());

    int indice = comboTipo->findData(tipo);
    if (indice < 0) {
        indice = 0;
    }
    comboTipo->setCurrentIndex(indice);
    comboTipo->setEnabled(false);
    paginePersonalizzate->setCurrentIndex(indice);

    popolaCampiSpecifici(tipo, dati);

    idOriginale = dati.value("id").toString();
    modificaAttiva = true;
}

void FormSpedizioneWidget::popolaCampiSpecifici(const QString& tipo, const QJsonObject& dati) {
    if (tipo == "ClientiStandard") {
        campoCorriereStd->setText(dati.value("corriere").toString());
    } else if (tipo == "ClientiEspressa") {
        campoCorriereEsp->setText(dati.value("corriere").toString());
        campoOreEsp->setValue(dati.value("oreConsegnaGarantite").toInt());
    } else if (tipo == "ReviewerSponsor") {
        campoReviewer->setText(dati.value("nomeReviewer").toString());
        campoCampagna->setText(dati.value("codiceCampagna").toString());
        campoValoreOmaggio->setValue(dati.value("valoreProdottoOmaggio").toDouble());
    } else if (tipo == "RifornimentoStock") {
        campoFornitore->setText(dati.value("fornitore").toString());
        campoOrdineAcquisto->setText(dati.value("numeroOrdineAcquisto").toString());
        campoQuantitaColli->setValue(dati.value("quantitaColli").toInt());
    } else if (tipo == "ResoFabbrica") {
        campoRMA->setText(dati.value("codiceRMA").toString());
        campoGaranzia->setChecked(dati.value("copertoDaGaranzia").toBool());
        campoMotivoReso->setText(dati.value("motivoReso").toString());
    } else if (tipo == "GroupBuyInbound") {
        QDate data = QDate::fromString(dati.value("dataArrivoPrevista").toString(), Qt::ISODate);
        campoDataArrivo->setDate(data.isValid() ? data : QDate::currentDate());
        campoLotto->setText(dati.value("idLottoProduzione").toString());
        campoAcconto->setValue(dati.value("accontoVersato").toDouble());
    }
}

Spedizione* FormSpedizioneWidget::costruisciSpedizione() const {
    QString id = campoId->text().trimmed();
    QString prodotto = campoProdotto->text().trimmed();
    QString destinatario = campoDestinatario->text().trimmed();
    QString indirizzo = campoIndirizzo->text().trimmed();
    double peso = campoPeso->value();

    if (id.isEmpty() || prodotto.isEmpty() || destinatario.isEmpty() || indirizzo.isEmpty()) {
        QMessageBox::warning(const_cast<FormSpedizioneWidget*>(this), "Dati mancanti",
                              "ID, prodotto, destinatario e indirizzo sono obbligatori.");
        return nullptr;
    }

    QString tipo = comboTipo->currentData().toString();

    if (tipo == "ClientiStandard") {
        return new SpedizioneClientiStandard(id, destinatario, indirizzo, peso, prodotto, percorsoImmagineSelezionata,
                                              campoCorriereStd->text());
    }
    if (tipo == "ClientiEspressa") {
        return new SpedizioneClientiEspressa(id, destinatario, indirizzo, peso, prodotto, percorsoImmagineSelezionata,
                                              campoCorriereEsp->text(), campoOreEsp->value());
    }
    if (tipo == "ReviewerSponsor") {
        return new SpedizioneReviewerSponsor(id, destinatario, indirizzo, peso, prodotto, percorsoImmagineSelezionata,
                                              campoReviewer->text(), campoCampagna->text(),
                                              campoValoreOmaggio->value());
    }
    if (tipo == "RifornimentoStock") {
        return new SpedizioneRifornimentoStock(id, destinatario, indirizzo, peso, prodotto, percorsoImmagineSelezionata,
                                                campoFornitore->text(), campoOrdineAcquisto->text(),
                                                campoQuantitaColli->value());
    }
    if (tipo == "ResoFabbrica") {
        return new SpedizioneResoFabbrica(id, destinatario, indirizzo, peso, prodotto, percorsoImmagineSelezionata,
                                           campoRMA->text(), campoGaranzia->isChecked(),
                                           campoMotivoReso->text());
    }
    if (tipo == "GroupBuyInbound") {
        return new SpedizioneGroupBuyInbound(id, destinatario, indirizzo, peso, prodotto, percorsoImmagineSelezionata,
                                              campoDataArrivo->date(), campoLotto->text(),
                                              campoAcconto->value());
    }

    return nullptr;
}

QString FormSpedizioneWidget::idInModifica() const {
    return idOriginale;
}

bool FormSpedizioneWidget::inModalitaModifica() const {
    return modificaAttiva;
}
