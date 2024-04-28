#include "guloso.hpp"

Guloso::Guloso(ProblemaServidor *problema)
{
    problemaServidor = problema;
}

SolucaoServidores *Guloso::executar()
{
    SolucaoServidores *solucao = new SolucaoServidores(problemaServidor);
    vector<int> &arrayCapacidadesTempoServidores = problemaServidor->getCapacidadesTempoServidores();
    vector<vector<int>> &matrizCustoServidorJob = problemaServidor->getMatrizCustoServidorJob();
    vector<vector<int>> &matrizTempoServidorJob = problemaServidor->getMatrizTempoServidorJob();
    vector<Servidor> listaServidores = {};
    vector<int> listaJobsNaoAlocados = {};
    int custoFixo = problemaServidor->getCustoFixoJobNaoAlocado();
    int quantidadeJobs = problemaServidor->getQuantidadeJobs();
    int sizeArrayCapacidadesTempoServidores = arrayCapacidadesTempoServidores.size();
    int custoParaSolucao = 0;

    for (int i = 0; i < sizeArrayCapacidadesTempoServidores; i++)
    {
        Servidor *newServidor = new Servidor(i, arrayCapacidadesTempoServidores[i]);
        listaServidores.push_back(*newServidor);
    }

    vector<bool> arrayVerificaJobsAlocados(quantidadeJobs, false);

    for (int i = 0; i < problemaServidor->getQuantidadeServidores(); i++)
    {

        for (int j = 0; j < quantidadeJobs; j++)
        {
            int custoJobAtual = matrizCustoServidorJob[i][j];
            int tempoJobAtual = matrizTempoServidorJob[i][j];

            // verifica se o job nao foi alocado e se eh possivel add ele no servidor
            if (!arrayVerificaJobsAlocados[j] &&
                (listaServidores[i].getTempoDisponivel() >= tempoJobAtual))
            {
                listaServidores[i].adicionarJob(j);

                custoParaSolucao += custoJobAtual;
                arrayVerificaJobsAlocados[j] = true;
            }
        }
    }

    for (size_t i = 0; i < arrayVerificaJobsAlocados.size(); i++)
    {
        if (!arrayVerificaJobsAlocados[i])
        {
            listaJobsNaoAlocados.push_back(i);
            custoParaSolucao += custoFixo;
        }
    }

    solucao->setCustoTotal(custoParaSolucao);
    solucao->setListaServidores(listaServidores);
    solucao->setListaJobsNaoAlocados(listaJobsNaoAlocados);

    return solucao;
}