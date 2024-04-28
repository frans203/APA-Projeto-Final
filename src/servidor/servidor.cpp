#include "servidor.hpp"

Servidor::Servidor(int index, int tempoMax)
{
    listaJobsAlocados = {};
    id = index;
    tempoMaximo = tempoMax;
    tempoUsado = 0;
    tempoDisponivel = tempoMax;
    qtdJobs = 0;
    custoTotal = 0;
    instanciaDoProblema = ProblemaServidor::obterInstancia();
}

vector<int> &Servidor::getListaJobsAlocados()
{
    return listaJobsAlocados;
}

int Servidor::getId()
{
    return id;
}

int Servidor::getTempoMaximo()
{
    return tempoMaximo;
}

int Servidor::getTempoUsado()
{
    return tempoUsado;
}

int Servidor::getCustoServidor()
{
    return custoTotal;
}

int Servidor::getTempoDisponivel()
{
    return tempoDisponivel;
}

int Servidor::getQtdJobs()
{
    return qtdJobs;
}

void Servidor::adicionarJob(int novoJob)
{
    int tempoNovoJob = instanciaDoProblema->getMatrizTempoServidorJob()[id][novoJob];
    if (tempoNovoJob > tempoDisponivel)
    {
        cerr << "Erro: job '" << novoJob << "' nao cabe no servidor '" << id << "'. Tempo disponivel:[" << tempoDisponivel << "] - Tempo necessário:[" << tempoNovoJob << +"]";
        exit(1);
    }
    listaJobsAlocados.push_back(novoJob);
    tempoUsado += tempoNovoJob;
    tempoDisponivel -= tempoNovoJob;
    qtdJobs++;
    custoTotal += instanciaDoProblema->getMatrizCustoServidorJob()[id][novoJob];
}

void Servidor::removerJob(int jobIndex)
{
    int tempoJobRemovido = instanciaDoProblema->getMatrizTempoServidorJob()[id][listaJobsAlocados[jobIndex]];
    int custoJobRemovido = instanciaDoProblema->getMatrizCustoServidorJob()[id][listaJobsAlocados[jobIndex]];

    // quando for o último ou a posição indicada extrapola o array, só da swap no final
    if (!(jobIndex >= (int)listaJobsAlocados.size() - 1))
        std::swap(listaJobsAlocados[jobIndex], listaJobsAlocados[qtdJobs - 1]);
    listaJobsAlocados.pop_back();

    tempoUsado -= tempoJobRemovido;
    tempoDisponivel += tempoJobRemovido;

    qtdJobs--;
    custoTotal -= custoJobRemovido;
}
