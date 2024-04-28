#include "./problema/problema_servidor.hpp"
#include "./solucao/solucao_servidores.hpp"
#include "./guloso/guloso.hpp"
#include "./melhoria_servidor/melhoria.hpp"
#include "./metaheuristicas/metaheuristica.hpp"
#include <chrono>
#include <vector>
#include <iostream>
#include <limits>

void rodarTodos()
{
     using namespace chrono;


     srand(time(NULL));

     // Lista de instâncias
     vector<string> instancias = {
          "instances/n5m15A.txt",
          "instances/n5m15B.txt",
          "instances/n25m5A.txt",
          "instances/n30m5A.txt",
          "instances/n60m10.txt",
          "instances/n60m10A.txt"
          };

     // Configurações para o ILS
     int maxIter = 70;
     int maxIterILS = 80;
     int limiteFor = 10;

     // Itera por cada instância
     for (const auto &instancia : instancias)
     {
          cout << "\n################################## [" << instancia << "] ##################################" << endl;

          // Inicialize variáveis para calcular média dos tempos e custos
          nanoseconds totalTempoGuloso = nanoseconds(0);
          nanoseconds totalTempoVND = nanoseconds(0);
          nanoseconds totalTempoILS = nanoseconds(0);
          double totalCustoILS = 0;
          int melhorCustoILS = INT_MAX;

          double CustoGuloso = 0;
          double CustoVND = 0;

          // Rode cada heurística 10 vezes
          for (int i = 0; i < limiteFor; ++i)
          {
               // Crie o problema e leia a instância
               ProblemaServidor *problema = new ProblemaServidor(instancia);
               problema->lerInstanciaProblema();

               // Guloso
               Guloso *guloso = new Guloso(problema);
               auto inicio = high_resolution_clock::now();
               SolucaoServidores *solucao_guloso = guloso->executar();
               auto fim = high_resolution_clock::now();
               nanoseconds duracao = duration_cast<nanoseconds>(fim - inicio);
               totalTempoGuloso += duracao;
               CustoGuloso = solucao_guloso->getCustoTotal();


               // VND
               SolucaoServidores *solucao_vnd = new SolucaoServidores(problema);
               *solucao_vnd = *solucao_guloso;
               Melhoria *melhoria = new Melhoria(solucao_vnd, problema);

               inicio = high_resolution_clock::now();
               melhoria->vnd();
               fim = high_resolution_clock::now();
               duracao = duration_cast<nanoseconds>(fim - inicio);
               totalTempoVND += duracao;
               CustoVND = solucao_vnd->getCustoTotal();


               // ILS
               Metaheuristica *metaheuristica = new Metaheuristica(problema);

               inicio = high_resolution_clock::now();
               SolucaoServidores *solucao_meta = metaheuristica->ils(maxIter, maxIterILS);
               fim = high_resolution_clock::now();
               duracao = duration_cast<nanoseconds>(fim - inicio);
               totalTempoILS += duracao;
               totalCustoILS += solucao_meta->getCustoTotal();

               if (solucao_meta->getCustoTotal() < melhorCustoILS)
               {
                    melhorCustoILS = solucao_meta->getCustoTotal();
               }

               // Limpeza de objetos alocados
               delete problema;
               delete guloso;
               delete solucao_guloso;
               delete solucao_vnd;
               delete melhoria;
               delete metaheuristica;
               delete solucao_meta;
          }

          // Calcular médias dos tempos e custos
          nanoseconds mediaTempoGuloso = totalTempoGuloso / 10;
          nanoseconds mediaTempoVND = totalTempoVND / 10;
          nanoseconds mediaTempoILS = totalTempoILS / 10;
          double mediaCustoILS = totalCustoILS / 10;

          // Exibir resultados
          cout << "\tMédia do tempo de execução Guloso: " << mediaTempoGuloso.count() << " nanosegundos\n";
          cout << "\tMédia do tempo de execução VND: " << mediaTempoVND.count() << " nanosegundos\n";
          cout << "\tMédia do tempo de execução ILS: " << mediaTempoILS.count() << " nanosegundos\n\n";

          cout << "\tCusto Guloso: " << CustoGuloso << "\n";
          cout << "\tCusto VND: " << CustoVND << "\n";
          cout << "\tMédia do custo ILS: " << mediaCustoILS << "\n\n";
          cout << "\tMelhor custo ILS: " << melhorCustoILS << "\n";
     }
}
