#include "problema_servidor.hpp"

ProblemaServidor *ProblemaServidor::instancia = nullptr;

ProblemaServidor::ProblemaServidor(string arquivoInstancia)
{
    nomeInstancia = arquivoInstancia;
    ProblemaServidor::instancia = this;
}

ProblemaServidor *ProblemaServidor::obterInstancia()
{
    return instancia;
}

vector<vector<int>> lerMatriz(
    ifstream &arquivo,
    int quantidadeServidores,
    int quantidadeJobs)
{
    vector<vector<int>> matriz;
    string linha = "";
    int countLinha = 0;

    getline(arquivo, linha);
    while (linha.empty() || (int)linha.length() < quantidadeJobs)
    {
        getline(arquivo, linha);
    }

    while (!linha.empty() && countLinha < quantidadeServidores)
    {
        vector<int> linhaMatriz = {};

        istringstream iss(linha);
        int valor = 0;
        while (iss >> valor)
        {
            linhaMatriz.push_back(valor);
        }
        matriz.push_back(linhaMatriz);
        getline(arquivo, linha);
        countLinha++;
    }
    return matriz;
}

void printVector(vector<int> vector)
{
    cout << "[ ";
    int size = vector.size();
    for (int i = 0; i < size; i++)
    {
        cout << vector[i] << " ";
    }
    cout << "]" << endl;
}

void ProblemaServidor::lerInstanciaProblema()
{
    ifstream arquivo(nomeInstancia);

    if (!arquivo || !arquivo.is_open())
    {
        cerr << "ERRO: Nao foi possível abrir arquivo" << endl;
        return;
    }
    int quantidadeJobs = 0, quantidadeServidores = 0, custoFixoNaoAlocado = 0;
    vector<int> arrArquivoCapacidadeTempoServidores;
    arquivo >> quantidadeJobs >> quantidadeServidores >> custoFixoNaoAlocado;

    setQuantidadeJobs(quantidadeJobs);
    setQuantidadeServidores(quantidadeServidores);
    setCustoFixoJobNaoAlocado(custoFixoNaoAlocado);

    for (int i = 0; i < quantidadeServidores; i++)
    {
        int valorAtual;
        arquivo >> valorAtual;
        arrArquivoCapacidadeTempoServidores.push_back(valorAtual);
    }

    setCapacidadesTempoServidores(arrArquivoCapacidadeTempoServidores);
    setMatrizTempoServidorJob(lerMatriz(arquivo, quantidadeServidores, quantidadeJobs));
    setMatrizCustoServidorJob(lerMatriz(arquivo, quantidadeServidores, quantidadeJobs));
}

void ProblemaServidor::mostrarInstanciaProblema()
{
    cout << "INFORMAÇÕES DA INSTANCIA" << endl;

    cout << "n (numero de jobs): " << getQuantidadeJobs() << endl;
    cout << "m (numero de servidores): " << getQuantidadeServidores() << endl;
    cout << "p (custo fixo para cada job não alocado): " << getCustoFixoJobNaoAlocado() << endl;
    cout << endl;
    cout << "array Bs (quantidade de tempo max para cada servidor s):" << endl;

    for (const auto &i : getCapacidadesTempoServidores())
    {
        cout << i << " ";
    }
    cout << endl;
    cout << endl;

    cout << "matrix Tsj(quantidade de tempo para jobs em servidores):" << endl;
    for (const auto &i : getMatrizTempoServidorJob())
    {
        for (const auto &j : i)
        {
            cout << setw(2) << setfill('0') << j << " ";
        }
        cout << endl;
    }

    cout << endl;

    cout << "matrix Csj(custo para jobs em servidores):" << endl;

    for (const auto &i : getMatrizCustoServidorJob())
    {
        for (const auto &j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}

void ProblemaServidor::setCapacidadesTempoServidores(vector<int> &array)
{
    capacidadesTempoServidores = array;
}

void ProblemaServidor::setMatrizTempoServidorJob(vector<vector<int>> matriz)
{
    matrizTempoServidorJob = matriz;
}

void ProblemaServidor::setMatrizCustoServidorJob(vector<vector<int>> matriz)
{
    matrizCustoServidorJob = matriz;
}

void ProblemaServidor::setQuantidadeJobs(int quantidade)
{
    quantidadeJobs = quantidade;
};

void ProblemaServidor::setQuantidadeServidores(int quantidade)
{
    quantidadeServidores = quantidade;
}

void ProblemaServidor::setCustoFixoJobNaoAlocado(int custo)
{
    custoFixoJobNaoAlocado = custo;
}

vector<int> &ProblemaServidor::getCapacidadesTempoServidores()
{
    return capacidadesTempoServidores;
};

vector<vector<int>> &ProblemaServidor::getMatrizTempoServidorJob()
{
    return matrizTempoServidorJob;
}

vector<vector<int>> &ProblemaServidor::getMatrizCustoServidorJob()
{
    return matrizCustoServidorJob;
}

int ProblemaServidor::getQuantidadeJobs()
{
    return quantidadeJobs;
}
int ProblemaServidor::getQuantidadeServidores()
{
    return quantidadeServidores;
}
int ProblemaServidor::getCustoFixoJobNaoAlocado()
{
    return custoFixoJobNaoAlocado;
}