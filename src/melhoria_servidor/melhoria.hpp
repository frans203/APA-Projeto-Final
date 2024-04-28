#ifndef MELHORIA_HPP
#define MELHORIA_HPP
#define QUANTIDADE_ESTRUTURAS_VIZINHANCA 9

#include "../solucao/solucao_servidores.hpp"
#include <algorithm>

using namespace std;

class Melhoria
{
private:
    SolucaoServidores *solucaoAtual;
    ProblemaServidor *problemaServidor;

public:
    Melhoria(SolucaoServidores *solucao, ProblemaServidor *problema);
    SolucaoServidores *vnd();
    bool swap(int tamamnhoBloco1, int tamanhoBlcoo2);
    bool reinsertion(int tamBloco);
    bool remove();
    bool insertion();
    int verificaCustoServidores();
};

#endif