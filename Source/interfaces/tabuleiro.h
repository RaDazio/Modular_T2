#pragma once
/***************************************************************************
*
*	$MCD M�dulo de defini��o:	Módulo Tabuleiro
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
*		Este m�dulo implementa e gerencia o tabuleiro do jogo de gamão
*
***************************************************************************/

#include "../interfaces/LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: TBL Condi��es de retorno
*
*
***********************************************************************/

   typedef enum {

      TBL_notEnoughMemory = -1,
		   /* Faltou memoria */
      TBL_ok = 0,
         /* Executou corretamente */
      TBL_erro = 1,
         /* Ocorreu erro na execução */
      TBL_erroCriarPeca = 2,
         /* Ocorreu erro na criação da peça */
      TBL_erroGetCasas = 3,
         /* Ocorreu ao buscar casas */
      TBL_erroMovimentarPeca = 4
         /* Ocorreu erro na movimentação da peça */

   } TBL_CondRet ;


/******* TIPOS E FUN��ES EXPORTADOS DO M�DULO *****************************/



/***********************************************************************
*
*	$FC Fun��o:	TBL Cria tabuleiro
*
*	$ED Descri��o da fun��o:
*		Esta fun��o cria um tabuleiro.
*
*
***********************************************************************/


   TBL_CondRet TBL_CriarTabuleiro() ;


/***********************************************************************
*
*	$FC Fun��o:	TBL Destruir Tabuleiro
*
*	$ED Descri��o da fun��o:
*		Esta fun��o destrói um tabuleiro.
*
*
***********************************************************************/

   TBL_CondRet TBL_DestruirTabuleiro();

/***********************************************************************
*
*	$FC Fun��o:	TBL Obter casas
*
*	$ED Descri��o da fun��o:
*		Esta fun��o busca todas as casas do tabuleiro e as peças contidas nelas.
*
*	$EP Par�metros:
*		$P	tabuleiro	 -	tabuleiro de onde serão buscadas as casas
*
*		$P	casas	 -	Referencia de retorno das casas do tabuleiro
*
***********************************************************************/

	TBL_CondRet TBL_ObterCasas(LIS_tppLista* casas);

/***********************************************************************
*
*	$FC Fun��o:	TBL Destruir Tabuleiro
*
*	$ED Descri��o da fun��o:
*		Esta fun��o destrói um tabuleiro.
*
*	$EP Par�metros:
*		$P	tabuleiro	 -	tabuleiro onde serão movidas as peças
*
*		$P	casaInicio -	casa de onde a peça movida sairá.
*
*		$P	casaFim -	casa para onde a peça se moverá.
*
***********************************************************************/

   TBL_CondRet TBL_MoverPeca(int casaInicio, int casaFim ) ;




