// PIETRO TRABUIO

#include "../include/Tabellone.h"

Tabellone::Tabellone() {
    constexpr int MAX_ECONOMICO = 8; // numero di casella di classe economica da inserire nel tabellone
    constexpr int MAX_STANDARD = 10; // numero di casella di classe standard da inserire nel tabellone
    constexpr int MAX_LUSSO = 6; // numero di casella di classe lusso da inserire nel tabellone

    // vettore temporaneo per l'assegnamento casuale dei terreni sul tabellone
    std::vector<int> estrazioneCaselle;
    estrazioneCaselle.reserve(MAX_ECONOMICO + MAX_STANDARD + MAX_LUSSO);
    for (int i = 0; i < MAX_ECONOMICO; ++i) {
        estrazioneCaselle.push_back(1);
    }
    for (int i = 0; i < MAX_STANDARD; ++i) {
        estrazioneCaselle.push_back(2);
    }
    for (int i = 0; i < MAX_LUSSO; ++i) {
        estrazioneCaselle.push_back(3);
    }

    // inserimento casella d'angolo
    caselle.push_back(std::unique_ptr<Casella>(new Casella{0}));

    // inserisco 7 - 1 = 6 caselle per un lato del tabellone
    for (int i = 1; i < 7; ++i) {
        int random = rand() % estrazioneCaselle.size();
        switch (estrazioneCaselle.at(random)) {
            case 1:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoEconomico{i}));
                break;
            case 2:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoStandard{i}));
                break;
            case 3:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoLusso{i}));
                break;
        }
        estrazioneCaselle.erase(estrazioneCaselle.begin() + random);
    }

    // inserimento casella d'angolo
    caselle.push_back(std::unique_ptr<Casella>(new Casella{7}));

    // inserisco 14 - 8 = 6 caselle per un lato del tabellone
    for (int i = 8; i < 14; ++i) {
        int random = rand() % estrazioneCaselle.size();
        switch (estrazioneCaselle.at(random)) {
            case 1:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoEconomico{i}));
                break;
            case 2:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoStandard{i}));
                break;
            case 3:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoLusso{i}));
                break;
        }
        estrazioneCaselle.erase(estrazioneCaselle.begin() + random);
    }

    // inserimento casella d'angolo
    caselle.push_back(std::unique_ptr<Casella>(new Casella{14, TipoCasella::PARTENZA}));

    // inserisco 21 - 15 = 6 caselle per un lato del tabellone
    for (int i = 15; i < 21; ++i) {
        int random = rand() % estrazioneCaselle.size();
        switch (estrazioneCaselle.at(random)) {
            case 1:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoEconomico{i}));
                break;
            case 2:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoStandard{i}));
                break;
            case 3:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoLusso{i}));
                break;
        }
        estrazioneCaselle.erase(estrazioneCaselle.begin() + random);
    }

    // inserimento casella d'angolo
    caselle.push_back(std::unique_ptr<Casella>(new Casella{21}));

    // inserisco 28 - 22 = 6 caselle per un lato del tabellone
    for (int i = 22; i < 28; ++i) {
        int random = rand() % estrazioneCaselle.size();
        switch (estrazioneCaselle.at(random)) {
            case 1:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoEconomico{i}));
                break;
            case 2:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoStandard{i}));
                break;
            case 3:
                caselle.push_back(std::unique_ptr<Casella>(new TerrenoLusso{i}));
                break;
        }
        estrazioneCaselle.erase(estrazioneCaselle.begin() + random);
    }
}

std::ostream& operator<<(std::ostream& os, Tabellone& t){
    std::string outputString;
    outputString += spanChar(' ');
    // stampo la prima riga di numeri da 1 a 9
    for (int i = 1; i < 9; ++i) {
        outputString += spanInt(i);
    }
    outputString += '\n';


    int count = 0; // indica la posizione della casella che verrà stampata nella colonna destra verticale del tabellone
    // stampo tutte le righe del tabellone
    for (char i = 'A'; i <= 'H'; i++) {
        outputString += spanChar(i);
        if (i == 'A') { // riga superiore
            for (int j = 0; j < 8; ++j) {
                outputString += t.getCaselle().at(j)->toString();
            }
        } else if (i == 'H') { // riga inferiore
            for (int j = 21; j >= 14; --j) {
                outputString += t.getCaselle().at(j)->toString();
            }
        } else { // colonne
            outputString += t.getCaselle().at(t.getCaselle().size() - 1 - count)->toString();
            for (int j = 0; j < 6; ++j) {
                outputString += spanChar(' ');
            }
            outputString += t.getCaselle().at(8 + count)->toString();
            count++;
        }
        outputString += '\n';
    }
    return os << outputString;
}

