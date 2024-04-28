#include "metaheuristica.hpp"

Metaheuristica::Metaheuristica(ProblemaServidor *problema)
{
    problemaServidor = problema;

    solucaoVNDInicial = new SolucaoServidores(problemaServidor);
    melhorSolucao = new SolucaoServidores(problemaServidor);
    solucaoTemporaria = new SolucaoServidores(problemaServidor);
}

// metodo ILS
SolucaoServidores *Metaheuristica::ils(int maxIter, int maxIterILS)
{

    Guloso *guloso_ILS = new Guloso(problemaServidor);

    delete solucaoVNDInicial;
    solucaoVNDInicial = guloso_ILS->executar();

    Melhoria *melhoriaInicial = new Melhoria(solucaoVNDInicial, problemaServidor);
    melhoriaInicial->vnd();

    *melhorSolucao = *solucaoVNDInicial;

    Melhoria *melhoriaILS = new Melhoria(solucaoTemporaria, problemaServidor);

    for (int i = 0; i < maxIter; i++)
    {
        // resetando o valor da solucaoTemporaria
        *solucaoTemporaria = *solucaoVNDInicial;

        int quantidade_iteracoes = 0;
        while (quantidade_iteracoes < maxIterILS)
        {
            if (this->pert_swap())
            {
                melhoriaILS->vnd();

                if (solucaoTemporaria->getCustoTotal() < melhorSolucao->getCustoTotal())
                {
                    *melhorSolucao = *solucaoTemporaria;
                    quantidade_iteracoes = 0;
                }
            }
            quantidade_iteracoes++;
        }
    }

    return melhorSolucao;
}