#ifndef MODULOREALIMENTADO_H
#define MODULOREALIMENTADO_H
#include "Sinal.h"
#include "Somador.h"
#include "Amplificador.h"
#include "Piloto.h"
#include "Modulo.h"
#include "ModuloEmSerie.h"

class ModuloRealimentado: public Modulo{
private:
    //MRa = ModuloRealimentado
    Somador *somadorMRa;
    Amplificador *inversorMRa;
    ModuloEmSerie *moduloEmSerieMRa;
public:
    ModuloRealimentado();
    virtual ~ModuloRealimentado();
    Sinal* processar(Sinal* sinalIN);
};

#endif 
