#ifndef PERSISTENCIADEMODULO_H
#define PERSISTENCIADEMODULO_H
#include "CircuitoSISO.h"
#include "Modulo.h"
#include "ModuloEmSerie.h"
#include "ModuloEmParalelo.h"
#include "Derivador.h"
#include "Integrador.h"
#include "Amplificador.h"
#include "Somador.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <list>

using namespace std;

class PersistenciaDeModulo{
private:
  string nomeDoArquivo;
public:
  PersistenciaDeModulo(string nomeDoArquivo);
  virtual ~PersistenciaDeModulo();
  void salvarEmArquivo(Modulo* mod);
  Modulo* lerDeArquivo();
};

#endif
