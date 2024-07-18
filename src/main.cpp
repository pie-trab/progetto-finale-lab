// MIRKO BERTARELLO

#include <iostream>
#include "fstream"
#include "Gioco.h"

int main(int argc, char* argv[]) {
    // si imposta il seed della funzione rand()
    srand(time(0));
    std::string modalita = argv[1];

    // il file di log viene creato se non esiste e ripulito se già esistente
    std::ofstream logFile{"../logPartita.txt"};
    logFile.close();

    // si legge l'argomento da riga di comando per avviare la partita in modalità umano contro computer o solo computer
    if (modalita == "human"){
        Gioco gioco{true};
        gioco.avviaGioco();
    } else if (modalita == "computer") {
        Gioco gioco{false};
        gioco.avviaGioco();
    } else {
        throw std::runtime_error("Argomenti partita non validi");
    }
    return 0;
}
