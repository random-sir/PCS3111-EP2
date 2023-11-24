#ifndef PERSISTENCIADEMODULO_H
#define PERSISTENCIADEMODULO_H
#include "Modulo.h"
#include <string>
#include <fstream>

using namespace std;

class PersistenciaDeModulo{
public:
  PersistenciaDeModulo(string nomeDoArquivo);
  virtual ~PersistenciaDeModulo();
  void salvarEmArquivo(Modulo* mod);
  Modulo* lerDeArquivo();
}

#endif
