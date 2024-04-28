#include "../melhoria_servidor/melhoria.hpp"

SolucaoServidores *Melhoria::vnd()
{
    int estruturaAtual = 0;
    bool melhorou = false;

    while (estruturaAtual < QUANTIDADE_ESTRUTURAS_VIZINHANCA)
    {
        switch (estruturaAtual)
        {
        case 0:
            melhorou = this->insertion();
            break;
        case 7:
            melhorou = this->swap(1, 1);
            break;
        case 8:
            melhorou = this->remove();
            break;
        case 1:
            melhorou = this->reinsertion(1);
            break;
        case 2:
            melhorou = this->swap(2, 1);
            break;
        case 3:
            melhorou = this->swap(3, 2);
            break;
        case 4:
            melhorou = this->reinsertion(2);
            break;
        case 5:
            melhorou = this->swap(2, 2);
            break;
        case 6:
            melhorou = this->reinsertion(3);
            break;
        default:
            break;
        }

        if (melhorou)
        {
            estruturaAtual = 0;
        }
        else
        {
            estruturaAtual++;
        }
    }
    return solucaoAtual;
}