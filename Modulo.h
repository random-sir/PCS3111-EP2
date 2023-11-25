#ifndef MODULO_H
#define MODULO_H
#include "CircuitoSISO.h"
#include <list>
#include <iostream>

using namespace std;

class Modulo: public CircuitoSISO{
  protected:
    list<CircuitoSISO*>* circuitos;
  public:
    Modulo();
    virtual ~Modulo();
    virtual void adicionar(CircuitoSISO* circ);
    virtual list<CircuitoSISO*>* getCircuitos();
};

#endif
