// PIETRO TRABUIO

#ifndef PROGETTO_FINALE_GIOCATORECOMPUTER_H
#define PROGETTO_FINALE_GIOCATORECOMPUTER_H

#include "Giocatore.h"

/**
 * Classe che eredita Giocatore e che rappresenta un giocatore di tipologia 'computer'
 */
class GiocatoreComputer : public Giocatore{
public:
    /**
     * costruttore parametrico
     * @param id l'id del giocatore
     */
    explicit GiocatoreComputer(int id): Giocatore(id){}

    /**
     * override di compra terreno, permette l'acquisto di un terreno
     */
    void compraTerreno(Casella&, Gioco&) override;

    /**
     * ooverride di migliora terreno, permette di migliorare un terreno
     */
    void miglioraTerreno(Casella&, Gioco& ) override;
};

#endif //PROGETTO_FINALE_GIOCATORECOMPUTER_H
