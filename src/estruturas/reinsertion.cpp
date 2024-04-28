#include "../melhoria_servidor/melhoria.hpp"
#include <climits>

bool Melhoria::reinsertion(int tamBloco)
{
    if (tamBloco < 1)
    {
        cerr << "O reinsertion deve ter aragumento > 0" << endl;
        exit(1);
    }

    int custoTotalSolucao = solucaoAtual->getCustoTotal();
    int melhorCustoEncontrado = custoTotalSolucao;

    int indexBlocoAlvo = -1; // guarda o índice do primeiro elemento do bloco
    int indexServidorOrigem = -1;
    int indexServidorDestino = -1;

    vector<Servidor> &listaServidores = solucaoAtual->getListaServidores();
    int qtdServidores = listaServidores.size();
    vector<vector<int>> &matrizTempoServidorJob = problemaServidor->getMatrizTempoServidorJob();
    vector<vector<int>> &matrizCustoServidorJob = problemaServidor->getMatrizCustoServidorJob();

    // elege o servidor origem
    for (int i = 0; i < qtdServidores; i++)
    {
        Servidor &servidorOrigem = listaServidores[i];
        int qtdJobsServidorOrigem = servidorOrigem.getQtdJobs();

        if (qtdJobsServidorOrigem < tamBloco)
            continue;
        // percorre os jobs do servidor origem até o job em que o tamanho do bloco se encaixa exatamente no extremo final
        for (int j = 0; j <= qtdJobsServidorOrigem - tamBloco; j++)
        {
            int tempoBlocoServidorOrigem = 0;
            int custoBlocoServidorOrigem = 0;

            // percorre os blocos de jobs alocados no servidor origem e obtém o tempo e o custo de cada um
            for (int aux = 0; aux < tamBloco; aux++)
            {
                int jobServidorOrigem = servidorOrigem.getListaJobsAlocados()[j + aux];
                tempoBlocoServidorOrigem += matrizTempoServidorJob[i][jobServidorOrigem];
                custoBlocoServidorOrigem += matrizCustoServidorJob[i][jobServidorOrigem];
            }

            // elege o servidor destino
            for (int k = 0; k < qtdServidores; k++)
            {
                if (k == i) // destino = origem
                    continue;

                Servidor &servidorDestino = listaServidores[k];
                int tempoDispServidorDestino = servidorDestino.getTempoDisponivel();
                int tempoBlocoServidorDestino = 0;
                int custoBlocoServidorDestino = 0;

                // percorre os bloco de jobs alocados no servidor destino e obtém o tempo e o custo de cada um
                for (int aux = 0; aux < tamBloco; aux++)
                {
                    int jobServidorDestino = servidorOrigem.getListaJobsAlocados()[j + aux];
                    tempoBlocoServidorDestino += matrizTempoServidorJob[k][jobServidorDestino];
                    custoBlocoServidorDestino += matrizCustoServidorJob[k][jobServidorDestino];
                }

                int custoComReinsercao = custoTotalSolucao - custoBlocoServidorOrigem + custoBlocoServidorDestino;

                bool haTempoNoDestino = tempoDispServidorDestino >= tempoBlocoServidorDestino;
                bool houveMelhora = custoComReinsercao < melhorCustoEncontrado;

                // elege a melhor reinserção até o momento e salva os dados dela
                if (haTempoNoDestino && houveMelhora)
                {
                    indexServidorOrigem = i;
                    indexBlocoAlvo = j; // primeiro job do bloco no servidor origem
                    indexServidorDestino = k;
                    melhorCustoEncontrado = custoComReinsercao;
                }
            }
        }
    }

    if (indexBlocoAlvo != -1)
    {
        Servidor &servidorOrigem = listaServidores[indexServidorOrigem];
        Servidor &servidorDestino = listaServidores[indexServidorDestino];
        vector<int> &jobsOrigem = servidorOrigem.getListaJobsAlocados();

        // percorre o bloco, adiciona os elementos no servidor alvo e retira do servidor origem
        for (int aux = 0; aux < tamBloco; aux++)
        {
            int IndexJobReinsert = indexBlocoAlvo + aux;
            servidorDestino.adicionarJob(jobsOrigem[IndexJobReinsert]);
            servidorOrigem.removerJob(IndexJobReinsert);
        }
        solucaoAtual->setCustoTotal(melhorCustoEncontrado);
        return true; // encontrou solução melhor
    }

    return false; // não encontrou solução melhor
};