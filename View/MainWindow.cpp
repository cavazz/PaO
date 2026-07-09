#include "MainWindow.h"
#include "JsonReader.h"
#include "XmlPersistenza.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QAction>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), modificheNonSalvate(false)
{
    paginaLista = new ListaSpedizioniWidget(this);
    paginaDettaglio = new DettaglioSpedizioneWidget(this);
    paginaForm = new FormSpedizioneWidget(this);

    stackPagine = new QStackedWidget(this);
    stackPagine->addWidget(paginaLista);
    stackPagine->addWidget(paginaDettaglio);
    stackPagine->addWidget(paginaForm);
    setCentralWidget(stackPagine);

    creaMenu();

    connect(paginaLista, &ListaSpedizioniWidget::ricercaCambiata, this, [this](const QString&) { aggiornaLista(); });
    connect(paginaLista, &ListaSpedizioniWidget::richiestaNuova, this, &MainWindow::apriFormNuova);
    connect(paginaLista, &ListaSpedizioniWidget::richiestaDettaglio, this, &MainWindow::apriDettaglio);

    connect(paginaDettaglio, &DettaglioSpedizioneWidget::richiestaModifica, this, &MainWindow::apriModifica);
    connect(paginaDettaglio, &DettaglioSpedizioneWidget::richiestaEliminazione, this, &MainWindow::eliminaSpedizione);
    connect(paginaDettaglio, &DettaglioSpedizioneWidget::richiestaIndietro, this, &MainWindow::tornaAllaLista);

    connect(paginaForm, &FormSpedizioneWidget::salvaCliccato, this, &MainWindow::salvaDaForm);
    connect(paginaForm, &FormSpedizioneWidget::annullaCliccato, this, &MainWindow::tornaAllaLista);

    resize(950, 650);
    aggiornaLista();
    impostaTitoloFinestra();
}

void MainWindow::creaMenu() {
    QMenu* menuFile = menuBar()->addMenu("&File");
    menuFile->addAction("&Nuovo Progetto", QKeySequence::New, this, &MainWindow::nuovoProgetto);
    menuFile->addAction("&Apri...", QKeySequence::Open, this, &MainWindow::apriFile);
    menuFile->addAction("&Salva", QKeySequence::Save, this, &MainWindow::salvaFile);
    menuFile->addAction("Salva &Come...", QKeySequence::SaveAs, this, &MainWindow::salvaFileComeNuovo);
    menuFile->addSeparator();
    menuFile->addAction("&Esci", QKeySequence::Quit, this, &QWidget::close);

    QMenu* menuSpedizione = menuBar()->addMenu("&Spedizione");
    menuSpedizione->addAction("&Nuova Spedizione...", QKeySequence("Ctrl+Shift+N"), this, &MainWindow::apriFormNuova);

    QMenu* menuModifica = menuBar()->addMenu("&Modifica");
    menuModifica->addAction("&Cerca", QKeySequence::Find, this, &MainWindow::mostraCampoRicerca);
}

void MainWindow::aggiornaLista() {
    QString filtro = paginaLista->testoRicerca().trimmed();

    if (filtro.isEmpty()) {
        paginaLista->aggiornaElenco(hub.getElencoSpedizioni());
        return;
    }

    std::vector<Spedizione*> filtrate;
    for (Spedizione* s : hub.getElencoSpedizioni()) {
        if (s->getId().contains(filtro, Qt::CaseInsensitive) ||
            s->getProdotto().contains(filtro, Qt::CaseInsensitive) ||
            s->getDestinatario().contains(filtro, Qt::CaseInsensitive) ||
            s->getIndirizzo().contains(filtro, Qt::CaseInsensitive)) {
            filtrate.push_back(s);
        }
    }
    paginaLista->aggiornaElenco(filtrate);
}

void MainWindow::apriFormNuova() {
    paginaForm->impostaModalitaCreazione();
    stackPagine->setCurrentIndex(PaginaForm);
}

void MainWindow::apriDettaglio(const QString& id) {
    Spedizione* s = hub.cercaSpedizione(id);
    if(s == nullptr){
        return;
    }
    paginaDettaglio->mostraSpedizione(s);
    stackPagine->setCurrentIndex(PaginaDettaglio);
}

void MainWindow::apriModifica(const QString& id) {
    Spedizione* s = hub.cercaSpedizione(id);
    if (s == nullptr) {
        return;
    }
    paginaForm->impostaModalitaModifica(s->toJson());
    stackPagine->setCurrentIndex(PaginaForm);
}

void MainWindow::eliminaSpedizione(const QString& id) {
    int risposta = QMessageBox::question(this, "Conferma Eliminazione",
                                          QString("Eliminare definitivamente la spedizione %1?").arg(id));
    if (risposta != QMessageBox::Yes) {
        return;
    }

    hub.rimuoviSpedizione(id);
    modificheNonSalvate = true;
    impostaTitoloFinestra();
    tornaAllaLista();
}

