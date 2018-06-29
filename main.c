#include <stdio.h>
#include <stdlib.h>
#include "tp0.h"

int main(int argc, char* argv[])
{
    PGM *cena, *obj;
    Ponto p;
    int parametro;

    if (argc != 4 && argc != 5)  /*testa o número de parâmetros passados pelo cmd */
    {
       puts("Numero incorreto de parametros.");
       return 1;
    }
    else
    {
        parametro = atoi(argv[4]);
        if(parametro != 1 && parametro != 0)
        {
            puts("Quinto parametro incorreto (nada, 0 ou 1 apenas).\n");
            return 1;
        }
        cena = LePGM(argv[1]);
        obj = LePGM(argv[2]);
        if(parametro == 1)
            p = CorrelacaoModificada(cena, obj);
        else
            p = JanelaDeslizante(cena, obj);

        /* avisa se gravou o arquivo */
        if(EscreveArquivo(p, argv[3]) == 1)
            puts("\nArquivo gravado com sucesso!");

    } /* else */
    free(cena);
    free(obj);
    return 0;
} /* main */
