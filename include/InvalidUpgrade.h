// MIRKO BERTARELLO

#ifndef PROGETTO_FINALE_INVALIDUPGRADE_H
#define PROGETTO_FINALE_INVALIDUPGRADE_H

#include <stdexcept>

/**
 * Errore lanciato nel caso si tenti l'upgrade di una casella con statoUpgrade ad ALBERGO
 */
class InvalidUpgrade : public std::logic_error{
public:
    explicit InvalidUpgrade(const std::string& message): std::logic_error(message){};
};

#endif //PROGETTO_FINALE_INVALIDUPGRADE_H
