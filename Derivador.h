#ifndef DERIVADOR_H
#define DERIVADOR_H
#include "Sinal.h"
#include "CircuitoSISO.h"

class Derivador: public CircuitoSISO{
public:
    Derivador();
    virtual ~Derivador();
    Sinal* processar(Sinal* sinalIN);
};
#endif
