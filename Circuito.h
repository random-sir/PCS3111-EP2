#ifndef CIRCUITO_H
#define CIRCUITO_H

class Circuito(){
protected:
  static int GlobalID;
  int ID;
public:
  Circuito();
  virtual ~Circuito() = 0;
  int getID();
  void imprimir();
  static int getUltimoID();
};

#endif
