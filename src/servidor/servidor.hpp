#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP

#include "../problema/problema_servidor.hpp"
#include <vector>
#include <climits>

using namespace std;

class Servidor
{
private:
    vector<int> listaJobsAlocados;
    int id;
    int tempoMaximo;
    int tempoUsado;
    int tempoDisponivel;
    int qtdJobs;
    int custoTotal;
    ProblemaServidor *instanciaDoProblema;

public:
    Servidor(int id, int tempoMax);

    vector<int> &getListaJobsAlocados();
    int getId();
    int getTempoMaximo();
    int getTempoUsado();
    int getCustoServidor();
    int getTempoDisponivel();
    int getQtdJobs();

    void adicionarJob(int newjob);
    void removerJob(int jobIndex);
};

#endif