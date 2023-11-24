#ifndef MODULO_H
#define MODULO_H
#include "CircuitoSISO.h"
#include <list>

class Modulo: public CircuitoSISO{
  protected:
    std::list<CircuitoSISO*>* circuitos;
  public:
    Modulo();
    virtual ~Modulo();
    virtual void adicionar(CircuitoSISO* circ);
    virtual std::list<CircuitoSISO*>* getCircuitos();
};

#endif
