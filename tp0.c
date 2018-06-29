#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp0.h"

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
  Protótipo: TestaExtensão(char* string1, char* string2)
  Função: Testa se a extensão do arquivo de saída passado como
  parâmetro
  Entrada: nome do arquivo de saída
  Saída: 1 se a extensão não estiver certa, 0 se estiver
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

int TestaExtensao(char* entrada)
{
    char *ext;

    ext = strrchr(entrada, '.');
    if(!ext || !strcmp(ext, ".txt"))
    {
        free(ext);
        return 1;
    }
    else
    {
        free(ext);
        return 0;
    }
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
  Protótipo: *LePGM(char* entrada)
  Função: Lê o arquivo de uma imagem e coloca as informações numa
  estrutura do tipo PGM*
  Entrada: Nome do arquivo para abrir tipo char*
  Saída: Estrutura PGM* preenchida
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

PGM *LePGM(char* entrada)
{
    FILE *f;
    PGM *imagem = malloc(sizeof(PGM));
    int l, c;

    if((f = fopen(entrada, "r")) == NULL)   /* testa se abriu arquivo com sucesso */
    {
        perror(entrada);
        exit(0);
    }
    else
    {
        /* pula o P2 que é padrão no início das imagens */
        fseek(f, 3, 0);

        /* pega coluna, linha e valor max (padrões do formato da iamgem) */
        fscanf(f, "%d %d %d", &imagem->c, &imagem->l, &imagem->maximo);

        /* aloca espaço para matriz */
        imagem->dados = malloc(imagem->l*sizeof(unsigned char*));

        for (l = 0; l < imagem->l; l++)
        {
            imagem->dados[l] = malloc(imagem->c*sizeof(int));
        }

        /* preenche matriz */
        while(!feof(f))
        {
            for(l =0; l <imagem->l;l++)
                for(c =0; c <imagem->c;c++)
                    fscanf(f, " %4d", &imagem->dados[l][c]);

        }
    } /* else */
    fclose(f);
    return imagem;
} /* Lê PGM */

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
  Protótipo: CorrelacaoCruzada(PGM *cena , PGM *obj , Ponto p)
  Função: Aplica o processor de correlação cruzada para as imagens
  em determinada estrutura Ponto
  Entrada: Duas estruturas do tipo PGM* e uma estrutura Ponto p
  Saída: Retorna o valor da correlação cruzada (int)
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

int CorrelacaoCruzada(PGM *cena, PGM *obj, Ponto p)
{
    int valor=0, i, j;

    for(i = 0; i < obj->l; i++)
        for(j = 0; j < obj->c; j++)
            valor += obj->dados[i][j]*cena->dados[p.y + i][p.x + j];

    return valor;
} /* Correlação Cruzada */

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
  Protótipo: AchaValor(int valores[], int n)
  Função: Procura o maior valor em um vetor de inteiros que contém
  os valores calculados pela função de correlação cruzada e devolve
  o índice da posição em que foi encontrado
  Entrada: Vetor de inteiros e seu tamanho, ambos do tipo int
  Saída: Índice do maior valor do vetor (int)
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

int AchaValor(int valores[], int n)
{
    int maior, i, idx;

    maior = valores[0];
    for(i =1; i <n; i++)
        if(valores[i] > maior)
        {
            maior = valores[i];
            idx = i;
        }

    return idx;
} /* Acha Valor */

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
  Protótipo: EscreveArquivo(Ponto p, char* entrada)
  Função: Escreve o ponto encontrado pela função da Janela Deslizante
  em um arquivo de saída
  Entrada: Uma estrutura Ponto e o nome do arquivo de saída (char*)
  Saída: retorna 0 se houve algum problema e 1 se escreveu o
  arquivo com sucesso
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

int EscreveArquivo(Ponto p, char* entrada)
{
    FILE *f;

    if(!TestaExtensao(entrada))
    {
        printf("Extensao invalida.\n");
        exit(0);
    }

    if((f = fopen(entrada, "w")) == NULL)   /* testa se criou com sucesso */
    {
        perror(entrada);
        exit(0);
    }
    else
    {
        fflush(f);
        fprintf(f, "%d %d", p.x, p.y);  /* escreve ponto no formato x y */
        fflush(f);
    }
    fclose(f);
    return 1;
} /* Escreve Arquivo */

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
  Protótipo: JanelaDeslizante(PGM *cena , PGM *obj)
  Função: Faz o processo de janela deslizante para encontrar o ponto
  na matriz onde a estrutura cena e a estrutura obj são iguais (maior valor)
  Entrada: Duas estruturas do tipo PGM*
  Saída: Uma estrutura tipo Ponto
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/


Ponto JanelaDeslizante(PGM *cena, PGM *obj)
{
    int i, x, y, tam = 0;
    Ponto p;
    Ponto *q;
    int *aux;

    for(y = 0; y <= (cena->l - obj->l); y++)        /* verificar quantidade de "janelas" para usar nos vetores */
        for(x = 0; x <= (cena->c - obj->c); x++)
            tam++;

    /* alocações de vetores auxiliares para os pontos e os valores */
    q = calloc(tam, sizeof(Ponto));
    aux = calloc(tam, sizeof(int));

    i = 0;
    for(y = 0; y <= (cena->l - obj->l); y++)
    {
        p.y = y;
        for(x = 0; x <= (cena->c - obj->c); x++, i++)
        {
            p.x = x;
            aux[i] = CorrelacaoCruzada(cena, obj, p);
            q[i] = p;
        }
    }

    i = AchaValor(aux, tam);
    p = q[i];

    free(q);
    free(aux);
    return p;
} /* Janela Deslizante */

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
  Protótipo: CorrelacaoModificada(PGM *cena, PGM *obj)
  Função: Imita o processo da JanelaDeslizante para encontrar o ponto
  na matriz onde a estrutura cena e a estrutura obj são iguais
  Entrada: Duas estruturas do tipo PGM*
  Saída: Uma estrutura tipo Ponto
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

Ponto CorrelacaoModificada(PGM *cena, PGM *obj)
{
    int x, y, aux;
    Ponto p;

    for(y = 0; y <= (cena->l - obj->l); y++)
    {
        p.y = y;
        for(x = 0; x <= (cena->c - obj->c); x++)
        {
            p.x = x;
            aux = Compara(cena, obj, p);
            if(aux == 0)
                return p;
        }
    }
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
  Protótipo: Compara(PGM* cena, PGM* obj, Ponto p)
  Função: compara duas matrizes de "mesmo tamanho"
  Entrada: Duas estruturas do tipo PGM* e uma estrutura Ponto
  Saída: 1 se não são iguais, 0 se são
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

int Compara(PGM* cena, PGM* obj, Ponto p)
{
    int i, j;

    for(i = 0; i < obj->l; i++)
        for(j = 0; j < obj->c; j++)
            if(obj->dados[i][j] == cena->dados[p.y + i][p.x + j])
                continue;
            else return 1;
    return 0;
}

