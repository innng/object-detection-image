/*              TRABALHO PRÁTICO 0
 *
 * Aluna: Ingrid Rosselis Sant'Ana da Cunha.
 * Número: 2016430936.
 * Turma: AEDS II - TN.
 * Objetivo: Implementar um "detector de objetos" usando duas imagens (da cena total e do objeto específico.
 */

/* Estrutura da imagem */
typedef struct
{
    int c;                  // número de colunas na imagem
    int l;                  // número de linhas na imagem
    unsigned char maximo;   // valor máximo para cada pixel
    unsigned char **dados;  // variável para armazenar os pixels da imagem (matriz)
} PGM;

/* Estrutura do ponto */
typedef struct
{
    int x;  //coluna
    int y;  //linha
} Ponto;


        /* FUNÇÕES */

int TesteExtensao(char* string1, char* string2);    //testa extensão do arquivo

PGM *LePGM(char* entrada);  //lê arquivos de entrada e salva informações na estrutura PGM

int CorrelacaoCruzada(PGM *cena, PGM *obj, Ponto p);    //calcula processo de correlação cruzada

Ponto JanelaDeslizante(PGM *cena, PGM *obj);    //aplica processo da janela deslizante

int AchaValor(int valores[], int n);    //acha o maior valor num vetor de inteiros

int EscreveArquivo(Ponto p, char* entrada);     //abre e esqcreve um arquivo de saída

Ponto CorrelacaoModificada(PGM *cena, PGM *obj);    //utiliza o processo modificado da correlação cruzada

int Compara(PGM* cena, PGM* obj, Ponto p);      //compara números de matrizes

