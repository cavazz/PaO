#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QCloseEvent>
#include "HubLogistica.h"
#include "ListaSpedizioniWidget.h"
#include "DettaglioSpedizioneWidget.h"
#include "FormSpedizioneWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* evento) override;

private slots:
    void apriFormNuova();
    void apriDettaglio(const QString& id);
    void apriModifica(const QString& id);
    void eliminaSpedizione(const QString& id);
    void salvaDaForm();
    void tornaAllaLista();
    void mostraCampoRicerca();

    void nuovoProgetto();
    void apriFile();
    bool salvaFile();
    bool salvaFileComeNuovo();

private:
    void creaMenu();
    void aggiornaLista();
    void impostaTitoloFinestra();
    bool chiediConfermaSeModifichePendenti();

    HubLogistica hub;
    QString percorsoFileCorrente;
    bool modificheNonSalvate;

    QStackedWidget* stackPagine;
    ListaSpedizioniWidget* paginaLista;
    DettaglioSpedizioneWidget* paginaDettaglio;
    FormSpedizioneWidget* paginaForm;

    enum Pagina { PaginaLista = 0, PaginaDettaglio = 1, PaginaForm = 2 };
};

#endif // MAINWINDOW_H
