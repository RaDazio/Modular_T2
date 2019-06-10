#if ! defined(PECASCAPTURADAS_)
#define BAR_EXT

#include "PECA.H"

/***************************************************************************
*
*  $MCD Módulo de definição: Módulo peças capturadas
*
*  Arquivo gerado:              PECASCAPTURADAS.H
*  Letras identificadoras:      BAR
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

typedef struct BAR_tagPecasCapturadas BAR_tpPecasCapturadas;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Condições de retorno
*
*
***********************************************************************/

   typedef enum {

         BAR_CondRetOK,
               /* Executou correto */

		 BAR_CondRetListaPecasCapturadasNaoExiste,
			   /* Lista de peças capturadas não existe */

		 BAR_CondRetPecaNaoExiste,
			   /* Peça não existe na lista de peças capturadas */

         BAR_CondRetFaltouMemoria
               /* Faltou memória ao alocar dados */

   } BAR_tpCondRet;


/***********************************************************************
*
*  $FC Função: BAR Criar lista de peças capturadas
*
*  $ED Descrição da função
*     Cria uma nova lista de peças capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças capturadas a ser criada. Passado por referência.
*
*  $FV Valor retornado
*     BAR_CondRetOK
*     BAR_CondRetFaltouMemoria
*
***********************************************************************/

   BAR_tpCondRet BAR_CriarListaPecasCapturadas();

/***********************************************************************
*
*  $FC Função: BAR Inserir peça
*
*  $ED Descrição da função
*     Insere uma peça na lista de peças capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças capturadas a ser utilizada.
*     $P pPeca - ponteiro para a peça a ser utilizada.
*
*  $FV Valor retornado
*     BAR_CondRetOK
*     BAR_CondRetListaPecasCapturadasNaoExiste
*	  BAR_CondRetFaltouMemoria
*
***********************************************************************/

   BAR_tpCondRet BAR_InserirPeca( PecaHead pPeca);

/***********************************************************************
*
*  $FC Função: BAR Remover peça
*
*  $ED Descrição da função
*     Removee uma peça na lista de peças capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças capturadas a ser utilizada.
*     $P pPeca - ponteiro para a peça a ser utilizada.
*
*  $FV Valor retornado
*     BAR_CondRetOK
*     BAR_CondRetListaPecasCapturadasNaoExiste
*     BAR_CondRetPecaNaoExiste
*	  BAR_CondRetFaltouMemoria
*
***********************************************************************/

   BAR_tpCondRet BAR_RemoverPeca( PEC_color CorPeca, PecaHead *pPeca);

/***********************************************************************
*
*  $FC Função: BAR Contar peças
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
*     BAR_CondRetOK
*	  BAR_CondRetListaPecasCapturadasNaoExiste
*
***********************************************************************/

   BAR_tpCondRet BAR_ContarPecas( PEC_color CorPeca, int *pContagem);

/***********************************************************************
*
*  $FC Função: BAR Destruir lista de peças capturadas
*
*  $ED Descrição da função
*     Destrói a lista de peças capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças capturadas a ser utilizada. Passado por referência.
*
*  $FV Valor retornado
*     BAR_CondRetOK
*	  BAR_CondRetListaPecasCapturadasNaoExiste
*
***********************************************************************/

   BAR_tpCondRet BAR_DestruirListaPecasCapturadas();

#undef BAR_EXT

/********** Fim do módulo de definição: Módulo peças capturadas **********/

#else
#endif