// PIETRO TRABUIO

#ifndef PROGETTO_FINALE_TERRENOLUSSO_H
#define PROGETTO_FINALE_TERRENOLUSSO_H

#include "Terreno.h"

/**
 * Classe derivata da Terreno, rappresenta un terreno di classe lusso
 */
class TerrenoLusso : public Terreno{
private:
    // prezzi relativi a un terreno di classe lusso
    constexpr static int ACQUISTO_TERRENO = 20;
    constexpr static int ACQUISTO_CASA = 10;
    constexpr static int ACQUISTO_ALBERGO = 10;
    constexpr static int PERNOTTAMENTO_CASA = 7;
    constexpr static int PERNOTTAMENTO_ALBERGO = 14;
public:
    /**
     * costruttore parametrico
     * utilizza il costruttore di Terreno impostando il TipoCasella a LUSSO
     * @param indiceCasella l'indice della casella nel tabellone
     */
    explicit TerrenoLusso(int indiceCasella):Terreno{indiceCasella, TipoCasella::LUSSO}{}

    // override metodi get dei prezzi
    int getPrezzoAcquistoTerreno() const override{ return ACQUISTO_TERRENO;}
    int getPrezzoAcquistoCasa() const override{return ACQUISTO_CASA;}
    int getPrezzoAcquistoAlbergo() const override{return ACQUISTO_ALBERGO;}
    int getPrezzoPernottamentoCasa() const override{return PERNOTTAMENTO_CASA;}
    int getPrezzoPernottamentoAlbergo() const override{return PERNOTTAMENTO_ALBERGO;}
};

#endif //PROGETTO_FINALE_TERRENOLUSSO_H
