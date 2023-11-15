#ifndef PILOTO_H
#define PILOTO_H
#include "Sinal.h"
#include "Amplificador.h"
#include "Integrador.h"

class Piloto{
private:
    Amplificador* amplificadorPiloto;
    Integrador* integradorPiloto;
public:
    Piloto(double ganho);
    virtual ~Piloto();
    Sinal* processar(Sinal* sinalIN);
};

#endif /* PILOTO_H */
