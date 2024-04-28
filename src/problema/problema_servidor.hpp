#ifndef PROBLEMA_SERVIDOR_HPP
#define PROBLEMA_SERVIDOR_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class ProblemaServidor
{
private:
    static ProblemaServidor *instancia;
    string nomeInstancia;
    int quantidadeJobs;
    int quantidadeServidores;
    int custoFixoJobNaoAlocado;
    vector<int> capacidadesTempoServidores;
    vector<vector<int>> matrizTempoServidorJob;
    vector<vector<int>> matrizCustoServidorJob;

public:
    ProblemaServidor(string instancia);
    static ProblemaServidor *obterInstancia();

    void lerInstanciaProblema();
    void mostrarInstanciaProblema();

    void setCapacidadesTempoServidores(vector<int> &array);
    void setMatrizTempoServidorJob(vector<vector<int>> matriz);
    void setMatrizCustoServidorJob(vector<vector<int>> matriz);
    void setQuantidadeJobs(int quantidade);
    void setQuantidadeServidores(int quantidade);
    void setCustoFixoJobNaoAlocado(int custo);

    vector<int> &getCapacidadesTempoServidores();
    vector<vector<int>> &getMatrizTempoServidorJob();
    vector<vector<int>> &getMatrizCustoServidorJob();
    int getQuantidadeJobs();
    int getQuantidadeServidores();
    int getCustoFixoJobNaoAlocado();
};

#endif