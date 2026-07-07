#include <QCoreApplication>
#include <QDebug>
#include "Model/Memory/HubLogistica.h"
#include "Model/JSON/JsonConverter.h"
#include "Model/JSON/JsonFile.h"

// Includiamo i file veri di Andrea
#include "Model/Items/Spedizione.h"
#include "Model/Items/SpedizioneStandard.h" 
// #include "Model/Items/SpedizioneEspressa.h" // Scommentalo se hai anche questo file

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qDebug() << "--- START TEST REALE COFFEE KEYS LOGISTICS ---";

    // 1. Creiamo l'Hub logistico (il tuo Manager)
    HubLogistica hub;

    // 2. Creiamo le spedizioni reali usando le classi di Andrea
    // Nota: Adatta i parametri del costruttore (es. "SPED001", "Roma", ecc.) 
    // in base a come Andrea ha definito il costruttore in SpedizioneStandard.h
    Spedizione* s1 = new SpedizioneStandard("SPED001", "Roma", 15.5);
    Spedizione* s2 = new SpedizioneStandard("SPED002", "Milano", 5.0);
    Spedizione* s3 = new SpedizioneStandard("SPED001", "Napoli", 2.0); // Duplicato di ID per test

    // 3. Testiamo l'inserimento nell'Hub
    qDebug() << "Aggiungo SPED001:" << hub.aggiungiSpedizione(s1); // Deve dare true
    qDebug() << "Aggiungo SPED002:" << hub.aggiungiSpedizione(s2); // Deve dare true
    
    // Il tuo manager dovrebbe rifiutare questo perché l'ID esiste già
    bool aggiuntoDuplicato = hub.aggiungiSpedizione(s3);
    qDebug() << "Tentativo duplicato SPED001:" << aggiuntoDuplicato; 
    if (!aggiuntoDuplicato) {
        delete s3; // Evitiamo memory leak visto che l'hub lo ha rifiutato
    }

    // 4. Verifichiamo il totale in memoria
    qDebug() << "Totale spedizioni nell'Hub:" << hub.getElencoSpedizioni().size();

    // 5. Testiamo il salvataggio su file JSON
    qDebug() << "Generazione JSON in corso...";
    QJsonObject jsonHub = JsonConverter::hubToJson(hub);
    
    QString percorsoFile = "spedizioni_reali.json";
    bool salvato = JsonFile::salva(percorsoFile, jsonHub);
    qDebug() << "Salvataggio su file" << percorsoFile << ":" << (salvato ? "SUCCESS" : "FAILED");

    qDebug() << "--- FINE TEST ---";
    return 0;
}