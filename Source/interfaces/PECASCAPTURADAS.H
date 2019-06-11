#if ! defined(PECASCAPTURADAS_)
#define PCAP_EXT

#include "PECA.H"

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
*
*  $ED Descrição do módulo
*     Este módulo implementa funções para operar uma lista de peças capturadas
*     O módulo Ecapaz de trabalhar com n peças.
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

		 PCAP_CondRetListaPecasCapturadasNaoExiste,
			   /* Lista de peças capturadas não existe */

		 PCAP_CondRetPecaNaoExiste,
			   /* Peça não existe na lista de peças capturadas */

         PCAP_CondRetFaltouMemoria,
               /* Faltou memória ao alocar dados */
         PCAP_CondRetCorErrada

   } PCAP_tpCondRet;


/***********************************************************************
*
*  $FC Função: PCAP Criar lista de peças capturadas
*
*  $ED Descrição da função
*     Cria uma nova lista de peças capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças capturadas a ser criada. Passado por referência.
*
*  $FV Valor retornado
*     PCAP_CondRetOK
*     PCAP_CondRetFaltouMemoria
*
***********************************************************************/

   PCAP_tpCondRet PCAP_CriarListaPecasCapturadas();

/***********************************************************************
*
*  $FC Função: PCAP Inserir peça Branca
*
*  $ED Descrição da função
*     Insere uma peça na lista de peças capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças capturadas a ser utilizada.
*     $P pPeca - ponteiro para a peça a ser utilizada.
*
*  $FV Valor retornado
*     PCAP_CondRetOK
*     PCAP_CondRetListaPecasCapturadasNaoExiste
*	  PCAP_CondRetFaltouMemoria
*
***********************************************************************/

 PCAP_tpCondRet PCAP_InserirPecaCapBranca(PecaHead pPeca);

/***********************************************************************
*
*  $FC Função: PCAP Remover peça Preta
*
*  $ED Descrição da função
*     Removee uma peça na lista de peças capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças capturadas a ser utilizada.
*     $P pPeca - ponteiro para a peça a ser utilizada.
*
*  $FV Valor retornado
*     PCAP_CondRetOK
*     PCAP_CondRetListaPecasCapturadasNaoExiste
*     PCAP_CondRetPecaNaoExiste
*    PCAP_CondRetFaltouMemoria
*
***********************************************************************/


 PCAP_tpCondRet PCAP_InserirPecaCapPreta(PecaHead pPeca);

/***********************************************************************
*
*  $FC Função: PCAP Remover peça 
*
*  $ED Descrição da função
*     Removee uma peça na lista de peças capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças capturadas a ser utilizada.
*     $P pPeca - ponteiro para a peça a ser utilizada.
*
*  $FV Valor retornado
*     PCAP_CondRetOK
*     PCAP_CondRetListaPecasCapturadasNaoExiste
*     PCAP_CondRetPecaNaoExiste
*    PCAP_CondRetFaltouMemoria*/

   PCAP_tpCondRet PCAP_RemoverPeca( PEC_color CorPeca, PecaHead *pPeca);

/***********************************************************************
*
*  $FC Função: PCAP Obter peças Brancas
*
*  $ED Descrição da função
*     Conta as peças de uma determinada cor na lista de peças capturadas
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças capturadas a ser utilizada.
*     $P CorPeca - cor das peças a serem contadas.
*     $P pContagem - ponteiro para o inteiro onde serEarmazenado o número de peças.
*
*  $FV Valor retornado
*     PCAP_CondRetOK
*	  PCAP_CondRetListaPecasCapturadasNaoExiste
*
***********************************************************************/

   PCAP_tpCondRet PCAP_ObterPecasCapBrancas( int *pContagem);

/***********************************************************************
*
*  $FC Função: PCAP Obter peças Pretas
*
*  $ED Descrição da função
*     Conta as peças de uma determinada cor na lista de peças capturadas
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças capturadas a ser utilizada.
*     $P CorPeca - cor das peças a serem contadas.
*     $P pContagem - ponteiro para o inteiro onde serEarmazenado o número de peças.
*
*  $FV Valor retornado
*     PCAP_CondRetOK
*    PCAP_CondRetListaPecasCapturadasNaoExiste
*
***********************************************************************/

   PCAP_tpCondRet PCAP_ObterPecasCapPretas( int *pContagem);
*
*  $FC Função: PCAP Destruir lista de peças capturadas
*
*  $ED Descrição da função
*     Destrói a lista de peças capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças capturadas a ser utilizada. Passado por referência.
*
*  $FV Valor retornado
*     PCAP_CondRetOK
*	  PCAP_CondRetListaPecasCapturadasNaoExiste
*
**********************************************************************

   PCAP_tpCondRet PCAP_DestruirListaPecasCapturadas();

#undef PCAP_EXT

/********** Fim do módulo de definição: Módulo peças capturadas **********/

#else
#endif