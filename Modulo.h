#ifndef MODULO_H
#define MODULO_H
#include "CircuitoSISO.h"
#include <list>

class Modulo: public CircuitoSISO{
  protected:
    std::list<CircuitoSISO*>* circuitos;
  public:
    Modulo();
    virtual ~Modulo() = 0; //no enunciado não há especificação de qual método deveria ser o abstrato, entretanto há de que a classe deveria ser. Logo, tornei o destrutor abstrato;
    void adicionar(CircuitoSISO* circ);
    std::list<CircuitoSISO*>* getCircuitos();
};

#endif
