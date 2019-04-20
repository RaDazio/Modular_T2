/********************************************************************************************
*	$MCI M�dulo de implementa��o:	Gerador de n�meros aleat�rios, baseado no n�mero de faces
*
*	Arquivo gerado:			DADO.c
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
*******************************************************************************************/

#include "../interfaces/dado.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*******************************************************/
/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
/*******************************************************/

/***********************************************************************
*	$FC Fun��o:	DICE Roll dice
*
**********************************************************************/

DICE_CondRet roll_dice(int *dice, int numSides){
	int value;
	srand( ((unsigned int)time(NULL)) * rand() );
	value = rand() % numSides + 1;
	if(value > numSides || value < 1){
		return DICE_wrong;
	}
	*dice = value;
	return DICE_ok;
}
