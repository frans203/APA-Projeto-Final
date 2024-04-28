#include "./problema/problema_servidor.hpp"
#include "./solucao/solucao_servidores.hpp"
#include "./guloso/guloso.hpp"
#include "./melhoria_servidor/melhoria.hpp"
#include "./metaheuristicas/metaheuristica.hpp"
#include "./rodarTodos.cpp"
#include <chrono>
#include <vector>

int main()
{

	// rodarTodos();

	using namespace std::chrono;

	Guloso *guloso;
	SolucaoServidores *solucao_guloso;
	SolucaoServidores *solucao_vnd;
	SolucaoServidores *solucao_meta;
	Melhoria *melhoria;
	Metaheuristica *metaheuristica;

	int maxIteracoes = 10;
	int maxPerturbacoes = 250;

	ProblemaServidor *problemaServidor8 = new ProblemaServidor("instances/n5m15A.txt");
	cout << "\n################################## [n5m15A.txt] ##################################" << endl;
	problemaServidor8->lerInstanciaProblema();
	guloso = new Guloso(problemaServidor8);
	solucao_vnd = new SolucaoServidores(problemaServidor8);

	auto inicio = high_resolution_clock::now();
	solucao_guloso = guloso->executar();
	auto fim = high_resolution_clock::now();

	nanoseconds duracao = duration_cast<nanoseconds>(fim - inicio);

	cout << "\nCusto Guloso: " << solucao_guloso->getCustoTotal() << endl;
	cout << "Tempo de execução Guloso: " << duracao.count() << " nanosegundos\n"
		 << endl;

	//-----------------------------------------------------------------------------------

	*solucao_vnd = *solucao_guloso;

	melhoria = new Melhoria(solucao_vnd, problemaServidor8);

	inicio = high_resolution_clock::now();
	melhoria->vnd();
	fim = high_resolution_clock::now();

	duracao = duration_cast<nanoseconds>(fim - inicio);

	cout << "Custo VND: " << solucao_vnd->getCustoTotal() << endl;
	cout << "Tempo de execução VND: " << duracao.count() << " nanosegundos\n"
		 << endl;

	//-----------------------------------------------------------------------------------

	metaheuristica = new Metaheuristica(problemaServidor8);

	inicio = high_resolution_clock::now();
	solucao_meta = metaheuristica->ils(maxIteracoes, maxPerturbacoes);
    // solucao_meta->gerarArquivoSaida("saidas/n5m15A_saida.txt");

	fim = high_resolution_clock::now();

	duracao = duration_cast<nanoseconds>(fim - inicio);

	cout << "Custo Metaheuristica: " << solucao_meta->getCustoTotal() <<  endl;
	cout << "Tempo de execução Metaheuristica: " << duracao.count() << " nanosegundos\n"
		 << endl;

	solucao_meta->printSolucao();


	return 0;
}