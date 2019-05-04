/********************************************************************************************
*	$MCI M�dulo de implementa��o:	Gerenciador de pe�as preto e brancas.
*
*	Arquivo gerado:			PECA.c
*	Letras identificadoras:	PEC
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	gcmc - Gabriel Garcia Mascheroni Costa
				rdms - Rafael Damazio Monteiro da Silva
*				fo	 - Felipe de Oliveira
*
*	$HA Hist�rico e evolu��o:
*		Vers�o  Autor	Data		Observa��es
*		1.00	rdms	21/04/2019	Inicio do desnvolvimento
*
*******************************************************************************************/

#include "../interfaces/peca.h"

#include <stdio.h>
#include <stdlib.h>

/***********************************************************************
*
*  $TC Tipo de dados: PEC Pe�a
*
*  $ED Descri��o do tipo
*		Descreve a organiza��o de uma pe�a
*
***********************************************************************/

typedef struct peca Peca;

struct peca{
	PEC_color color;
};

/*******************************************************/
/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
/*******************************************************/

/***********************************************************************
*	$FC Fun��o:	PEC Criar pe�a
*
**********************************************************************/

PEC_CondRet PEC_CriaPeca(PEC_color color, PecaHead* ret){
	*ret = (PecaHead)malloc(sizeof(PecaHead));
	if(*ret == NULL) return PEC_notEnoughMemory;
	if(color != COLOR_White && color != COLOR_Black) return PEC_colorNotExist;
	(*ret)->color = color;

	return PEC_ok;
}

/***********************************************************************
*	$FC Fun��o: PEC Obter Cor
*
**********************************************************************/

PEC_CondRet PEC_ObterCor(PEC_color *ret, PecaHead peca){
	if( peca == NULL ) return PEC_doNotExist;
	*ret = peca->color;
	return PEC_ok;
}

/***********************************************************************
*	$FC Fun��o:	PEC Destruir pe�a
*
**********************************************************************/

PEC_CondRet PEC_DestruirPeca(PecaHead peca){
	free(peca);
	peca = NULL;
	return PEC_ok;
}

