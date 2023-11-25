#ifndef MODULOEMSERIE_H
#define MODULOEMSERIE_H
#include "Sinal.h"
#include "Modulo.h"

class ModuloEmSerie: public Modulo{
  public:
    ModuloEmSerie();
    virtual ~ModuloEmSerie();
    Sinal* processar(Sinal *sinalIN);
};

#endif
