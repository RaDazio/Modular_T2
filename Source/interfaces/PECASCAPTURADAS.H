#if ! defined(PECASCAPTURADAS_)
#define PCAP_EXT

#include "peca.h"

/***************************************************************************
*
*  $MCD Módulo de definição: Módulo peças capturadas
*
*  Arquivo gerado:              PECASCAPTURADAS.H
*  Letras identificadoras:      PCAP
*
*  Projeto: Disciplina INF 1301
*
*  Autores: gcmc - Gabriel Garcia Mascheroni Costa
            rdms - Rafael Damazio Monteiro da Silva
*           fo  - Felipe de Oliveira
*
*  $HA Histórico de evolução:
*     Versão       Autor          Data         Observações
*       1.00         fo       10/06/2019     Inú€io do desenvolvimento
*       2.00         svp      13/06/2019     Mudanca de approach para semelhante ao PecasFinalizadas
*       3.00         svp      15/06/2019     Ajustes nos valores de retorno
*
*  $ED Descrição do módulo
*     Este módulo implementa funções para operar listas de peças capturadas
*     O módulo eh capaz de trabalhar com n peças.
*     Ao iniciar a execução do programa não existe lista de peças.
*
***************************************************************************/
 
#if defined(PECASCAPTURADAS_OWN)
   #define PECASCAPTURADAS_EXT
#else
   #define PECASCAPTURADAS_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista de peças capturadas */

typedef struct PCAP_tagPecasCapturadas PCAP_tpPecasCapturadas;

/***********************************************************************
*
*  $TC Tipo de dados: PCAP Condições de retorno
*
*
***********************************************************************/

   typedef enum {

      PCAP_CondRetOK,
            /* Executou correto */

		PCAP_CondRetFaltouMemoria,
			   /* Faltou memória ao alocar dados */

		PCAP_CondRetErroInsercaoListaBranca,
			   /* Erro ao inserir peca na lista de pecas brancas capturadas */
      PCAP_CondRetErroInsercaoListaPreta,
            /* Erro ao inserir peca na lista de pecas pretas capturadas */

      PCAP_CondRetErroRemocaoPecaBranca,
            /* Erro ao remover peca na lista de pecas brancas capturadas */
      PCAP_CondRetErroRemocaoPecaPreta,
            /* Erro ao remover peca na lista de pecas pretas capturadas */   

      PCAP_CondRetPecasCapturadasJaExiste,
            /* Erro ao tentar criar peca capturadas com ponteiro de pecas capturadas ja existentes */ 

      PCAP_CondRetErroNaoExisteSingleton,
            /* Erro estrutura de pecas capturadas nao existe */

      PCAP_CondRetCorInexistente
            /* Cor fornecida nao eh preta nem branca */

   } PCAP_CondRet;


/***********************************************************************
*
*  $FC Função: PCAP Criar listas de peças capturadas
*
*  $ED Descrição da função
*     Cria uma estrutura contendo duas listas de pecas capturadas: uma lista para as brancas e outra para as pretas.
*
*
*  $FV Valor retornado
*     PCAP_CondRetOK
*     PCAP_CondRetFaltouMemoria
* AS: Caso não haja erro de memória, será criada a estrutura.
*
***********************************************************************/

   PCAP_CondRet PCAP_CriarListasPecasCapturadas();

/***********************************************************************
*
*  $FC Função: PCAP Inserir peca capturada
*
*  $ED Descrição da função
*     Insere uma peça na lista de peças capturadas da cor correspondente
*
*  $EP Parâmetros
*     $P cor - cor da peca a ser inserida na sua devida lista de pecas capturadas
*
*  $FV Valor retornado
*     PCAP_CondRetOK
*     PCAP_CondRetErroInsercaoListaBranca
*	   PCAP_CondRetErroInsercaoListaPreta
*     PCAP_CondRetErroNaoExisteSingleton
*   AE: Será passada uma variável do tipo PEC_color 
*   AS: Caso existe a estrutura e não ocorra erro de memória ao inserir a peça, uma peça com a cor passada terá sido adicionada à estrutura
*
***********************************************************************/

   PCAP_CondRet PCAP_InserirPecaCapturada(PEC_color cor);

/***********************************************************************
*
*  $FC Função: PCAP Remover peca capturada
*
*  $ED Descrição da função
*     Remove uma peça na lista de peças capturadas da cor correspondente.
*
*  $EP Parâmetros
*     $P cor - cor da peca a ser removida de sua devida lista de pecas capturadas
*
*  $FV Valor retornado
*     PCAP_CondRetOK
*     PCAP_CondRetErroRemocaoPecaBranca
*     PCAP_CondRetErroRemocaoPecaPreta
*     PCAP_CondRetErroNaoExisteSingleton
*     PCAP_CondRetCorInexistente
*   AE: Será passada uma variável do tipo PEC_color
*   AS: Caso a estrutura exista, na estrutura exista uma peça com essa cor e não ocorra erro ao remover, a peça será removida.
*
***********************************************************************/


   PCAP_CondRet PCAP_RemoverPecaCapturada(PEC_color cor);

/***********************************************************************
*
*  $FC Função: PCAP Obter quantidade pecas capturadas
*
*  $ED Descrição da função
*     Conta o numero de pecas capturadas da cor especificada
*
*  $EP Parâmetros
*     $P cor - cor das pecas que se deseja a contagem
*     $P qtd - ponteiro para um inteiro onde sera devolvido o numero de pecas contadas
*
*  $FV Valor retornado
*     PCAP_CondRetOK
*     PCAP_CondRetErroNaoExisteSingleton
*     PCAP_CondRetCorInexistente
* AE: Será passada um variável do tipo PEC_Color e um ponteiro para uma área de memória do tipo int que será passado por referência.
* AS: Caso exista a estrutura, a variável passada por referência terá seu valor alterado para a quantodade de pecas na estrutura da cor passada.
***********************************************************************/

   PCAP_CondRet PCAP_ObterQuantidadePecasCapturadas(PEC_color cor, int *qtd);

/***********************************************************************
*
*  $FC Função: PCAP Destruir pecas capturadas
*
*  $ED Descrição da função
*     Destroi as duas listas de pecas capturadas (lista de brancas e lista de pretas), assim
*     como a propria estutura que contem as listas
*
*  $FV Valor retornado
*    PCAP_CondRetOK
*    PCAP_CondRetErroNaoExisteSingleton
* AS: Caso exista a estrutura, a mesma será destruída.
***********************************************************************/

	PCAP_CondRet PCAP_DestruirPecasCapturadas();

#undef PCAP_EXT

/********** Fim do módulo de definição: Módulo peças capturadas **********/

#else
#endif
