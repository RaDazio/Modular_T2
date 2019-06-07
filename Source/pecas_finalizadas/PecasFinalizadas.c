/********************************************************************************************
*	$MCI Módulo de implementação:	Peças finalizadas
*
*	Arquivo gerado:			PecasFinalizadas.c
*	Letras identificadoras:	PF
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	rdms - Rafael Damazio Monteiro da Silva
*               gmc - Gabriel Garcia Mascheroni Costa
*				fo	 - Felipe de Oliveira
*
*	$HA Hist�rico e evolu��o:
*		Vers�o  Autor	Data		Observa��es
*		1.00	gmc	07/06/2019	Inicio do desenvolvimento
*
*******************************************************************************************/

#include "../interfaces/tabuleiro.h"
#include "../interfaces/LISTA.H"
#include "../interfaces/peca.h"

#include <stdio.h>
#include <stdlib.h>

#include "PecasFinalizadas.h"


/***********************************************************************
*
*  $TC Tipo de dados: PF Descritor da estrutura de pe�as finalizadas
*
*
***********************************************************************/

typedef struct PF_tagFinalizadas {

	LIS_tppLista PecasFinalizadas;
	/* Lista de Pe�as Finalizadas*/

	PEC_color cor;
	/* Cor das peças finalizadas */

} PF_tpFinalizadas ;

/*******************************************************/
/*****  Código das funções exportadas pelo módulo  *****/
/*******************************************************/

/***************************************************************************
*	$FC Fun��o:	PF Criar Peças Finalizadas
*  
**********************************************************************/

PF_CondRet PF_CriarPecasFinalizadas(PF_tppFinalizadas *pPF, PEC_color cor)
{

	*pPF = (PF_tppFinalizadas)malloc(sizeof(PF_tpFinalizadas));

	(*pPF)->PecasFinalizadas = LIS_CriarLista(PEC_DestruirPeca);
	(*pPF)->cor = cor;

	return PF_OK;
}

/***************************************************************************
*	$FC Fun��o:	PF Adicionar Peça finalizada
*  
**********************************************************************/

PF_CondRet PF_AdicionarPecaFinalizada(PF_tppFinalizadas pPF)
{
	PEC_color cor = pPF->cor;
	PecaHead newPeca;
	if(Pec_CriarPeca(cor, newPeca) != PEC_ok)
	{
		printf("Erro ao criar peca finalizada\n");
		return PF_Erro;
	}
	if(LIS_InserirElementoApos(pPF->PecasFinalizadas, newPeca) != LIS_CondRetOK)
	{
		printf("Erro ao inserir pe�a na lista (PF) \n");
		return PF_Erro;
	}

	return PF_OK;
}


/***************************************************************************
*	$FC Fun��o:	PF Obter Qtd Peças Finalizadas
*  
**********************************************************************/

PF_CondRet PF_ObterTamanhoPecasFinalizadas(PF_tppFinalizadas pPF, int *tam)
{
	if(tam == NULL)
		return PF_Erro;

	*tam = LIS_ObterTamanho(pPF->PecasFinalizadas);

	if(*tam == 0)
		return PF_Vazia;

	return PF_OK;
}

/***************************************************************************
*	$FC Fun��o:	PF Obter cor Peças finalizasas
*  
**********************************************************************/

PF_CondRet PF_ObterCorPecasFinalizadas(PF_tppFinalizadas pPF, PEC_color *cor)
{
	if(cor == NULL)
		return PF_Erro;

	*cor = pPF->cor;

	return PF_OK;
}

/***************************************************************************
*	$FC Fun��o:	PF Destruir Peças Finalizadas
*  
**********************************************************************/

PF_CondRet PF_DestruirPecasFinalizadas(PF_tppFinalizadas pPF)
{
	LIS_DestruirLista(pPF->PecasFinalizadas);
	free(pPF);
	return PF_OK;
}
