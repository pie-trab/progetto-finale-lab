// NICOLÒ FIORANZATO

#ifndef PROGETTO_FINALE_GIOCO_H
#define PROGETTO_FINALE_GIOCO_H

#include <list>
#include <vector>
#include <memory>
#include <algorithm>
#include "Terreno.h"
#include "Giocatore.h"
#include "Tabellone.h"
#include "GiocatoreUmano.h"
#include "GiocatoreComputer.h"

/**
 * Classe che gestisce i metodi per lo svolgimento del gioco
 */
class Gioco{
private:
    int turniCount = 0; // numero di turni effettuati
    std::list<int> ordineTurni; // lista che indica l'ordine dei lanci dei giocatori
                                // il primo elemento indica il giocatore a cui tocca tirare i dadi
                                // la lista inoltre ruota per dare le priorità ai giocatori successivi nell'ordine stabilito
    std::vector<std::unique_ptr<Giocatore>> giocatori; // vettore contenente dei puntatori ai giocatori della partita
    bool modalita; // true se gioca un umano, false se giocano solo computer
    Tabellone tabellone; // tabellone del gioco

public:
    // costruttore parametrico per la scelta della modalità (true o false)
    explicit Gioco(bool);

    // stampo quando richiesto l'attuale stato del tabellone, delle proprietà e dei fiorini di ogni giocatore
    void show();

    // metodo per l'avvio del gioco
    void avviaGioco();

    // muove il giocatore passato come parametro sul tabellone
    void muoviGiocatore(Giocatore&);

    // metodo per l'eliminazione di un giocatore
    void eliminaGiocatore(Giocatore&);

    /**
     * getFioriniGiocatori
     * @return una stringa contenente la lista dei giocatori con relativo saldo di fiorini
     */
    std::string getFioriniGiocatori() const;
};

#endif //PROGETTO_FINALE_GIOCO_H