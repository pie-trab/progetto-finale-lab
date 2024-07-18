// NICOLÒ FIORANZATO

#ifndef PROGETTO_FINALE_CASELLA_H
#define PROGETTO_FINALE_CASELLA_H

#include <vector>
#include <string>
#include "TipoCasella.h"

constexpr int SPAN = 8; // spaziatura per la visualizzazione di un elemento del tabellone

/**
 * Classe che rappresenta una casella generica del tabellone (default casella d'angolo)
 */
class Casella{
protected:
    TipoCasella tipoCasella = TipoCasella::ANGOLO; // tipo della casella
    std::vector<int> giocatoriSopra; // lista giocatori sopra la casella
    int indiceCasella; // indice numerico della casella nel tabellone [0-27]
public:
    /**
     * costruttore parametrico
     * per istanziare una casella d'angolo (non di partenza)
     * @param indiceCasella
     */
    explicit Casella(int indiceCasella): indiceCasella{indiceCasella}{}

    /**
     * costruttore parametrico
     * per istanziare caselle di tipo terreno e di partenza
     * @param indiceCasella
     * @param tipoCasella
     */
    Casella(int indiceCasella, TipoCasella tipoCasella):indiceCasella{indiceCasella} , tipoCasella{tipoCasella}{}

    // costruttore e assegnamento di copia disabilitati
    Casella(const Casella&) = delete;
    Casella& operator=(const Casella&) = delete;

    // metodi getter
    std::vector<int>& getGiocatoriSopra(){
        return giocatoriSopra;
    }

    int getIndiceCasella() const {
        return indiceCasella;
    }

    /**
     * toString
     * @return una stringa formattata che rappresenta lo stato della casella
     */
    virtual std::string toString() const;
};

#endif //PROGETTO_FINALE_CASELLA_H
