#include "../melhoria_servidor/melhoria.hpp"

bool Melhoria::remove()
{
    int custoAtual = solucaoAtual->getCustoTotal();
    int custoTotalSolucao = solucaoAtual->getCustoTotal();
    int custoFixoJobNaoAlocado = problemaServidor->getCustoFixoJobNaoAlocado();
    int jobASerRemovido = -1;
    int indexJobASerRemovido = -1;
    int indexServidorJobASerRemovido = -1;
    int sizeListaServidores = solucaoAtual->getListaServidores().size();

    vector<vector<int>> &matrizCustoServidorJob = problemaServidor->getMatrizCustoServidorJob();
    vector<Servidor> &listaServidores = solucaoAtual->getListaServidores();

    for (int i = 0; i < sizeListaServidores; i++)
    {
        Servidor &servidorAtual = listaServidores[i];
        int sizeListaJobsAlocados = servidorAtual.getListaJobsAlocados().size();

        for (int j = 0; j < sizeListaJobsAlocados; j++)
        {
            int jobAtual = servidorAtual.getListaJobsAlocados()[j];
            int custoJobAtual = matrizCustoServidorJob[i][jobAtual];
            int novoCusto = custoTotalSolucao - custoJobAtual + custoFixoJobNaoAlocado;

            if (novoCusto < custoAtual)
            {
                custoAtual = novoCusto;
                jobASerRemovido = jobAtual;
                indexServidorJobASerRemovido = i;
                indexJobASerRemovido = j;
            }
        }
    }

    if (jobASerRemovido != -1)
    {
        listaServidores[indexServidorJobASerRemovido].removerJob(indexJobASerRemovido);
        solucaoAtual->inserirJobNaoAlocado(jobASerRemovido);
        solucaoAtual->setCustoTotal(custoAtual);

        return true;
    }

    return false;
}