#ifndef MODULOEMPARALELO_H
#define MODULOEMPARALELO_H
#include "CircuitoSISO.h"
#include "Modulo.h"
#include "Somador.h"
#include <iostream>
#include <list>

using namespace std;

class ModuloEmParalelo: public Modulo{
  public:
    ModuloEmParalelo();
    virtual ~ModuloEmParalelo();
    Sinal* processar(Sinal* sinalIN);
};

#endif