void MainWindow::salvaDaForm() {
    Spedizione* nuovo = paginaForm->costruisciSpedizione();
    if(nuovo == nullptr){
        return;
    }

    if (paginaForm->inModalitaModifica()) {
        QString idOriginale = paginaForm->idInModifica();
        if (nuovo->getId() != idOriginale && hub.cercaSpedizione(nuovo->getId()) != nullptr) {
            QMessageBox::warning(this, "ID Duplicato", "Esiste già una spedizione con questo ID.");
            delete nuovo;
            return;
        }
        // tolgo prima la vecchia versione, altrimenti se l'id non cambia aggiungiSpedizione la trova già presente e fallisce
        hub.rimuoviSpedizione(idOriginale);
        hub.aggiungiSpedizione(nuovo);
    } else {
        if (!hub.aggiungiSpedizione(nuovo)) {
            QMessageBox::warning(this, "ID Duplicato", "Esiste già una spedizione con questo ID.");
            delete nuovo;
            return;
        }
    }

    modificheNonSalvate = true;
    impostaTitoloFinestra();
    tornaAllaLista();
}

void MainWindow::tornaAllaLista() {
    aggiornaLista();
    stackPagine->setCurrentIndex(PaginaLista);
}

void MainWindow::mostraCampoRicerca() {
    stackPagine->setCurrentIndex(PaginaLista);
    paginaLista->impostaFocusRicerca();
}

bool MainWindow::chiediConfermaSeModifichePendenti() {
    if (!modificheNonSalvate) {
        return true;
    }

    int risposta = QMessageBox::question(this, "Modifiche Non Salvate",
                                          "Ci sono modifiche non salvate. Continuare comunque e perderle?",
                                          QMessageBox::Yes | QMessageBox::No);
    return risposta == QMessageBox::Yes;
}

void MainWindow::nuovoProgetto() {
    if (!chiediConfermaSeModifichePendenti()) {
        return;
    }

    hub.svuota();
    percorsoFileCorrente.clear();
    modificheNonSalvate = false;
    tornaAllaLista();
    impostaTitoloFinestra();
}

void MainWindow::apriFile() {
    if (!chiediConfermaSeModifichePendenti()) {
        return;
    }

    QString percorso = QFileDialog::getOpenFileName(this, "Apri File Spedizioni", QString(),
                                                     "File JSON (*.json);;File XML (*.xml)");
    if (percorso.isEmpty()) {
        return;
    }

    bool ok = false;
    bool formatoXml = percorso.endsWith(".xml", Qt::CaseInsensitive);
    std::vector<Spedizione*> caricate = formatoXml ? XmlPersistenza::caricaSpedizioni(percorso, ok)
                                                    : JsonReader::caricaSpedizioni(percorso, ok);
    if (!ok) {
        QMessageBox::critical(this, "Errore Caricamento", "Impossibile leggere o interpretare il file selezionato.");
        for (Spedizione* s : caricate) {
            delete s;
        }
        return;
    }

    hub.svuota();
    for (Spedizione* s : caricate) {
        if (!hub.aggiungiSpedizione(s)) {
            delete s;
        }
    }

    percorsoFileCorrente = percorso;
    modificheNonSalvate = false;
    tornaAllaLista();
    impostaTitoloFinestra();
}

bool MainWindow::salvaFile() {
    if (percorsoFileCorrente.isEmpty()) {
        return salvaFileComeNuovo();
    }

    bool formatoXml = percorsoFileCorrente.endsWith(".xml", Qt::CaseInsensitive);
    bool successo = formatoXml ? XmlPersistenza::salvaSpedizioni(percorsoFileCorrente, hub.getElencoSpedizioni())
                                : JsonReader::salvaSpedizioni(percorsoFileCorrente, hub.getElencoSpedizioni());
    if (!successo) {
        QMessageBox::critical(this, "Errore Salvataggio", "Impossibile scrivere sul file selezionato.");
        return false;
    }

    modificheNonSalvate = false;
    impostaTitoloFinestra();
    return true;
}

bool MainWindow::salvaFileComeNuovo() {
    QString filtroSelezionato;
    QString percorso = QFileDialog::getSaveFileName(this, "Salva File Spedizioni", QString(),
                                                     "File JSON (*.json);;File XML (*.xml)", &filtroSelezionato);
    if (percorso.isEmpty()) {
        return false;
    }

    if (!percorso.endsWith(".json", Qt::CaseInsensitive) && !percorso.endsWith(".xml", Qt::CaseInsensitive)) {
        percorso += filtroSelezionato.contains("xml", Qt::CaseInsensitive) ? ".xml" : ".json";
    }

    percorsoFileCorrente = percorso;
    return salvaFile();
}

void MainWindow::impostaTitoloFinestra() {
    QString nomeFile = percorsoFileCorrente.isEmpty() ? "nuovo progetto" : QFileInfo(percorsoFileCorrente).fileName();
    QString asterisco = modificheNonSalvate ? "*" : "";
    setWindowTitle(QString("Coffee Keys Logistics - %1%2").arg(nomeFile, asterisco));
}

void MainWindow::closeEvent(QCloseEvent* evento) {
    if (chiediConfermaSeModifichePendenti()) {
        evento->accept();
    } else {
        evento->ignore();
    }
}
