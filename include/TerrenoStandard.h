// PIETRO TRABUIO

#ifndef PROGETTO_FINALE_TERRENOSTANDARD_H
#define PROGETTO_FINALE_TERRENOSTANDARD_H

#include "Terreno.h"

/**
 * Classe derivata da Terreno, rappresenta un terreno di classe standard
 */
class TerrenoStandard : public Terreno{
private:
    // prezzi relativi a un terreno di classe standard
    constexpr static int ACQUISTO_TERRENO = 10;
    constexpr static int ACQUISTO_CASA = 5;
    constexpr static int ACQUISTO_ALBERGO = 5;
    constexpr static int PERNOTTAMENTO_CASA = 4;
    constexpr static int PERNOTTAMENTO_ALBERGO = 8;
public:
    /**
     * costruttore parametrico
     * utilizza il costruttore di Terreno impostando il TipoCasella a STANDARD
     * @param indiceCasella l'indice della casella nel tabellone
     */
    explicit TerrenoStandard(int indiceCasella): Terreno{indiceCasella, TipoCasella::STANDARD}{}

    // override metodi get dei prezzi
    int getPrezzoAcquistoTerreno() const override{ return ACQUISTO_TERRENO;}
    int getPrezzoAcquistoCasa() const override{return ACQUISTO_CASA;}
    int getPrezzoAcquistoAlbergo() const override{return ACQUISTO_ALBERGO;}
    int getPrezzoPernottamentoCasa() const override{return PERNOTTAMENTO_CASA;}
    int getPrezzoPernottamentoAlbergo() const override{return PERNOTTAMENTO_ALBERGO;}
};

#endif //PROGETTO_FINALE_TERRENOSTANDARD_H
