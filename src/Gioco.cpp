// NICOLÒ FIORANZATO

#include "../include/Gioco.h"

Gioco::Gioco(bool modalita): modalita{modalita} {
    if(modalita){ // creo 1 giocatore umano e 3 computer
        giocatori.push_back(std::unique_ptr<Giocatore>{new GiocatoreUmano{1}});
        giocatori.push_back(std::unique_ptr<Giocatore>{new GiocatoreComputer{2}});
        giocatori.push_back(std::unique_ptr<Giocatore>{new GiocatoreComputer{3}});
        giocatori.push_back(std::unique_ptr<Giocatore>{new GiocatoreComputer{4}});
    }else{ // creo 4 giocatori computer
        for (int i = 1; i <= 4 ; ++i) {
            giocatori.push_back(std::unique_ptr<Giocatore>(new GiocatoreComputer{i}));
        }
    }

    // metto i giocatori sulla casella di partenza
    for (int i = 0; i < giocatori.size(); ++i) {
        tabellone.getCaselle().at(14)->getGiocatoriSopra().push_back(giocatori.at(i)->getId());
    }

    // stabilisco l'ordine dei turni
    std::vector<std::pair<int, int>> estrazioneTurni{4};
    for (int i = 0; i < giocatori.size(); ++i) {
        // ogni giocatore tira i dadi
        estrazioneTurni.at(i) = std::pair<int, int>(giocatori.at(i)->tiraDadi(), giocatori.at(i)->getId());
    }

    while(ordineTurni.size() < giocatori.size()){
        // trovo chi ha fatto il numero massimo del lancio
        auto max = std::max_element(estrazioneTurni.begin(), estrazioneTurni.end());
        int maxLancioDadi = max->first;
        // se il massimo lancio non ha pari-meriti allora il turno viene deciso e si inserisce l'id del giocatore nella lista ordine turni
        // la ricerca del massimo in estrazioneTurni avviene con 2 lambda function che cercano rispettivamente prima dell'indice max e dopo l'indice max
        if(std::find_if(estrazioneTurni.begin(), max, [maxLancioDadi](std::pair<int, int> el) -> bool {return el.first == maxLancioDadi;}) == max
           && std::find_if(max + 1, estrazioneTurni.end(), [maxLancioDadi](std::pair<int, int> el) -> bool  {return el.first == maxLancioDadi;}) == estrazioneTurni.end()){
            ordineTurni.push_back(max->second);
            estrazioneTurni.erase(max);
        }else{ // se vi sono dei pari-meriti allora i giocatori devono ritirare i dadi
            for (int i = 0; i < estrazioneTurni.size(); ++i) {
                if(estrazioneTurni.at(i).first == maxLancioDadi){
                    // per mantenere la priorità acquisita dai lanci precedenti, il lancio precedente non viene scartato ma sommato al valore ottenuto dai dadi in questo momento
                    estrazioneTurni.at(i).first += giocatori.at(estrazioneTurni.at(i).second - 1)->tiraDadi();
                }
            }
        }
    }
}

std::string Gioco::getFioriniGiocatori() const{
    std::string output;
    // stampo la quantità di fiorini posseduta da ogni giocatore, oppure 'eliminato' per ogni giocatore non più in partita
    for (int i = 0; i < giocatori.size(); ++i) {
        if(giocatori.at(i)->getFiorini() >= 0){
            output += "Giocatore " + std::to_string(giocatori.at(i)->getId()) + ": " + std::to_string(giocatori.at(i)->getFiorini()) + '\n';
        }else{
            output += "Giocatore " + std::to_string(giocatori.at(i)->getId()) + ": eliminato" + '\n';
        }
    }
    return output;
}

void Gioco::show(){
    std::cout << "TABELLONE:" << std::endl;
    std::cout << tabellone << std::endl;
    std::cout << "LISTA PROPRIETA':" << std::endl;
    std::cout << tabellone.getListaProprieta() << std::endl;
    std::cout << "FIORINI DI OGNI GIOCATORE:" << std::endl;
    std::cout << getFioriniGiocatori();
}

