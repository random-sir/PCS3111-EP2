#ifndef CIRCUITO_H
#define CIRCUITO_H

class Circuito(){
protected:
  static int GlobalID;
  int ID;
public:
  Circuito();
  virtual ~Circuito();
  int getID();
  void imprimir();
  static int getUltimoID();
};

#endif
