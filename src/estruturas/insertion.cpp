#include "../melhoria_servidor/melhoria.hpp"

bool Melhoria::insertion()
{
    int custoSolucaoAtual = solucaoAtual->getCustoTotal();
    int custoSolucaoNova = solucaoAtual->getCustoTotal();
    int jobAlocado = -1;
    int indexServidorJobAlocado = -1;
    int indexJobASerRemovido = -1;
    int custoFixo = problemaServidor->getCustoFixoJobNaoAlocado();

    vector<int> &listaJobsNaoAlocados = solucaoAtual->getListaJobsNaoAlocados();
    vector<Servidor> &listaServidores = solucaoAtual->getListaServidores();
    vector<vector<int>> &matrixTempoServidorJob = problemaServidor->getMatrizTempoServidorJob();
    vector<vector<int>> &matrixCustoServidorJob = problemaServidor->getMatrizCustoServidorJob();

    int sizeListaServidores = listaServidores.size();
    int sizeListaJobsNaoAlocados = listaJobsNaoAlocados.size();

    for (int i = 0; i < sizeListaServidores; i++)
    {
        Servidor &servidorAtual = listaServidores[i];
        int tempoDisponivelServidorAtual = servidorAtual.getTempoDisponivel();

        for (int j = 0; j < sizeListaJobsNaoAlocados; j++)
        {
            int jobNaoAlocadoAtual = listaJobsNaoAlocados[j];
            int custoJobSeFosseAlocado = matrixCustoServidorJob[i][jobNaoAlocadoAtual];
            int tempoJobSeFosseAlocado = matrixTempoServidorJob[i][jobNaoAlocadoAtual];
            int custoSolucaoSeAlocarJob = custoSolucaoAtual - custoFixo + custoJobSeFosseAlocado;

            if (tempoDisponivelServidorAtual >= tempoJobSeFosseAlocado &&
                custoSolucaoSeAlocarJob < custoSolucaoNova)
            {
                custoSolucaoNova = custoSolucaoSeAlocarJob;
                jobAlocado = jobNaoAlocadoAtual;
                indexServidorJobAlocado = i;
                indexJobASerRemovido = j;
            }
        }
    }

    if (jobAlocado != -1)
    {
        solucaoAtual->removerJobNaoAlocado(indexJobASerRemovido);
        solucaoAtual->setCustoTotal(custoSolucaoNova);
        listaServidores[indexServidorJobAlocado].adicionarJob(jobAlocado);
        return true;
    }
    return false;
}