void Gioco::avviaGioco() {
    constexpr int MAX_TURNI_COMPUTER = 100; // il limite di turni per partite di soli computer
    constexpr int MAX_TURNI_UMANO = 200; // il limite di turni per partite con un umano contro computer

    bool umanoNonEliminato = true; // controlla se il giocatore umano non è ancora stato eliminato
    /**
     * il ciclo dei turni continua fino a che:
     * - qualcuno rimane l'ultimo non eliminato (vince la partita)
     * - in modalità di soli computer viene raggiunto il limite di 100 turni
     * - in modalità umano contro computer, se l'umano perde e rimangono solo computer, andranno avanti per altri 100 turni
     * - in modalità umano contro computer viene raggiunto il limite dei 200 turni
     */
    while(turniCount < MAX_TURNI_UMANO && ordineTurni.size() > 1 && (modalita) ? (giocatori.at(0)->getFiorini() >= 0) || (turniCount < MAX_TURNI_COMPUTER) : (turniCount < MAX_TURNI_COMPUTER)){
        // si estrae il giocatore che deve tirare i dadi
        int giocatoreDelTurno = ordineTurni.front();
        ordineTurni.pop_front();
        // si fa muovere il giocatore
        muoviGiocatore(*giocatori.at(giocatoreDelTurno - 1));

        Casella* casellaAttuale = tabellone.getCaselle().at(giocatori.at(giocatoreDelTurno - 1)->getIndiceCasella()).release();
        Terreno* terrenoAttuale = dynamic_cast<Terreno*>(casellaAttuale);
        tabellone.getCaselle().at(giocatori.at(giocatoreDelTurno - 1)->getIndiceCasella()) = std::unique_ptr<Casella>(casellaAttuale);
        // tramite un dynamic cast verifichiamo che la casella sia una casella d'angolo oppure un terreno (il puntatore terrenoAttuale è nullptr in caso di casella d'angolo)
        if(terrenoAttuale){
            // se il terreno è posseduto da qualcun altro ed è edificato allora si deve pagare il pernottamento a quel giocatore
            if(terrenoAttuale->getProprietario() != giocatoreDelTurno && terrenoAttuale->getProprietario() != -1 && terrenoAttuale->getStatoUpgrade() != Upgrade::NESSUNO){
                giocatori.at(giocatoreDelTurno - 1)->pagaPernottamento(*terrenoAttuale, *giocatori.at(terrenoAttuale->getProprietario() - 1));
            }else if(terrenoAttuale->getProprietario() == giocatoreDelTurno){ // altrimenti se il possessore è il giocatore attuale si può migliorare il terreno
                if(terrenoAttuale->getStatoUpgrade() == Upgrade::NESSUNO || terrenoAttuale->getStatoUpgrade() == Upgrade::CASA){
                    giocatori.at(giocatoreDelTurno - 1)->miglioraTerreno(*terrenoAttuale, *this);
                }
            }else if(terrenoAttuale->getProprietario() == -1){ // se il terreno non è posseduto da nessuno, lo si può comprare
                giocatori.at(giocatoreDelTurno - 1)->compraTerreno(*terrenoAttuale, *this);
            }
        }

        // si controlla se il giocatore è stato eliminato (bilancio negativo)
        if(giocatori.at(giocatoreDelTurno - 1)->getFiorini() < 0){
            eliminaGiocatore(*giocatori.at(giocatoreDelTurno - 1));
            std::string log = "Giocatore " + std::to_string(giocatoreDelTurno) + " e' stato eliminato\n";
            std::cout << log;
            scriviLog(log);
        }else{
            // il giocatore viene reinserito nella lista ordineTurni solamente se non viene eliminato
            ordineTurni.push_back(giocatoreDelTurno);
        }
        // incremento il numero di turni effettuati
        turniCount++;
        // questa condizione permette che quando l'umano viene eliminato
        // il numero dei turni venga resettato e si vada dunque a fare altri 100 turni di soli computer
        if(modalita && umanoNonEliminato && giocatori.at(0)->getFiorini() < 0){
            turniCount = 0;
            umanoNonEliminato = false;
        }

        // stampo su log l'azione effettuata
        std::string log = "Giocatore " + std::to_string(giocatoreDelTurno) + " ha finito il turno" + '\n';
        std::cout << log;
        scriviLog(log);
    }
    // mostra la situazione del tabellone, delle proprietà e dei fiorini di ogni giocatore quando la partita è conclusa
    std::cout << std::endl;
    show();
    std::cout << std::endl;

    // se rimane solamente un giocatore nella lista ordineTurni significa che ha vinto la partita
    if(ordineTurni.size() == 1){
        std::string log = "Giocatore " + std::to_string(ordineTurni.front()) + " ha vinto la partita\n";
        std::cout << log;
        scriviLog(log);
    }else{ // altrimenti vince chi ha più fiorini (sono permesse vittorie ex-equo)
        int maxFiorini = giocatori.at(ordineTurni.front() - 1)->getFiorini();
        for(auto i = ordineTurni.begin(); i != ordineTurni.end(); i++){
            if(giocatori.at(*i - 1)->getFiorini() > maxFiorini){
                maxFiorini = giocatori.at(*i - 1)->getFiorini();
            }
        }
        for (int i = 0; i < giocatori.size(); ++i) {
            if(giocatori.at(i)->getFiorini() == maxFiorini){
                std::string log = "Giocatore " + std::to_string(giocatori.at(i)->getId()) + " ha vinto la partita\n";
                std::cout << log;
                scriviLog(log);
            }
        }
    }
}

