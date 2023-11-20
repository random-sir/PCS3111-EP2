#ifndef CIRCUITOSISO_H
#define CIRCUITOSISO_H
#include "Circuito.h"

class CircuitoSISO: public Circuito{
public:
  CircuitoSISO();
  virtual ~CircuitoSISO();
  virtual Sinal* processar(Sinal* sinalIN) = 0;
};

#endif
