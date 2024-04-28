#include "solucao_servidores.hpp"

SolucaoServidores::SolucaoServidores(
    ProblemaServidor *problema)
{
    problemaServidor = problema;
    listaJobsNaoAlocados = {};
    listaServidores = {};
    custoTotal = 0;
}

SolucaoServidores::SolucaoServidores(
    vector<Servidor> listaServers,
    vector<int> listaJobs,
    int custo,
    ProblemaServidor *problema)
{
    listaJobsNaoAlocados = listaJobs;
    listaServidores = listaServers;
    custoTotal = custo;
    problemaServidor = problema;
}

void SolucaoServidores::setCustoTotal(int custo)
{
    custoTotal = custo;
}

void SolucaoServidores::setListaJobsNaoAlocados(vector<int> listaJobs)
{
    listaJobsNaoAlocados = listaJobs;
}

void SolucaoServidores::inserirJobNaoAlocado(int novoJob)
{
    listaJobsNaoAlocados.push_back(novoJob);
}

void SolucaoServidores::removerJobNaoAlocado(int indexJob)
{
    std::swap(listaJobsNaoAlocados[indexJob], listaJobsNaoAlocados[listaJobsNaoAlocados.size() - 1]);
    listaJobsNaoAlocados.pop_back();
}

void SolucaoServidores::setListaServidores(vector<Servidor> listaServers)
{
    listaServidores = listaServers;
}

int SolucaoServidores::getCustoTotal()
{
    return custoTotal;
}

vector<int> &SolucaoServidores::getListaJobsNaoAlocados()
{
    return listaJobsNaoAlocados;
}

vector<Servidor> &SolucaoServidores::getListaServidores()
{
    return listaServidores;
}

void SolucaoServidores::printSolucao()
{

    cout << "" << endl;
    int sizeListaServidores = listaServidores.size();

    std::cout << "LISTA DE JOBS ALOCADOS PARA CADA SERVIDOR" << endl;
    for (int i = 0; i < sizeListaServidores; i++)
    {
        cout << "  SERVIDOR " << listaServidores[i].getId() << " | Tempo Máximo: " << listaServidores[i].getTempoMaximo()
             << " | Tempo Usado: " << listaServidores[i].getTempoUsado()
             << " | Custo Servidor: " << listaServidores[i].getCustoServidor() << endl;

        int sizeListaJobsAlocados = listaServidores[i].getListaJobsAlocados().size();

        for (int j = 0; j < sizeListaJobsAlocados; j++)
        {
            int jobAtual = listaServidores[i].getListaJobsAlocados()[j];
            int custoJobAtual = problemaServidor->getMatrizCustoServidorJob()[i][jobAtual];
            int tempoJobAtual = problemaServidor->getMatrizTempoServidorJob()[i][jobAtual];

            cout << "   job: " << jobAtual << " | custo: " << custoJobAtual << " | tempo: " << tempoJobAtual << endl;
        }

        cout << "" << endl;
    }

    cout << "" << endl;

    std::cout << "LISTA DE JOBS NÃO ALOCADOS" << endl;

    int sizeListaJobsNaoAlocados = listaJobsNaoAlocados.size();

    for (int i = 0; i < sizeListaJobsNaoAlocados; i++)
    {
        int jobAtual = listaJobsNaoAlocados[i];
        cout << " job: " << jobAtual << " | "
             << "custo: " << problemaServidor->getCustoFixoJobNaoAlocado() << " | " << endl;
    }

    cout << "" << endl;

    cout << "CUSTO TOTAL DA SOLUÇÃO: " << getCustoTotal() << endl;
}

void SolucaoServidores::gerarArquivoSaida(string nome_solucao)
{
    ofstream arquivo(nome_solucao);

    if (arquivo.is_open())
    {
        arquivo << custoTotal << "\n";
        arquivo << custoTotal - getListaJobsNaoAlocados().size() * problemaServidor->getCustoFixoJobNaoAlocado() << "\n";
        arquivo << getListaJobsNaoAlocados().size() * problemaServidor->getCustoFixoJobNaoAlocado() << "\n";
        arquivo << "\n";

        int sizeListaServidores = listaServidores.size();

        for (int i = 0; i < sizeListaServidores; i++)
        {
            Servidor servidorAtual = getListaServidores()[i];
            vector<int> listaJobsAlocados = servidorAtual.getListaJobsAlocados();
            int sizeListaJobsAlocados = listaJobsAlocados.size();

            for (int j = 0; j < sizeListaJobsAlocados; j++)
            {
                arquivo << listaJobsAlocados[j] << " ";
            }

            arquivo << "\n";
        }

        arquivo.close();
    }
    else
    {
        cerr << "Erro ao abrir arquivo \n";
    }
}