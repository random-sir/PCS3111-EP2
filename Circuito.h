#ifndef ""
#define "CIRCUITO_H"

class Circuito(){
protected:
  
public:
  Circuito();
  virtual ~Circuito();
  int getID();
  void imprimir();
  static int getUltimoID();
};

#endif
