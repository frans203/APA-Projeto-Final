#ifndef SOLUCAO_SERVIDORES_HPP
#define SOLUCAO_SERVIDORES_HPP

#include "../problema/problema_servidor.hpp"
#include "../servidor/servidor.hpp"
#include <vector>
#include <iostream>

using namespace std;

class SolucaoServidores
{
private:
    vector<Servidor> listaServidores;
    vector<int> listaJobsNaoAlocados;
    ProblemaServidor *problemaServidor;
    int custoTotal;

public:
    SolucaoServidores(
        ProblemaServidor *problemaServidor);
    SolucaoServidores(
        vector<Servidor> listaServidores,
        vector<int> listaJobsNaoAlocados,
        int custoTotal,
        ProblemaServidor *problemaServidor);

    void setListaServidores(vector<Servidor> listaServidores);
    void setListaJobsNaoAlocados(vector<int> listaJobs);
    void setCustoTotal(int custo);

    vector<Servidor> &getListaServidores();
    vector<int> &getListaJobsNaoAlocados();

    int getCustoTotal();
    void inserirJobNaoAlocado(int job);
    void removerJobNaoAlocado(int IndexJob);

    void printSolucao();
    void gerarArquivoSaida(string nome);
};

#endif