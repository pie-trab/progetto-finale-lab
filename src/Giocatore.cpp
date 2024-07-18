// NICOLÒ FIORANZATO

#include "../include/Giocatore.h"

void Giocatore::pagaPernottamento(Casella& c, Giocatore& g) {
    std::string log;

    // il dynamic cast serve per assicurarsi che il tipo di c sia un'istanza di tipo Terreno
    if(dynamic_cast<Terreno*>(&c)->getStatoUpgrade() == Upgrade::CASA){
        fiorini -= dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoCasa(); // si decrementano i fiorini del giocatore
        if(g.getFiorini() - dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoCasa() >= 0){ // controlla se il giocatore si può permettere di pagare il pernottamento
            g.riceviPagamento(dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoCasa());

            log = "Giocatore " +std::to_string(id) + " ha pagato " + std::to_string(dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoCasa()) + " fiorini a giocatore " +std::to_string(g.id)  + " per pernottamento" + '\n';
            std::cout << log;
            scriviLog(log);
        }else{ // se non si hanno abbastanza fiorini verrà ceduta solamente la somma residua
            g.riceviPagamento(dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoCasa() + g.getFiorini()); // che sarà negativo, eliminando di conseguenza il giocatore

            log = "Giocatore " + std::to_string(id) + " ha pagato " + std::to_string(dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoCasa() + g.getFiorini()) + " fiorini a giocatore " + std::to_string(g.id) + " per pernottamento" + '\n';
            std::cout << log;
            scriviLog(log);
        }
    }else{ // azioni analoghe per il caso dell'albergo
        fiorini -= dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoAlbergo();
        if(g.getFiorini() - dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoAlbergo() >= 0){
            g.riceviPagamento(dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoAlbergo());

            log = "Giocatore " + std::to_string(id) + " ha pagato " + std::to_string(dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoAlbergo()) + " fiorini a giocatore " + std::to_string(g.id) + " per pernottamento\n";
            std::cout << log;
            scriviLog(log);
        }else{
            g.riceviPagamento(dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoAlbergo() + g.getFiorini());

            log = "Giocatore " + std::to_string(id) + " ha pagato " + std::to_string(dynamic_cast<Terreno*>(&c)->getPrezzoPernottamentoAlbergo() + g.getFiorini()) + " fiorini a giocatore " + std::to_string(g.id) + " per pernottamento\n";
            std::cout << log;
            scriviLog(log);
        }
    }
}

int Giocatore::tiraDadi() const {
    // genero due numeri casuali tra 1 e 6 e li sommo tra loro
    int dado1 = rand() % 6 + 1;
    int dado2 = rand() % 6 + 1;
    std::string log = "Giocatore " + std::to_string(id) + " ha tirato i dadi ottenendo un valore di " + std::to_string(dado1 + dado2) + '\n';
    std::cout << log;
    scriviLog(log);
    return dado1 + dado2;
}

void scriviLog(const std::string& str){
    std::ofstream logFile;
    // il messaggio viene scritto in modalità append
    logFile.open ("../logPartita.txt", std::ios::in | std::ios::app);
    logFile << str;
    logFile.close();
}
