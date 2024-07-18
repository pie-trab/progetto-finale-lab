// MIRKO BERTARELLO

#ifndef PROGETTO_FINALE_INVALIDTIPOCASELLA_H
#define PROGETTO_FINALE_INVALIDTIPOCASELLA_H

#include <stdexcept>

/**
 * Errore lanciato in caso di casella non valida
 * es. una casella di tipo angolo possiede come tipoCasella le tipologie di terreno (come LUSSO, STANDARD, ecc...)
 */
class InvalidTipoCasella : public std::logic_error{
public:
    explicit InvalidTipoCasella(const std::string& message): std::logic_error(message){};
};

#endif //PROGETTO_FINALE_INVALIDTIPOCASELLA_H
