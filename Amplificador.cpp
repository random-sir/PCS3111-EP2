#include "Amplificador.h"

Amplificador::Amplificador(double ganho) : ganho(ganho){ //O construtor da classe base nao precisa ser chamado explicitamente, pois nao possui argumentos. 
                                                         //Logo, o construtor chamado implicitamente(default) funciona.
}

Amplificador::~Amplificador(){
}

Sinal* Amplificador::processar(Sinal *sinalIN){
    int comprimentoOUT = sinalIN->getComprimento();
    double *sequenciaOUT = new double[comprimentoOUT];
    
    for (int i = 0; i < comprimentoOUT; i++)
        sequenciaOUT[i] = sinalIN->getSequencia()[i] * ganho;
    Sinal *sinalOUT = new Sinal(sequenciaOUT, comprimentoOUT);
    
    delete[] sequenciaOUT;
    return sinalOUT;
}

void Amplificador::setGanho(double ganho){
    this->ganho = ganho;
}

double Amplificador::getGanho(){
    return ganho;
}
