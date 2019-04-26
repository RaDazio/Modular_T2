/********************************************************************************************
*	$MCI Módulo de implementação:	Gerador de números aleatórios, baseado no número de faces
*
*	Arquivo gerado:			DADO.c
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
*******************************************************************************************/

#include "../interfaces/dado.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*******************************************************/
/*****  Código das funções exportadas pelo módulo  *****/
/*******************************************************/

/***********************************************************************
*	$FC Função:	DICE Roll dice
*
**********************************************************************/

DICE_CondRet DICE_RolarDado(int *dado, int numLados){
	int value;
	srand( ((unsigned int)time(NULL)) * rand() );
	value = rand() % numLados + 1;
	if(value > numLados || value < 1){
		return DICE_wrong;
	}	/* if */
	*dado = value;
	return DICE_ok;
}	/* Fim da função: DICE RolarDado */
