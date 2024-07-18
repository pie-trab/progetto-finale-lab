// PIETRO TRABUIO

#ifndef PROGETTO_FINALE_GIOCATOREUMANO_H
#define PROGETTO_FINALE_GIOCATOREUMANO_H

#include "Giocatore.h"
#include "Gioco.h"

/**
 * Classe che eredita Giocatore e che rappresenta un giocatore di tipologia 'umano'
 */
class GiocatoreUmano : public Giocatore{
public:
    /**
     * costruttore parametrico
     * @param id l'id del giocatore
     */
    explicit GiocatoreUmano(int id): Giocatore(id){}

    /**
     * override di compra terreno, permette l'acquisto di un terreno
     */
    void compraTerreno(Casella&, Gioco&) override;

    /**
     * override di migliora terreno, permette di migliorare un terreno
     */
    void miglioraTerreno(Casella&, Gioco&) override;
};

#endif //PROGETTO_FINALE_GIOCATOREUMANO_H
