#ifndef GULOSO_SERVIDORES_HPP
#define GULOSO_SERVIDORES_HPP

#include "../problema/problema_servidor.hpp"
#include "../solucao/solucao_servidores.hpp"

using namespace std;

class Guloso
{
private:
    ProblemaServidor *problemaServidor;

public:
    Guloso(ProblemaServidor *problema);
    SolucaoServidores *executar();
};

#endif