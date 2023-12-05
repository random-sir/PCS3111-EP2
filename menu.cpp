#include "Amplificador.h"
#include "Derivador.h"
#include "Grafico.h"
#include "Integrador.h"
#include "Modulo.h"
#include "ModuloRealimentado.h"
#include "ModuloEmSerie.h"
#include "ModuloEmParalelo.h"
#include "PersistenciaDeModulo.h"
#include "Sinal.h"
#include "Somador.h"
#include <cmath>
#include <iostream>
using namespace std;

Sinal* novoSinal();
Sinal* novaOperacao(Sinal *sinalIN,  Modulo *modulo);

void menu(){
    /*implementacao da interface*/
    //ATENÇÃO, EM TODAS AS PARTES DESSE CÓDIGO REAPROVEITEI A VARIÁVEL "opcao" PARA GUARDAR OS DIFERENTES INPUTS DO USUÁRIO
    int opcao;
    Sinal *sinalIN;
    cout << "\tSimulink em C++"                      << endl
         << "Qual simulacao voce gostaria de fazer?" << endl
         << "1) Circuito advindo de arquivo"         << endl
         << "2) Sua propria sequencia de operacoes"  << endl
         << "Escolha: ";
    cin >> opcao;
    cout << endl;
    sinalIN = novoSinal();
    
    Modulo *modulo;
    Sinal *sinalOUT;
    string nomeDoArquivo;
    if (opcao == 1){
        cout << "Qual o nome do arquivo a ser lido?" << endl
             << "Nome: ";
        cin >> nomeDoArquivo;
        cout << endl;
        PersistenciaDeModulo *PDM = new PersistenciaDeModulo(nomeDoArquivo);
        modulo = PDM->lerDeArquivo();
        sinalOUT = modulo->processar(sinalIN);
        delete sinalIN;
        delete PDM;
    }else{
        cout << "Qual estrutura de operacoes voce deseja ter como base?" << endl
             << "1) Operacoes em serie nao realimentadas"                << endl
             << "2) Operacoes em paralelo nao realimentadas"             << endl
             << "3) Operacoes em serie realimentadas"                    << endl
             << "Escolha: ";
        cin >> opcao;
        cout << endl;
        
        if(opcao == 1)
            modulo = new ModuloEmSerie(); //Upcasting eh nao problematico, pois ocorreria ao passar o argumento para novaOperacao
        else if(opcao == 2)
            modulo = new ModuloEmParalelo();
        else
            modulo = new ModuloRealimentado();
        sinalOUT = novaOperacao(sinalIN, modulo);
    }
    
    Grafico *grafico = new Grafico("Resultado Final", sinalOUT->getSequencia(), sinalOUT->getComprimento());
    grafico->plot();
    delete grafico;
    delete sinalOUT;

    cout << "Voce gostaria de salvar o circuito em um novo arquivo?" << endl
         << "1) Sim" << endl
         << "2) Nao" << endl
         << "Escolha: ";
    cin >> opcao;
    cout << endl;

    if(opcao == 1){
        cout << "Qual o nome do arquivo a ser escrito?" << endl
             << "Nome: ";
        cin >> nomeDoArquivo;
        cout << endl;
        PersistenciaDeModulo *PDM = new PersistenciaDeModulo(nomeDoArquivo);
        PDM->salvarEmArquivo(modulo);
        delete modulo;
        delete PDM;
    }
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

    if (opcao == 2){
        double constante;
        cout << "Qual o valor dessa constante?" << endl 
             << "C = ";
        cin >> constante;
        cout << endl;
        Sinal *sinalOUT = new Sinal(constante, tamanhoMaximo);
        return sinalOUT;
    }

    if (opcao == 1){
        for (int n = 0; n < tamanhoMaximo; n++) 
            sequencia[n] = 5 + 3 * cos(n * (M_PI / 8));
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

Sinal* novaOperacao(Sinal *sinalIN, Modulo *modulo) {
    int opcao;
    cout << "Qual operacao voce gostaria de fazer?" << endl
         << "1) Amplificar"                         << endl
         << "2) Derivar"                            << endl
         << "3) Integrar"                           << endl
         << "Escolha: ";
    cin >> opcao;
    cout << endl;
        
    Sinal *sinalOUT = nullptr;
    if (opcao == 1){
        double ganho;
        cout << "Qual o ganho dessa amplificacao?" << endl
             << "g = ";
        cin >> ganho;
        cout << endl;
        Amplificador *amplificadorOperacao = new Amplificador(ganho);
        modulo->adicionar(amplificadorOperacao);
        sinalOUT = modulo->processar(sinalIN);
        delete sinalIN;
    } else if (opcao == 2){
        Derivador *derivadorOperacao = new Derivador();
        modulo->adicionar(derivadorOperacao);
        sinalOUT = modulo->processar(sinalIN);
        delete sinalIN;
    } else{
        Integrador *integradorOperacao = new Integrador();
        modulo->adicionar(integradorOperacao);
        sinalOUT = modulo->processar(sinalIN);
        delete sinalIN;
    }
    
    cout << "O que voce quer fazer agora?"               << endl
         << "1) Realizar mais uma operacao no resultado" << endl
         << "2) Imprimir o resultado"                    << endl
         << "Escolha: ";
    cin >> opcao;
    cout << endl;
    if (opcao == 1){
        sinalOUT = novaOperacao(sinalOUT, modulo); //Solucao recursiva
    }
    else delete modulo; //necessario, pois modulo eh alocado dinamicamente e nao eh deletado em qualquer outro momento
                       //Essa delecao nao afetara a recursao, pois apenas ocorre no fim da mesma
    return sinalOUT;
}
