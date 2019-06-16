/********************************************************************************************
*	$MCI Módulo de implementação:	Gerenciador de peças preto e brancas.
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
*	$HA Histórico e evolução:
*		Versão  Autor	Data		Observações
*		1.00	rdms	21/04/2019	Inicio do desnvolvimento
*		2.00	rdms	05/05/2019	Modificação na assinatura da função de destruir uma peça
*
*******************************************************************************************/

#include "../interfaces/peca.h"

#include <stdio.h>
#include <stdlib.h>

/***********************************************************************
*
*  $TC Tipo de dados: PEC Peça
*
*  $ED Descrição do tipo
*		Descreve a organização de uma peça
*
***********************************************************************/

typedef struct peca Peca;

struct peca{
	PEC_color color;
};

/*******************************************************/
/*****  Código das funções exportadas pelo módulo  *****/
/*******************************************************/

/***********************************************************************
*	$FC Função:	PEC Criar peça
*
**********************************************************************/

PEC_CondRet PEC_CriaPeca(PEC_color color, PecaHead* ret){
	PecaHead aux;
	if (*ret != NULL) return PEC_alreadyExists;
	if(color != COLOR_White && color != COLOR_Black) return PEC_colorNotExist;
	aux = (PecaHead)malloc(sizeof(struct peca));
	if(aux == NULL) return PEC_notEnoughMemory;
	aux->color = color;
	*ret = aux;
	return PEC_ok;
}

/***********************************************************************
*	$FC Função: PEC Obter Cor
*
**********************************************************************/

PEC_CondRet PEC_ObterCor(PEC_color *ret, PecaHead peca){
	if( peca == NULL ) return PEC_doNotExist;
	*ret = peca->color;
	return PEC_ok;
}

/***********************************************************************
*	$FC Função:	PEC Destruir peça
*
**********************************************************************/

PEC_CondRet PEC_DestruirPeca(PecaHead peca){
	if (peca == NULL) return PEC_ok;
	free(peca);
	peca = NULL;
	return PEC_ok;
}



