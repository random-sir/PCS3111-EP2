#ifndef INTEGRADOR_H
#define INTEGRADOR_H
#include "Sinal.h"
#include "CircuitoSISO.h"

class Integrador: public CircuitoSISO{
public:
    Integrador();
    virtual ~Integrador();
    Sinal* processar(Sinal* sinalIN);
};

#endif 
