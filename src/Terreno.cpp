// NICOLÒ FIORANZATO

#include "../include/Terreno.h"

void Terreno::upgrade(){
    // controllo che il terreno non sia già potenziato al massimo
    if (statoUpgrade == ALBERGO) throw InvalidUpgrade("Impossibile fare l'upgrade di un albergo");
    statoUpgrade = static_cast<Upgrade>(statoUpgrade + 1);
}


std::string Terreno::toString() const{
    constexpr int DEFAULT_SPAN = 3; //una casella con una lettera al centro e 2 caratteri '|' occupa 3 di spazio

    std::string spanned;
    if(giocatoriSopra.empty()){
        // spaziatura iniziale
        for (int i = 0; i < (SPAN - DEFAULT_SPAN) / 2; ++i) {
            spanned += ' ';
        }

        // stampo il tipo della casella (E, L, S)
        spanned += '|';
        spanned += tipoCasella;
        switch (statoUpgrade) {
            case Upgrade::NESSUNO:
                break;
            case Upgrade::CASA:
                spanned += '*';
                break;
            case Upgrade::ALBERGO:
                spanned += '^';
                break;
            default:
                break;
        }
        spanned += '|';

        if(statoUpgrade == Upgrade::NESSUNO){
            for (int i = 0; i < (SPAN - DEFAULT_SPAN) / 2 + 1; ++i) {
                spanned += ' ';
            }
        }else{
            for (int i = 0; i < (SPAN - DEFAULT_SPAN) / 2; ++i) {
                spanned += ' ';
            }
        }
    }else {
        // spaziatura iniziale
        for (int i = 0; i < (SPAN - (giocatoriSopra.size() + DEFAULT_SPAN)) / 2; ++i) {
            spanned += ' ';
        }

        spanned += '|';
        // stampo il tipo della casella (E, L, S)
        spanned += tipoCasella;
        // stampo l'upgrade della casella (nessuno | * | ^)
        switch (statoUpgrade) {
            case Upgrade::NESSUNO:
                break;
            case Upgrade::CASA:
                spanned += '*';
                break;
            case Upgrade::ALBERGO:
                spanned += '^';
                break;
            default:
                break;
        }
        // stampo i giocatori sulla casella
        for (int i = 0; i < giocatoriSopra.size(); ++i) {
            spanned += std::to_string(giocatoriSopra.at(i));
        }

        spanned += '|';
        // spaziatura finale
        if(getStatoUpgrade() == Upgrade::NESSUNO){
            for (int i = 0; i < SPAN - (SPAN - (giocatoriSopra.size() + DEFAULT_SPAN)) / 2 - giocatoriSopra.size() - DEFAULT_SPAN; ++i) {
                spanned += ' ';
            }
        }else{
            for (int i = 0; i < SPAN - (SPAN - (giocatoriSopra.size() + DEFAULT_SPAN)) / 2 - giocatoriSopra.size() - DEFAULT_SPAN - 1; ++i) {
                spanned += ' ';
            }
        }
    }
    return spanned;
}

// metodo reset del terreno (utilizzato al momento dell'eliminazione di un giocatore)
void Terreno::reset() {
    proprietario = -1;
    statoUpgrade = Upgrade::NESSUNO;
}

