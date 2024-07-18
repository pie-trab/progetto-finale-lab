// NICOLÒ FIORANZATO

#include "../include/Casella.h"

std::string Casella::toString() const{
    constexpr int DEFAULT_SPAN = 3; // una casella con una lettera al centro e 2 caratteri '|' occupa 3 di spazio

    std::string spanned;
    if(giocatoriSopra.empty()){
        // spaziatura iniziale
        for (int i = 0; i < (SPAN - DEFAULT_SPAN) / 2; ++i) {
            spanned += ' ';
        }

        // stampo il tipo della casella (spazio vuoto | P)
        spanned += '|';
        spanned += tipoCasella;
        spanned += '|';

        for (int i = 0; i < ((SPAN - DEFAULT_SPAN) / 2) + 1; ++i) {
            spanned += ' ';
        }
    } else {
        // spaziatura iniziale
        //                                                     2 caratteri '|'
        for (int i = 0; i < (SPAN - (giocatoriSopra.size() + (DEFAULT_SPAN - 1))) / 2; ++i) {
            spanned += ' ';
        }

        spanned += '|';
        // stampo il tipo della casella (spazio vuoto | P)
        if(tipoCasella == TipoCasella::PARTENZA){
            spanned += tipoCasella;
        }
        // stampo giocatori
        for (int i = 0; i < giocatoriSopra.size(); ++i) {
            spanned += std::to_string(giocatoriSopra.at(i));
        }

        // stampo spaziatura rimanente per arrivare a lunghezza = SPAN
        spanned += '|';
        if (tipoCasella != TipoCasella::PARTENZA) { //          sommo 2 caratteri '|'
            for (int i = 0; i < SPAN - ((SPAN - (giocatoriSopra.size() + 2)) / 2) - DEFAULT_SPAN + 1 - giocatoriSopra.size(); ++i) {
                spanned += ' ';
            }
        } else {
            for (int i = 0; i < SPAN - ((SPAN - (giocatoriSopra.size() + 2)) / 2) - DEFAULT_SPAN - giocatoriSopra.size(); ++i) {
                spanned += ' ';
            }
        }
    }
    return spanned;
}


