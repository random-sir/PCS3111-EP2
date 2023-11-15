#include "Amplificador.h"
#include "Derivador.h"
#include "Grafico.h"
#include "Integrador.h"
#include "ModuloRealimentado.h"
#include "Piloto.h"
#include "Sinal.h"
#include "Somador.h"
#include <cmath>
#include <iostream>
using namespace std;

Sinal* novoSinal();
void novaOperacao(Sinal *sinalIN);

void menu(){
    /*implementacao da interface*/
    int opcao;
    Sinal *sinalIN;
    cout << "\tSimulink em C++"                      << endl
         << "Qual simulacao voce gostaria de fazer?" << endl
         << "1) Piloto Automatico"                   << endl
         << "2) Sua propria sequencia de operacoes"  << endl
         << "Escolha: ";
    cin >> opcao;
    cout << endl;
    sinalIN = novoSinal();
    
    if (opcao == 1){
        double ganho;
        cout << "Qual o ganho do acelerador?" << endl
             << "g = ";
        cin >> ganho;
        cout << endl;
        ModuloRealimentado *pilotoAutomatico = new ModuloRealimentado(ganho);
        Sinal *sinalOUT = pilotoAutomatico->processar(sinalIN);
        Grafico *grafico = new Grafico("Velocidade do Carro", sinalOUT->getSequencia(), sinalOUT->getComprimento());
        grafico->plot();
        delete sinalIN;
        delete pilotoAutomatico;
        delete grafico;
        delete sinalOUT;
    }else novaOperacao(sinalIN);
}

Sinal* novoSinal(){
    int opcao;
    const int tamanhoMaximo = 60;
    double sequencia[tamanhoMaximo];
    cout << "Qual sinal voce gostaria de utilizar como entrada da sua simulacao?" << endl
         << "1) 5+3*cos(n*pi/8)"                                                  << endl
         << "2) constante"                                                        << endl
         << "3) rampa"                                                            << endl 
         << "Escolha: ";
    cin >> opcao;
    cout << endl;
    
    if (opcao == 1){
        for (int n = 0; n < tamanhoMaximo; n++) 
            sequencia[n] = 5 + 3 * cos(n * (M_PI / 8));
    } else if (opcao == 2){
        double constante;
        cout << "Qual o valor dessa constante?" << endl 
             << "C = ";
        cin >> constante;
        cout << endl;
        for (int n = 0; n < tamanhoMaximo; n++)
            sequencia[n] = constante;
    } else{
        double inclinacao;
        cout << "Qual a inclinacao dessa rampa?" << endl
             << "a = ";
        cin >> inclinacao;
        cout << endl;
        for (int n = 0; n < tamanhoMaximo; n++)
            sequencia[n] = inclinacao * n;
    }
    Sinal *sinalOUT = new Sinal(sequencia, tamanhoMaximo);
    return sinalOUT;
}

void novaOperacao(Sinal *sinalIN) {
    int opcao;
    Sinal *sinalOUT = nullptr;
    cout << "Qual operacao voce gostaria de fazer?" << endl
         << "1) Amplificar"                         << endl
         << "2) Somar"                              << endl
         << "3) Derivar"                            << endl
         << "4) Integrar"                           << endl
         << "Escolha: ";
    cin >> opcao;
    cout << endl;

    if (opcao == 1){
        double ganho;
        cout << "Qual o ganho dessa amplificacao?" << endl
             << "g = ";
        cin >> ganho;
        cout << endl;
        Amplificador *amplificadorOperacao = new Amplificador(ganho);
        sinalOUT = amplificadorOperacao->processar(sinalIN);
        delete sinalIN;
        delete amplificadorOperacao;
    } else if (opcao == 2){
        Somador *somadorOperacao = new Somador();
        cout << "Informe mais um sinal para ser somado." << endl;
        Sinal *sinalSomado = novoSinal();
        sinalOUT = somadorOperacao->processar(sinalIN, sinalSomado); 
        delete sinalIN;
        delete somadorOperacao;
    } else if (opcao == 3){
        Derivador *derivadorOperacao = new Derivador();
        sinalOUT = derivadorOperacao->processar(sinalIN); 
        delete sinalIN;
        delete derivadorOperacao;
    } else{
        Integrador *integradorOperacao = new Integrador();
        sinalOUT = integradorOperacao->processar(sinalIN);
        delete sinalIN;
        delete integradorOperacao;
    }
    
    cout << "O que voce quer fazer agora?"               << endl
         << "1) Realizar mais uma operacao no resultado" << endl
         << "2) Imprimir o resultado para terminar"      << endl
         << "Escolha: ";
    cin >> opcao;
    cout << endl;
    if (opcao == 1){
        novaOperacao(sinalOUT); //Solucao recursiva
    } else{
        Grafico *grafico = new Grafico("Resultado Final", sinalOUT->getSequencia(), sinalOUT->getComprimento());
        grafico->plot();
        delete grafico;
        delete sinalOUT;
    }
}
