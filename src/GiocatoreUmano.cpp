// PIETRO TRABUIO

#include"../include/GiocatoreUmano.h"

#include <iostream>

void GiocatoreUmano::compraTerreno(Casella &c, Gioco &g) {
    if (fiorini - dynamic_cast<Terreno*>(&c)->getPrezzoAcquistoTerreno() >= 0) {
        bool flag = true;
        do { // attende l'input dell'utente (S | N | show), continua a chiederlo finché non è corretto
            std::cout << "Vuoi comprare questo terreno per " << dynamic_cast<Terreno *>(&c)->getPrezzoAcquistoTerreno()
                      << " fiorini? [S/N] (oppure usa il comando 'show' per visualizzare la situazione)" << std::endl;
            std::string temp;
            std::cin >> temp;
            if (temp == "N" || temp == "n") {
                return;
            }
            if (temp == "S" || temp == "s") {
                flag = false;
            }
            if (temp == "show") {
                g.show();
            }
        } while (flag);

        // se l'utente ha abbastanza fiorini e risponde S allora si effettua l'azione
        fiorini -= dynamic_cast<Terreno *>(&c)->getPrezzoAcquistoTerreno();
        dynamic_cast<Terreno *>(&c)->setProprietario(getId());
        std::string log = "Giocatore " + std::to_string(id) + " ha acquistato il terreno " + convertToCoordinate(c.getIndiceCasella()) + '\n';
        std::cout << log;
        scriviLog(log);
    }
}

void GiocatoreUmano::miglioraTerreno(Casella &c, Gioco &g) {
    bool fioriniSufficienti = true;
    int prezzo = 0;
    switch (dynamic_cast<Terreno*>(&c)->getStatoUpgrade()) { // si controlla l'edificio presente sulla casella per capire il prezzo dell'operazione
        case Upgrade::NESSUNO:
            if (fiorini - dynamic_cast<Terreno *>(&c)->getPrezzoAcquistoCasa() >= 0) {
                prezzo = dynamic_cast<Terreno *>(&c)->getPrezzoAcquistoCasa();
            } else {
                fioriniSufficienti = false;
            }
            break;
        case Upgrade::CASA:
            if (fiorini - dynamic_cast<Terreno *>(&c)->getPrezzoAcquistoAlbergo() >= 0) {
                prezzo = dynamic_cast<Terreno *>(&c)->getPrezzoAcquistoAlbergo();
            } else {
                fioriniSufficienti = false;
            }
            break;
        default:
            break;
    }

    bool flag = true;
    while (fioriniSufficienti && flag) { // attende l'input dell'utente (S | N | show), continua a chiederlo finché non è corretto
        std::cout
                << "Vuoi fare l'upgrade di questo terreno per " << prezzo << " fiornini? [S/N] (oppure usa il comando 'show' per visualizzare la situazione)"
                << std::endl;
        std::string temp;
        std::cin >> temp;
        if (temp == "N" || temp == "n") {
            return;
        }
        if (temp == "S" || temp == "s") {
            flag = false;
        }
        if (temp == "show") {
            g.show();
        }
    }

    if(fioriniSufficienti){ // se i fiorini sono sufficienti si effettua l'operazione
        fiorini -= prezzo;
        dynamic_cast<Terreno *>(&c)->upgrade();
        std::string log;
        switch (dynamic_cast<Terreno*>(&c)->getStatoUpgrade()) {
            case Upgrade::NESSUNO:
                log = "Giocatore " + std::to_string(id) + " ha costruito una casa sul terreno " + convertToCoordinate(c.getIndiceCasella()) + '\n';
                std::cout << log;
                scriviLog(log);
                break;
            case Upgrade::CASA:
                log = "Giocatore " + std::to_string(id) + " ha migliorato una casa in albergo sul terreno " + convertToCoordinate(c.getIndiceCasella()) + '\n';
                std::cout << log;
                scriviLog(log);
                break;
            default:
                break;
        }
    }
}


