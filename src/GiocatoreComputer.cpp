// PIETRO TRABUIO

#include "../include/GiocatoreComputer.h"

void GiocatoreComputer::compraTerreno(Casella& c, Gioco& g) {
    if (fiorini - dynamic_cast<Terreno*>(&c)->getPrezzoAcquistoTerreno() >= 0){ // verifica disponibilità di fiorini
        if((rand() % 4) == 0){ // probabilità di effettuare l'azione del 25%
            dynamic_cast<Terreno*>(&c)->setProprietario(getId());
            fiorini -= dynamic_cast<Terreno*>(&c)->getPrezzoAcquistoTerreno();
            std::string log = "Giocatore " + std::to_string(id) + " ha acquistato il terreno " + convertToCoordinate(c.getIndiceCasella()) + '\n';
            std::cout << log;
            scriviLog(log);
        }
    }
}

void GiocatoreComputer::miglioraTerreno(Casella& c, Gioco& g){
    if (rand() % 4 == 0){ // probabilità di effettuare l'azione del 25%
        switch (dynamic_cast<Terreno*>(&c)->getStatoUpgrade()) { // verifico se si deve migliorare una casa oppure un terreno vuoto
            case Upgrade::CASA:
                if (fiorini - dynamic_cast<Terreno*>(&c)->getPrezzoAcquistoAlbergo() >= 0){ // verifica disponibilità di fiorini
                    dynamic_cast<Terreno*>(&c)->upgrade();
                    fiorini -= dynamic_cast<Terreno*>(&c)->getPrezzoAcquistoAlbergo();
                    std::string log = "Giocatore " + std::to_string(id) + " ha migliorato una casa in albergo sul terreno " + convertToCoordinate(c.getIndiceCasella()) + '\n';
                    std::cout << log;
                    scriviLog(log);
                }
                break;
            case Upgrade::NESSUNO:
                if (fiorini - dynamic_cast<Terreno*>(&c)->getPrezzoAcquistoCasa() >= 0){ // verifica disponibilità di fiorini
                    dynamic_cast<Terreno*>(&c)->upgrade();
                    fiorini -= dynamic_cast<Terreno*>(&c)->getPrezzoAcquistoCasa();
                    std::string log = "Giocatore " + std::to_string(id) + " ha costruito una casa sul terreno " + convertToCoordinate(c.getIndiceCasella()) + '\n';
                    std::cout << log;
                    scriviLog(log);
                }
                break;
            default:
                break;
        }
    }
}


