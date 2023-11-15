#include "Somador.h"

Somador::Somador(){
}

Somador::~Somador(){
}

Sinal* Somador::processar(Sinal *sinalIN1, Sinal *sinalIN2){
    int comprimentoOUT;
    if (sinalIN1->getComprimento() <= sinalIN2->getComprimento()) 
        comprimentoOUT = sinalIN1->getComprimento();
    else comprimentoOUT = sinalIN2->getComprimento();
    
    double *sequenciaOUT = new double[comprimentoOUT];
    for (int i = 0; i < comprimentoOUT; i++) 
        sequenciaOUT[i] = sinalIN1->getSequencia()[i] + sinalIN2->getSequencia()[i];
    Sinal *sinalOUT = new Sinal(sequenciaOUT,comprimentoOUT);
    
    delete[] sequenciaOUT;
    return sinalOUT;
}
