/*              TRABALHO PR�TICO 0
 *
 * Aluna: Ingrid Rosselis Sant'Ana da Cunha.
 * N�mero: 2016430936.
 * Turma: AEDS II - TN.
 * Objetivo: Implementar um "detector de objetos" usando duas imagens (da cena total e do objeto espec�fico.
 */

/* Estrutura da imagem */
typedef struct
{
    int c;                  // n�mero de colunas na imagem
    int l;                  // n�mero de linhas na imagem
    unsigned char maximo;   // valor m�ximo para cada pixel
    unsigned char **dados;  // vari�vel para armazenar os pixels da imagem (matriz)
} PGM;

/* Estrutura do ponto */
typedef struct
{
    int x;  //coluna
    int y;  //linha
} Ponto;


        /* FUN��ES */

int TesteExtensao(char* string1, char* string2);    //testa extens�o do arquivo

PGM *LePGM(char* entrada);  //l� arquivos de entrada e salva informa��es na estrutura PGM

int CorrelacaoCruzada(PGM *cena, PGM *obj, Ponto p);    //calcula processo de correla��o cruzada

Ponto JanelaDeslizante(PGM *cena, PGM *obj);    //aplica processo da janela deslizante

int AchaValor(int valores[], int n);    //acha o maior valor num vetor de inteiros

int EscreveArquivo(Ponto p, char* entrada);     //abre e esqcreve um arquivo de sa�da

Ponto CorrelacaoModificada(PGM *cena, PGM *obj);    //utiliza o processo modificado da correla��o cruzada

int Compara(PGM* cena, PGM* obj, Ponto p);      //compara n�meros de matrizes

