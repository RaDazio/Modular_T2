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
      TBL_tabNaoExiste = 2
		/* Tabuleiro Nao existe */
   } TBL_CondRet ;


/******* TIPOS E FUN��ES EXPORTADOS DO M�DULO *****************************/



/***********************************************************************
*
*	$FC Fun��o:	TBL Cria tabuleiro
*
*	$ED Descri��o da fun��o:
*		Esta fun��o cria um tabuleiro.
*	Assertiva de entrada:
*		Deve existir um ponteiro para qual o tabuleiro criado será retornado por
*		referência.
*	Assertiva de saída:
*		O tabuleiro criado será salvo no ponteiro passado por referência, ele terá uma lista de 24 casas com as peças iniciais posicionadas.
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
*	Assertiva de entrada:
*		O espaço de dados passado deve possuir um tabuleiro alocado
*	Assertiva de Saída
*		Após a destruição do tabuleiro, o ponteiro passado terá o valor de NULL.
*
***********************************************************************/

   TBL_CondRet TBL_DestruirTabuleiro();

/***********************************************************************
*
*	$FC Fun��o:	TBL Obter casas
*
*	Assertiva de entrada:
*		Deve existir uma área de memória do tipo LIS_tppLista para qual
*		será retornada a lista de casas.
*	Assertiva de saída:
*		Caso não exista o tabuleiro a função não retornará a lista de casas.
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
*	Assertiva de entrada:
*		O espaço de dados passado deve possuir um tabuleiro alocado
*		Os paramêtros casaInicio e casaFim devem ser casas válidas do tabuleiro
*	Assertiva de saída:
*		Uma peça da casa inicial deve ser movida para a casa final
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