void Gioco::muoviGiocatore(Giocatore& giocatore) {
    int tiroDadi = giocatore.tiraDadi();
    // rimuove il giocatore dalla sua casella attuale
    auto giocatoreNellaCasella = std::find_if(tabellone.getCaselle().at(giocatore.getIndiceCasella())->getGiocatoriSopra().begin(), tabellone.getCaselle().at(giocatore.getIndiceCasella())->getGiocatoriSopra().end(),
                 [&giocatore](int g) -> bool {return g == giocatore.getId();});
    tabellone.getCaselle().at(giocatore.getIndiceCasella())->getGiocatoriSopra().erase(giocatoreNellaCasella);
    // posiziono il giocatore sulla sua nuova casella corrispondente al tiro dei dadi effettuato
    int nuovaCasella = (giocatore.getIndiceCasella() + tiroDadi) % 28;
    tabellone.getCaselle().at(nuovaCasella)->getGiocatoriSopra().push_back(giocatore.getId());

    std::string log = "Giocatore " + std::to_string(giocatore.getId())  + " e' arrivato alla casella " + convertToCoordinate(nuovaCasella) + '\n';
    std::cout << log;
    scriviLog(log);

    // quando il giocatore passa dal via riceve 20 fiorini
    if(giocatore.getIndiceCasella() < 14 && nuovaCasella >= 14){
        giocatore.riceviPagamento(20);
        log =  "Giocatore " + std::to_string(giocatore.getId()) + " e' passato dal via e ha ritirato 20 fiorini\n";
        std::cout << log;
        scriviLog(log);
    }

    giocatore.setIndiceCasella(nuovaCasella);
}

void Gioco::eliminaGiocatore(Giocatore& giocatore) {
    // si rimuove il giocatore dal tabellone
    auto giocatoreNellaCasella = std::find_if(tabellone.getCaselle().at(giocatore.getIndiceCasella())->getGiocatoriSopra().begin(), tabellone.getCaselle().at(giocatore.getIndiceCasella())->getGiocatoriSopra().end(),
                                              [&giocatore](int g) -> bool {return g == giocatore.getId();});
    tabellone.getCaselle().at(giocatore.getIndiceCasella())->getGiocatoriSopra().erase(giocatoreNellaCasella);

    // vengono rimosse le sue proprietà resettando i terreni in suo possesso
    for (int i = 0; i < tabellone.getCaselle().size(); ++i) {
        if(i != 0 && i != 7 && i != 14 && i != 21){
            Terreno* temp = dynamic_cast<Terreno*>(tabellone.getCaselle().at(i).release());
            if(temp->getProprietario() == giocatore.getId()){
                temp->reset();
            }
            tabellone.getCaselle().at(i) = std::unique_ptr<Casella>{temp};
        }
    }
}



