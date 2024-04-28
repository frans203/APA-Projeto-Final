#include "../metaheuristicas/metaheuristica.hpp"

bool Metaheuristica::pert_swap()
{
    vector<vector<int>> &matrizTempo = problemaServidor->getMatrizTempoServidorJob();

    vector<Servidor> &listaServidores = solucaoTemporaria->getListaServidores();
    int custoIncialSolucao = solucaoTemporaria->getCustoTotal();

    int quantidadeServidores = listaServidores.size();

    vector<int> listaServidores_NaoVazios = {};

    // indice dos servidores 1 e 2 no array de não vazios
    int idx_nao_vazio1 = -1;
    int idx_nao_vazio2 = -1;

    // indice(valor) real dos servidors
    int idx_servidor1 = -1;
    int idx_servidor2 = -1;

    // indice do jobs nos servidores
    int idx_job1_servidor1 = -1;
    int idx_job2_servidor2 = -1;

    // número do job
    int job1 = 0;
    int job2 = 0;

    // guardando indices dos servidores nao vazios em um array
    for (int i = 0; i < quantidadeServidores; i++)
    {
        if (listaServidores[i].getListaJobsAlocados().size() > 0)
        {
            listaServidores_NaoVazios.push_back(i);
        }
    }

    int quantidade_Servidores_NaoVazios = listaServidores_NaoVazios.size();
    if (quantidade_Servidores_NaoVazios < 2)
    {
        return false;
    }

    // sorteando o indice do primeiro servidor
    idx_nao_vazio1 = rand() % quantidade_Servidores_NaoVazios;
    idx_servidor1 = listaServidores_NaoVazios[idx_nao_vazio1];

    // impedindo o servidor1 de ser sorteado novamente
    std::swap(listaServidores_NaoVazios[idx_nao_vazio1], listaServidores_NaoVazios[quantidade_Servidores_NaoVazios - 1]);
    listaServidores_NaoVazios.pop_back();
    quantidade_Servidores_NaoVazios--;

    // sorteando indice do segundo servidor
    idx_nao_vazio2 = rand() % quantidade_Servidores_NaoVazios;
    idx_servidor2 = listaServidores_NaoVazios[idx_nao_vazio2];

    // coletando informações do servidor1
    Servidor &servidor1 = listaServidores[idx_servidor1];
    vector<int> &listaJobsServidor1 = servidor1.getListaJobsAlocados();
    int quantidadeJobsServidor1 = listaJobsServidor1.size();
    int tempoUsadoServidor1 = servidor1.getTempoUsado();
    int tempoMaximoServidor1 = servidor1.getTempoMaximo();
    int custoInicialServidor1 = servidor1.getCustoServidor();

    // coletando informacoes do servidor2
    Servidor &servidor2 = listaServidores[idx_servidor2];
    vector<int> &listaJobsServidor2 = servidor2.getListaJobsAlocados();
    int quantidadeJobsServidor2 = listaJobsServidor2.size();
    int tempoUsadoServidor2 = servidor2.getTempoUsado();
    int tempoMaximoServidor2 = servidor2.getTempoMaximo();
    int custoInicialServidor2 = servidor2.getCustoServidor();

    // descobrindo indice real do job1
    idx_job1_servidor1 = rand() % quantidadeJobsServidor1;
    job1 = listaJobsServidor1[idx_job1_servidor1];

    // descobrindo indice real do job2
    idx_job2_servidor2 = rand() % quantidadeJobsServidor2;
    job2 = listaJobsServidor2[idx_job2_servidor2];

    // simulando os tempos
    int tempoServidor1SemJob1 = tempoUsadoServidor1 - matrizTempo[idx_servidor1][job1];
    int tempoServidor2SemJob2 = tempoUsadoServidor2 - matrizTempo[idx_servidor2][job2];

    int tempoServidor1ComJob2 = tempoServidor1SemJob1 + matrizTempo[idx_servidor1][job2];
    int tempoServidor2ComJob1 = tempoServidor2SemJob2 + matrizTempo[idx_servidor2][job1];

    // fazendo a troca para perturbar a solucao
    if (tempoServidor1ComJob2 <= tempoMaximoServidor1 && tempoServidor2ComJob1 <= tempoMaximoServidor2)
    {
        servidor1.removerJob(idx_job1_servidor1);
        servidor2.removerJob(idx_job2_servidor2);

        servidor1.adicionarJob(job2);
        servidor2.adicionarJob(job1);

        int novoCusto = custoIncialSolucao - custoInicialServidor1 - custoInicialServidor2 + servidor1.getCustoServidor() + servidor2.getCustoServidor();

        solucaoTemporaria->setCustoTotal(novoCusto);

        return true;
    }

    return false;
}