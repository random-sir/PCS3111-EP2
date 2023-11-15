#include "Piloto.h"

Piloto::Piloto(double ganho){
    amplificadorPiloto = new Amplificador(ganho);
    integradorPiloto = new Integrador();
}

Piloto::~Piloto(){
    delete amplificadorPiloto;
    delete integradorPiloto;
}

Sinal* Piloto::processar(Sinal *sinalIN){
    Sinal *sinalAmplificado = amplificadorPiloto->processar(sinalIN);
    Sinal *sinalOUT = integradorPiloto->processar(sinalAmplificado);
    delete sinalAmplificado;
    return sinalOUT;
}
