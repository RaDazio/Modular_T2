#pragma once
/***************************************************************************
*
*	$MCD Módulo de definição:	Módulo Dado
*	
*	Arquivo gerado:			DADO.h
*	Letras identificadoras:	DICE
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	rdms - Rafael Damazio Monteiro da Silva
*
*	$HA Histórico e evolução:
*		Versão  Autor	Data		Observações
*		1.00	rdms	20/04/2019	Inicio do desnvolvimento
*
*	$ED Descrição do módulo:
*		Este módulo implementa a geração de números aleatórios (um dado) cujo
*		possui n lados.
*
***************************************************************************/

/***********************************************************************
*
*  $TC Tipo de dados:	DICE Condições de retorno
*
*
***********************************************************************/

typedef enum{
	DICE_ok = 0,
		/*	Valor correto, entre 1 e o número de lados do dado */
	DICE_wrong = 1	
		/*	Valor invalido, menor que 1 ou maior que o numero de lados do dado */
} DICE_CondRet ;

/***********************************************************************
*
*	$FC Função:	DICE Roll dice
*
*	$ED Descrição da função:
*		Esta função gera um número aleatorio e o guarda por referencia 
*		em um parâmetro
*
*	$EP Parâmetros:
*		$P	*dado	 -	Referência para uma variavel onde será salvo o 
*						valor
*		$P	numLados -	Número de lados do dado
*
***********************************************************************/

DICE_CondRet DICE_RolarDado(int *dado, int numLados);

