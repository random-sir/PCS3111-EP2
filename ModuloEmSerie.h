#ifndef MODULOEMSERIE_H
#define MODULOEMSERIE_H
#include "Sinal.h"
#include "CircuitoSISO.h"
#include "Modulo.h"
#include <iostream>
#include <list>

using namespace std;

class ModuloEmSerie: public Modulo{
  public:
    ModuloEmSerie();
    virtual ~ModuloEmSerie();
    Sinal* processar(Sinal *sinalIN);
};

#endif
