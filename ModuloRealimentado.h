#ifndef MODULOREALIMENTADO_H
#define MODULOREALIMENTADO_H
#include "Sinal.h"
#include "Somador.h"
#include "Amplificador.h"
#include "CircuitoSISO.h"
#include "Modulo.h"
#include "ModuloEmSerie.h"
#include <list>

using namespace std;

class ModuloRealimentado: public Modulo{
private:
    Somador *somadorModuloRealimentado;
    Amplificador *inversorModuloRealimentado;
    ModuloEmSerie *moduloEmSerie_ModuloRealimentado;
public:
    ModuloRealimentado();
    virtual ~ModuloRealimentado();
    Sinal* processar(Sinal* sinalIN);
    void adicionar(CircuitoSISO* circ);
    list<CircuitoSISO*>* getCircuitos();
};

#endif 
