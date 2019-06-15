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
*		2.00	rdms 08/06/2019	Expansão de funcionalidades
*
*	$ED Descri��o do m�dulo:
*		Este m�dulo implementa e gerencia o tabuleiro do jogo de gamão
*
***************************************************************************/

#include "LISTA.H"
#include "peca.h"

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
*	$FC Fun��o:	TBL Mover peças
*
*	Assertiva de entrada:
*		O espaço de dados passado deve possuir um tabuleiro alocado
*		Os paramêtros casaInicio e casaFim devem ser casas válidas do tabuleiro
*	Assertiva de saída:
*		Uma peça da casa inicial deve ser movida para a casa final
*
*	$ED Descri��o da fun��o:
*		Esta fun��o move peças.
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

/***********************************************************************
*
*	$FC Fun��o:	TBL Quantidade peças casa
*
*  Assertiva de entrada:
*		O espaço de dados passado deve possuir um tabuleiro alocado
*		O parâmetro casa deve ser uma casa válida do tabuleiro
*	Assertiva de saída:
*
*	$ED Descri��o da fun��o:
*		Esta fun��o retorna a quantidade de peças em uma casa.
*
*	$EP Par�metros:
*		$P	quantidade	 -	quantidade de peças na casa
*
*		$P	casa -	casa que terá as peças contabilizadas.
*
***********************************************************************/

   TBL_CondRet  TBL_QuantidadePecasCasa(int* quantidade, int casa);

/***********************************************************************
*
*	$FC Fun��o:	TBL Cor Peças casa
*
*	Assertiva de entrada:
*		O espaço de dados passado deve possuir um tabuleiro alocado
*		O parâmetro casa deve ser uma casa válida do tabuleiro
*	Assertiva de saída:
*
*	$ED Descri��o da fun��o:
*		Esta fun��o retorna o dono da casa escolhida.
*
*	$EP Par�metros:
*		$P	color	 -	cor das peças na casa
*
*		$P	casa -	casa de onde serão buscadas as peças.
*
***********************************************************************/

   TBL_CondRet  TBL_CorPecasCasa(PEC_color* color, int casa);

/***********************************************************************
*
*	$FC Fun��o:	TBL ObterCasasPorDono
*
*	Assertiva de entrada:
*		O espaço de dados passado deve possuir um tabuleiro alocado
*		Deve existir o vetor que será preenchido
*		Deve existir a variavel de retorno para o número de casas
*	Assertiva de saída:
*		O vetor será preenchido somente do inicio até o numero de casas 
*		encontrado, ou seja, o vetor serve como um buffer parcialmente 
*		preenchido
*
*	$ED Descri��o da fun��o:
*		Esta função preenche um vetor com as casas de uma cor
*
*	$EP Par�metros:
*		$P	color_a_procurar -	cor de procura
*
*		$P	vector -	Vetor de inteiros de tamanho 24 (tamanho maximo do tabuleiro)
*
*		$P	num_casa - Variavel de retorno do número de casas encontrado
*
***********************************************************************/

   TBL_CondRet TBL_ObterCasasPorDono(PEC_color color_a_procurar, int vector[24], int* num_casa);

/***********************************************************************
*
*	$FC Fun��o:	TBL RetirarPecaDoTabuleiro
*
*	Assertiva de entrada:
*		Deve existir a casa do tabuleiro, caso contrario sera retirado o ultimo
*		Deve existir pelo menos uma peça
*	Assertiva de saída:
*		Remove a peça de determinada casa
*
*	$EP Par�metros:
*		$P	*ret	 -	retorno da cor 
*
*		$P	casa -	casa de onde será removida a peças.
*
***********************************************************************/

   TBL_CondRet RetirarPecaDoTabuleiro(PEC_color* ret, int casa);

/***********************************************************************
*
*	$FC Fun��o:	TBL InserirPecaNoTabuleiro
*
*	Assertiva de entrada:
*		Deve existir a casa do tabuleiro, caso contrario sera inserida na ultima
*	Assertiva de saída:
*		Insere a peça em determinada casa
*
*	$EP Par�metros:
*		$P	*ret	 -	retorno da cor 
*
*		$P	casa -	casa de onde será inserida a peça.
*
***********************************************************************/

   TBL_CondRet TBL_InserirPecaNoTabuleiro(PEC_color color,int casa);