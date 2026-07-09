#ifndef FORMSPEDIZIONEWIDGET_H
#define FORMSPEDIZIONEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QStackedWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QJsonObject>
#include "Spedizione.h"

class FormSpedizioneWidget : public QWidget {
    Q_OBJECT

public:
    explicit FormSpedizioneWidget(QWidget* parent = nullptr);

    void impostaModalitaCreazione();
    void impostaModalitaModifica(const QJsonObject& dati);

    Spedizione* costruisciSpedizione() const;

    QString idInModifica() const;
    bool inModalitaModifica() const;

signals:
    void salvaCliccato();
    void annullaCliccato();

private slots:
    void onTipoCambiato(int indice);
    void immagineSelezionata();

private:
    void creaPaginheSpecifiche();
    void popolaCampiSpecifici(const QString& tipo, const QJsonObject& dati);

    QLabel* labelTitolo;
    QLineEdit* campoId;
    QLineEdit* campoProdotto;
    QLineEdit* campoDestinatario;
    QLineEdit* campoIndirizzo;
    QDoubleSpinBox* campoPeso;
    QPushButton* bottoneImmagine;
    QString percorsoImmagineSelezionata;
    QComboBox* comboTipo;
    QStackedWidget* paginePersonalizzate;

    QLineEdit* campoCorriereStd;

    QLineEdit* campoCorriereEsp;
    QSpinBox* campoOreEsp;

    QLineEdit* campoReviewer;
    QLineEdit* campoCampagna;
    QDoubleSpinBox* campoValoreOmaggio;

    QLineEdit* campoFornitore;
    QLineEdit* campoOrdineAcquisto;
    QSpinBox* campoQuantitaColli;

    QLineEdit* campoRMA;
    QCheckBox* campoGaranzia;
    QLineEdit* campoMotivoReso;

    QDateEdit* campoDataArrivo;
    QLineEdit* campoLotto;
    QDoubleSpinBox* campoAcconto;

    QPushButton* bottoneSalva;
    QPushButton* bottoneAnnulla;

    QString idOriginale;
    bool modificaAttiva;
};

#endif // FORMSPEDIZIONEWIDGET_H
