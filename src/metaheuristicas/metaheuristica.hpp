#ifndef METAHEURISTICA_HPP
#define METAHEURISTICA_HPP

#include "../melhoria_servidor/melhoria.hpp"
#include "../guloso/guloso.hpp"

using namespace std;

class Metaheuristica
{
private:
    ProblemaServidor *problemaServidor;
    SolucaoServidores *solucaoVNDInicial;
    SolucaoServidores *melhorSolucao;
    SolucaoServidores *solucaoTemporaria;

public:
    Metaheuristica(ProblemaServidor *problema);
    SolucaoServidores *ils(int maxIter, int maxIterILS);
    bool pert_swap();
    void pert_reinsertion();
};

#endif