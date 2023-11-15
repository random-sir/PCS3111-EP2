#ifndef AMPLIFICADOR_H
#define AMPLIFICADOR_H
#include "Sinal.h"

class Amplificador{
private:
    double ganho;
public:
    Amplificador(double ganho);
    virtual ~Amplificador();
    Sinal* processar(Sinal* sinalIN);
    void setGanho(double ganho);
    double getGanho();
};
#endif