std::string spanInt(int n) {
    std::string spanned;
    // prima metà degli spazi necessari per la corretta formattazione
    for (int i = 0; i < (SPAN - 1) / 2; i++) {
        spanned += ' ';
    }
    // aggiungo il numero passato in input
    spanned += std::to_string(n);

    // seconda metà degli spazi necessari per la corretta formattazione
    for (int i = 0; i < SPAN / 2; i++) {
        spanned += ' ';
    }
    return spanned;
}

std::string spanChar(char c) {
    std::string spanned;
    // prima metà degli spazi necessari per la corretta formattazione
    for (int i = 0; i < (SPAN - 1) / 2; i++) {
        spanned += ' ';
    }
    // aggiungo il carattere passato in input
    spanned += c;

    // seconda metà degli spazi necessari per la corretta formattazione
    for (int i = 0; i < SPAN / 2; i++) {
        spanned += ' ';
    }
    return spanned;
}

std::string Tabellone::getListaProprieta() {
    std::vector<std::string> giocatore1;
    std::vector<std::string> giocatore2;
    std::vector<std::string> giocatore3;
    std::vector<std::string> giocatore4;

    // scorre la lista delle caselle
    for (int i = 0; i < caselle.size(); ++i) {
        // evito le caselle d'angolo e quella di partenza
        if (i != 0 && i != 7 && i != 14 && i != 21) {
            // eseguo il cast della casella a terreno (sono sicuro che sarà terreno per il controllo precedente)
            std::unique_ptr<Terreno> temp{dynamic_cast<Terreno*>(caselle.at(i).release())};
            // controllo il proprietario del terreno e lo aggiungo al vettore corrispondente
            if (temp->getProprietario() != -1 && temp->getStatoUpgrade() != Upgrade::NESSUNO) {
                switch (temp->getProprietario()) {
                    case 1:
                        giocatore1.push_back(convertToCoordinate(i));
                        break;
                    case 2:
                        giocatore2.push_back(convertToCoordinate(i));
                        break;
                    case 3:
                        giocatore3.push_back(convertToCoordinate(i));
                        break;
                    case 4:
                        giocatore4.push_back(convertToCoordinate(i));
                        break;
                }
            }
            // ricreo il puntatore alla casella in quella posizione
            caselle.at(i) = std::unique_ptr<Casella>{temp.release()};
        }
    }

    // a partire dai 4 vector precedenti vengono costruite le stringhe che riportano per ogni giocatore le sue proprietà
    std::string output;
    output += "Giocatore 1: ";
    if (!giocatore1.empty()) {
        for (int i = 0; i < giocatore1.size() - 1; ++i) {
            output += giocatore1.at(i) + ",";
        }
        output += giocatore1.at(giocatore1.size() - 1);
    }
    output += '\n';

    output += "Giocatore 2: ";
    if (!giocatore2.empty()) {
        for (int i = 0; i < giocatore2.size() - 1; ++i) {
            output += giocatore2.at(i) + ",";
        }
        output += giocatore2.at(giocatore2.size() - 1);
    }
    output += '\n';

    output += "Giocatore 3: ";
    if (!giocatore3.empty()) {
        for (int i = 0; i < giocatore3.size() - 1; ++i) {
            output += giocatore3.at(i) + ",";
        }
        output += giocatore3.at(giocatore3.size() - 1);
    }
    output += '\n';

    output += "Giocatore 4: ";
    if (!giocatore4.empty()) {
        for (int i = 0; i < giocatore4.size() - 1; ++i) {
            output += giocatore4.at(i) + ",";
        }
        output += giocatore4.at(giocatore4.size() - 1);
    }
    output += '\n';
    return output;
}

std::string convertToCoordinate(int i) {
    std::string coordinate;
    if (i >= 0 && i <= 7) { // sono sulla riga superiore
        coordinate = 'A';
        coordinate += std::to_string(i + 1);
    } else if (i >= 8 && i <= 14) { // sono sulla colonna di destra
        char rigaB = 'B';
        rigaB += i - 8;
        coordinate = rigaB;
        coordinate += std::to_string(8);
    } else if (i >= 15 && i <= 21) { // sono sulla riga inferiore
        coordinate = 'H';
        int colonna = 15 - i + 7;
        coordinate += std::to_string(colonna);
    } else { // sono sulla colonna di sinistra
        char rigaG = 'G';
        char riga = rigaG - i + 22;
        coordinate += riga;
        coordinate += std::to_string(1);
    }
    return coordinate;
}



