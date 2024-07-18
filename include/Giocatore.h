// NICOLÒ FIORANZATO

#ifndef PROGETTO_FINALE_GIOCATORE_H
#define PROGETTO_FINALE_GIOCATORE_H

#include <string>
#include <fstream>
#include "Terreno.h"
#include "Upgrade.h"
#include "Tabellone.h"

class Casella;
class Gioco;

/**
 * Classe virtuale pura per i giocatori, contiene metodi per comprare e migliorare terreni
 */

constexpr int FIORINI_INIZIALI = 100; // fiorini iniziali di ogni giocatore

class Giocatore{
protected:
    int id; // id del giocatore [1-4]
    int fiorini = FIORINI_INIZIALI; // fiorini iniziali di ogni giocatore
    int indiceCasella = 14; // indice della casella (default indice casella di partenza)
public:
    /**
     * costruttore parametrico
     * @param id identificativo del giocatore [1-4]
     */
    explicit Giocatore(int id): id{id}{}

    /**
     * metodo che consente di ricevere dei fiorini per un pagamento da un altro giocatore
     * o per ricevere il 20 fiorini al passaggio dal via
     */
    void riceviPagamento(int pagamento){
        this->fiorini += pagamento;
    }

    // metodi virtuali puri per comprare e migliorare un terreno
    virtual void compraTerreno(Casella&, Gioco&) = 0;
    virtual void miglioraTerreno(Casella&, Gioco&) = 0;

    // metodo per pagare il pernottamento
    void pagaPernottamento(Casella&, Giocatore&);

    // tira 2 dadi valori [2-12]
    int tiraDadi() const;

    // metodi getter e setter
    int getId() const {
        return id;
    }
    int getFiorini() const {
        return fiorini;
    }
    int getIndiceCasella() const {
        return indiceCasella;
    }
    void setIndiceCasella(int indiceCasella) {
        this->indiceCasella = indiceCasella;
    }
};

/**
 * scrive sul file di log il messaggio passato in input
 */
void scriviLog(const std::string&);

#endif //PROGETTO_FINALE_GIOCATORE_H
