#ifndef CIRCUITO_H
#define CIRCUITO_H
#include <iostream>

using namespace std;

class Circuito{
protected:
  static int GlobalID;
  int ID;
public:
  Circuito();
  virtual ~Circuito() = 0;
  int getID();
  virtual void imprimir();
  static int getUltimoID();
};

#endif
