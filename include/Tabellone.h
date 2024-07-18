// NICOLÒ FIORANZATO

#ifndef PROGETTO_FINALE_TABELLONE_H
#define PROGETTO_FINALE_TABELLONE_H

#include <vector>
#include <iostream>
#include <memory>
#include "Upgrade.h"
#include "Casella.h"
#include "TerrenoEconomico.h"
#include "TerrenoStandard.h"
#include "TerrenoLusso.h"

/**
 * Classe che rappresenta il tabellone di gioco
 */
class Tabellone{
private:
    std::vector<std::unique_ptr<Casella>> caselle; // le caselle sono memorizzate in un vettore di unique pointers a oggetti Casella

public:
    /**
     * costruttore di default
     * posiziona casualmente le caselle di tipo terreno
     */
    Tabellone();

    // ritorna una stringa per la visualizzazione della lista delle proprietà di ogni giocatore
    std::string getListaProprieta();

    // metodo getter
    std::vector<std::unique_ptr<Casella>>& getCaselle() {
        return caselle;
    }
};

/**
 * overload dell'operatore << per stampare un tabellone
 * @param oggetto ostream
 * @param il tabellone da stampare
 * @return un oggetto ostream contenente la stringa del tabellone
 */
std::ostream& operator<<(std::ostream&, Tabellone&);

/**
 * metodo stampare un numero a una cifra intero con spaziatura corretta per il metodo show()
 * @param il numero
 * @return la stringa formattata
 */
std::string spanInt(int);

/**
 * metodo stampare un singolo carattere con spaziatura corretta per il metodo show()
 * @param il carattere
 * @return la stringa formattata
 */
std::string spanChar(char);

/**
 * metodo che converte l'indice di una casella in coordinata [lettera-numero]
 * @param l'indice della casella
 * @return la stringa della coordinata
 */
std::string convertToCoordinate(int);

#endif //PROGETTO_FINALE_TABELLONE_H
