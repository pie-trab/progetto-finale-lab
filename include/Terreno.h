// NICOLÒ FIORANZATO

#ifndef PROGETTO_FINALE_TERRENO_H
#define PROGETTO_FINALE_TERRENO_H

#include <memory>
#include <iostream>
#include "Upgrade.h"
#include "InvalidUpgrade.h"
#include "Casella.h"
#include "InvalidTipoCasella.h"

/**
 * Classe virtuale pura che eredita Casella. Rappresenta una casella di tipo terreno
 */
class Terreno : public Casella{
protected:
    int proprietario = -1; // indice del proprietario (-1 = nessun proprietario)
    Upgrade statoUpgrade = Upgrade::NESSUNO; // stato dell'upgrade della casella
public:
    /**
     * costruttore parametrico
     * @param indiceCasella l'indice della casella nel tabellone
     */
    explicit Terreno(int indiceCasella): Casella{indiceCasella}{};

    /**
     * costruttore parametrico
     * @param indiceCasella l'indice della casella nel tabellone
     * @param tipoCasella il tipo della casella (LUSSO, STANDARD o ECONOMICA)
     */
    Terreno(int indiceCasella, TipoCasella tipoCasella): Casella{indiceCasella, tipoCasella}{
        if(tipoCasella == TipoCasella::ANGOLO || tipoCasella == TipoCasella::PARTENZA){
            throw InvalidTipoCasella{"Impossibile inizializzare una casella di tipo terreno con tipo ANGOLO o PARTENZA"};
        }
    };

    /**
     * metodo per eseguire l' upgrade di un terreno
     * quando invocato la prima volta passa da terreno a terreno con casa e poi a terreno con albergo
     */
    void upgrade();

    /**
     * override del metodo toString() di casella
     * @return una stringa rappresentante il terreno
     */
    std::string toString() const override;

    /**
     * resetta il terreno:
     * - rimuove il proprietario
     * - rimuove l'edificio
     */
    void reset();

    // metodi getter e setter
    Upgrade getStatoUpgrade() const {
        return statoUpgrade;
    }

    int getProprietario() const {
        return proprietario;
    }

    void setProprietario(int p){
        proprietario = p;
    }

    // metodi sovrascritti nelle sottoclassi TerrenoEconomico, TerrenoStandard e TerrenoLusso
    virtual int getPrezzoAcquistoTerreno() const = 0;
    virtual int getPrezzoAcquistoCasa() const = 0;
    virtual int getPrezzoAcquistoAlbergo() const = 0;
    virtual int getPrezzoPernottamentoCasa() const = 0;
    virtual int getPrezzoPernottamentoAlbergo() const = 0;
};

#endif //PROGETTO_FINALE_TERRENO_H
