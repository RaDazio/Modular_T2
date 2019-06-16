#pragma once
/***************************************************************************
*
*	$MCD M�dulo de definição:	Módulo Tabuleiro
*	
*	Arquivo gerado:			TABULEIRO.h
*	Letras identificadoras:	TBL
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	   rdms - Rafael Damazio Monteiro da Silva
*               gmc - Gabriel Garcia Mascheroni Costa
*				    fo  - Felipe de Oliveira
*
*
*	$HA Hist�rico e evolu��o:
*		Vers�o  Autor	Data		Observa��es
*		1.00	gmc	03/05/2019	Inicio do desenvolvimento
*		1.00	gmc	05/05/2019	Finalização do desenvolvimento
*
*	$ED Descri��o do m�dulo:
*		Este m�dulo implementa a lista de peças finalizadas do jogo de gamão
*
***************************************************************************/
 

/***** Declara��es exportadas pelo m�dulo *****/


/***********************************************************************
*
*  $TC Tipo de dados: PF Condi��es de retorno
*
*
***********************************************************************/

   typedef enum {

         PF_OK ,
               /* Concluiu corretamente */

         PF_Vazia ,
               /* PF n�o cont�m elementos */

		 PF_Erro,
				/* N�o concluiu corretamente */

         PF_FaltouMemoria
               /* Faltou mem�ria ao tentar criar a estrutura*/

   } PF_CondRet ;

/***********************************************************************
*
*  $FC Fun��o: PF &Criar estrutura de pe�as Finalizadas

*  $ED Descri��o da fun��o
*     Cria uma estrutura para as pe�as Finalizadas do jogo de gam�o
*
*  $EP Par�metros
*	  pPF		- Ponteiro da estrutura de pe�as finalizadas passada por refer�ncia
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*
***********************************************************************/

   PF_CondRet PF_CriarPecasFinalizadas() ;

/***********************************************************************
*
*  $FC Fun��o: PF Adicionar uma peça finalizada a lista
*
*  $ED Descri��o da fun��o
*		Adiciona uma pe�a a lista de pe�as finalizadas
*
*  $EP Par�metros
*	  pPF			- A estrutura que ser� adicionada a pe�a
*
*
***********************************************************************/

   PF_CondRet PF_AdicionarPecaFinalizada(PEC_color cor) ;

/***********************************************************************
*
*  $FC Fun��o: PF Obter tamanho da lista de pe�as finalizadas
*
*  $ED Descri��o da fun��o
*		Obtem a quantidade de pe�as na lista
*
*  $EP Par�metros
*	  pPF			- A estrutura que se deseja saber o tamanho
*	  *tam			- Ponteiro de referencia para o tamanho da PF
*
*
***********************************************************************/

   PF_CondRet PF_ObterTamanhoPecasFinalizadas(PEC_color cor, int *tam) ;


/***********************************************************************
*
*  $FC Fun��o: PF Destruir PF
*
*  $ED Descri��o da fun��o
*		Destroi a lista de pe�as finalizadas
*
*  $EP Par�metros
*	  pPF		    - A lista que será destruída
*
***********************************************************************/

   PF_CondRet PF_DestruirPecasFinalizadas() ;

