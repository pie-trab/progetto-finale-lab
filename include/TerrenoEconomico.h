// PIETRO TRABUIO

#ifndef PROGETTO_FINALE_TERRENOECONOMICO_H
#define PROGETTO_FINALE_TERRENOECONOMICO_H

#include "Terreno.h"

/**
 * Classe derivata da Terreno, rappresenta un terreno di classe economica
 */
class TerrenoEconomico : public Terreno{
private:
    // prezzi relativi a un terreno di classe economica
    constexpr static int ACQUISTO_TERRENO = 6;
    constexpr static int ACQUISTO_CASA = 3;
    constexpr static int ACQUISTO_ALBERGO = 3;
    constexpr static int PERNOTTAMENTO_CASA = 2;
    constexpr static int PERNOTTAMENTO_ALBERGO = 4;
public:
    /**
     * costruttore parametrico
     * utilizza il costruttore di Terreno impostando il TipoCasella a ECONOMICA
     * @param indiceCasella l'indice della casella nel tabellone
     */
    explicit TerrenoEconomico(int indiceCasella): Terreno{indiceCasella, TipoCasella::ECONOMICA}{}

    // override metodi get dei prezzi
    int getPrezzoAcquistoTerreno() const override{ return ACQUISTO_TERRENO;}
    int getPrezzoAcquistoCasa() const override{return ACQUISTO_CASA;}
    int getPrezzoAcquistoAlbergo() const override{return ACQUISTO_ALBERGO;}
    int getPrezzoPernottamentoCasa() const override{return PERNOTTAMENTO_CASA;}
    int getPrezzoPernottamentoAlbergo() const override{return PERNOTTAMENTO_ALBERGO;}
};

#endif //PROGETTO_FINALE_TERRENOECONOMICO_H
