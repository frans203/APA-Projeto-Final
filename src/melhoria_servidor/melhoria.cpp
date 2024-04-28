#include "melhoria.hpp"

Melhoria::Melhoria(SolucaoServidores *solucao, ProblemaServidor *problema)
{
  solucaoAtual = solucao;
  problemaServidor = problema;
}

int Melhoria::verificaCustoServidores()
{

  vector<vector<int>> matrizCusto = problemaServidor->getMatrizCustoServidorJob();
  vector<vector<int>> matrizTempo = problemaServidor->getMatrizTempoServidorJob();

  int custoFixo = problemaServidor->getCustoFixoJobNaoAlocado();
  int qtdJobsNaoAlocados = solucaoAtual->getListaJobsNaoAlocados().size();
  int custoTotal = custoFixo * qtdJobsNaoAlocados;

  for (size_t i = 0; i < solucaoAtual->getListaServidores().size(); i++)
  {
    for (size_t j = 0; j < solucaoAtual->getListaServidores()[i].getListaJobsAlocados().size(); j++)
    {
      custoTotal += matrizCusto[i][solucaoAtual->getListaServidores()[i].getListaJobsAlocados()[j]];
    }
  }

  return custoTotal;
}
