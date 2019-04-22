#pragma once
/***************************************************************************
*
*	$MCD M�dulo de defini��o:	M�dulo Dado
*	
*	Arquivo gerado:			DADO.h
*	Letras identificadoras:	DICE
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	rdms - Rafael Damazio Monteiro da Silva
*
*	$HA Hist�rico e evolu��o:
*		Vers�o  Autor	Data		Observa��es
*		1.00	rdms	20/04/2019	Inicio do desnvolvimento
*
*	$ED Descri��o do m�dulo:
*		Este m�dulo implementa a gera��o de n�meros aleat�rios (um dado) cujo
*		possui n lados.
*
***************************************************************************/

/***********************************************************************
*
*  $TC Tipo de dados:	DICE Condi��es de retorno
*
*
***********************************************************************/

typedef enum{
	DICE_ok = 0,
		/*	Valor correto, entre 1 e o n�mero de lados do dado */
	DICE_wrong = 1	
		/*	Valor invalido, menor que 1 ou maior que o numero de lados do dado */
} DICE_CondRet ;

/***********************************************************************
*
*	$FC Fun��o:	DICE Roll dice
*
*	$ED Descri��o da fun��o:
*		Esta fun��o gera um n�mero aleatorio e o guarda por referencia 
*		em um par�metro
*
*	$EP Par�metros:
*		$P	*dado	 -	Refer�ncia para uma variavel onde ser� salvo o 
*						valor
*		$P	numLados -	N�mero de lados do dado
*
***********************************************************************/

DICE_CondRet DICE_RolarDado(int *dado, int numLados);

