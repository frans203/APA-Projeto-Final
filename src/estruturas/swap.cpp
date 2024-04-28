#include "../melhoria_servidor/melhoria.hpp"

bool Melhoria::swap(int tamanhoBloco1, int tamanhoBloco2)
{
    vector<vector<int>> &matrizTempo = problemaServidor->getMatrizTempoServidorJob();
    vector<vector<int>> &matrizCusto = problemaServidor->getMatrizCustoServidorJob();

    vector<Servidor> &listaServidores = solucaoAtual->getListaServidores();
    int quantidadeServidores = listaServidores.size();

    int custoInicialSolucao = solucaoAtual->getCustoTotal();
    int melhorCustoEncontrado = custoInicialSolucao;

    int idxServidor1 = -1;
    int inicioBloco1 = -1;

    int idxServidor2 = -1;
    int inicioBloco2 = -1;

    // definindo o primeiro servidor
    for (int i = 0; i < quantidadeServidores; i++)
    {
        Servidor &servidor1 = listaServidores[i];

        int tempoServidor1 = servidor1.getTempoUsado();
        int tempoMaximoServidor1 = servidor1.getTempoMaximo();

        vector<int> &listaJobsServidor1 = servidor1.getListaJobsAlocados();
        int quantidadeJobsServidor1 = servidor1.getQtdJobs();

        // definindo o segundo servidor
        int j = (tamanhoBloco1 == tamanhoBloco2) ? i + 1 : 0; // Inicialização de acordo com a condição
        for (; j < quantidadeServidores; j++)
        { // Atualização da variável j dentro da expressão do loop
            if (j == i)
                continue;

            Servidor &servidor2 = listaServidores[j];

            int tempoServidor2 = servidor2.getTempoUsado();
            int tempoMaximoServidor2 = servidor2.getTempoMaximo();

            vector<int> &listaJobsServidor2 = servidor2.getListaJobsAlocados();
            int quantidadeJobsServidor2 = listaJobsServidor2.size();

            // percorre os jobs do servidor1 até o job em que o tamanho do bloco se encaixa exatamente no extremo final
            for (int k = 0; k <= quantidadeJobsServidor1 - tamanhoBloco1; k++)
            {
                int tempoBloco1 = 0;
                int tempoBloco1Em2 = 0;

                int custoBloco1 = 0;
                int custoBloco1Em2 = 0;

                // obtém os valores de tempo e custo do bloco1 para o servidor1 e para o servidor2
                for (int aux = 0; aux < tamanhoBloco1; aux++)
                {
                    tempoBloco1 += matrizTempo[i][listaJobsServidor1[k + aux]];
                    custoBloco1 += matrizCusto[i][listaJobsServidor1[k + aux]];

                    tempoBloco1Em2 += matrizTempo[j][listaJobsServidor1[k + aux]];
                    custoBloco1Em2 += matrizCusto[j][listaJobsServidor1[k + aux]];
                }

                // percorre os jobs do servidor2 até o job em que o tamanho do bloco se encaixa exatamente no extremo final
                for (int l = 0; l <= quantidadeJobsServidor2 - tamanhoBloco2; l++)
                {
                    int tempoBloco2 = 0;
                    int tempoBloco2Em1 = 0;

                    int custoBloco2 = 0;
                    int custoBloco2Em1 = 0;

                    // percorre os blocos de jobs alocados no servidor2 e obtém o tempo e o custo de cada um
                    for (int aux = 0; aux < tamanhoBloco2; aux++)
                    {
                        tempoBloco2 += matrizTempo[j][listaJobsServidor2[l + aux]];
                        custoBloco2 += matrizCusto[j][listaJobsServidor2[l + aux]];

                        tempoBloco2Em1 += matrizTempo[i][listaJobsServidor2[l + aux]];
                        custoBloco2Em1 += matrizCusto[i][listaJobsServidor2[l + aux]];
                    }

                    bool servidor1SuportaSwap = tempoServidor1 - tempoBloco1 + tempoBloco2Em1 <= tempoMaximoServidor1;
                    bool servidor2SuportaSwap = tempoServidor2 - tempoBloco2 + tempoBloco1Em2 <= tempoMaximoServidor2;

                    // algum dos dois servidores nao tem tempo suficiente para suportar a troca
                    if (!servidor1SuportaSwap || !servidor2SuportaSwap)
                        continue;

                    // custo da simulação
                    int custo = custoInicialSolucao - custoBloco1 - custoBloco2 + custoBloco1Em2 + custoBloco2Em1;

                    if (custo >= melhorCustoEncontrado)
                        continue;

                    // se chegou aqui, então temos uma troca viável, guarda as informações:
                    idxServidor1 = i;
                    idxServidor2 = j;

                    inicioBloco1 = k;
                    inicioBloco2 = l;

                    melhorCustoEncontrado = custo;
                }
            }
        }
    }

    if (melhorCustoEncontrado < custoInicialSolucao)
    {
        vector<int> jobsBloco1Aux = {};

        int qtdJobsServidorAlvo = listaServidores[idxServidor1].getQtdJobs() - 1;
        // adiciona os jobs do servidor 1 ao array auxiliar jobsBloco1Aux, depois remove do servidor 1
        for (int i = 0; i < tamanhoBloco1; i++)
        {
            int indexJobAlvo = inicioBloco1 + i;
            if (indexJobAlvo > qtdJobsServidorAlvo - 1)
                indexJobAlvo = listaServidores[idxServidor1].getQtdJobs() - 1;

            jobsBloco1Aux.push_back(listaServidores[idxServidor1].getListaJobsAlocados()[indexJobAlvo]);
            listaServidores[idxServidor1].removerJob(indexJobAlvo);
            qtdJobsServidorAlvo--;
        }

        // adiciona os jobs do servidor 2 DIRETAMENTE no servidor1, depois remove do servidor 2
        qtdJobsServidorAlvo = listaServidores[idxServidor2].getQtdJobs() - 1;
        for (int j = 0; j < tamanhoBloco2; j++)
        {
            int indexJobAlvo = inicioBloco2 + j;
            if (indexJobAlvo > qtdJobsServidorAlvo - 1)
                indexJobAlvo = listaServidores[idxServidor2].getQtdJobs() - 1;

            listaServidores[idxServidor1].adicionarJob(listaServidores[idxServidor2].getListaJobsAlocados()[indexJobAlvo]);
            listaServidores[idxServidor2].removerJob(indexJobAlvo);
        }

        // adiciona os jobs que estão no array auxiliar ao servidor2
        for (int k = 0; k < tamanhoBloco1; k++)
        {
            listaServidores[idxServidor2].adicionarJob(jobsBloco1Aux[k]);
        }

        solucaoAtual->setCustoTotal(melhorCustoEncontrado);

        return true;
    }
    return false;
}