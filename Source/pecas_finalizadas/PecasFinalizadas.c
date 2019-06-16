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

#include "../interfaces/PecasFinalizadas.h"


/***********************************************************************
*
*  $TC Tipo de dados: PF Descritor da estrutura de pe�as finalizadas
*
*
***********************************************************************/

typedef struct PF_tagFinalizadas {

	LIS_tppLista PecasFinalizadasBrancas;
	/* Lista de Pe�as Finalizadas*/

	LIS_tppLista PecasFinalizadasPretas;
	/* Lista de Pe�as Finalizadas*/

} PF_tpFinalizadas ;

/* Tipo refer�ncia para a estrutura de pecas finalizadas */

typedef struct PF_tagFinalizadas * PF_tppFinalizadas;

static PF_tpFinalizadas * pecasFinalizadasSingleton = NULL ;

/*******************************************************/
/*****  Código das funções exportadas pelo módulo  *****/
/*******************************************************/

static void ExcluirPeca(void *pPeca)
{
	PecaHead pPecaTemp = (PecaHead) pPeca;
	PEC_DestruirPeca(pPecaTemp);
}

/***************************************************************************
*	$FC Fun��o:	PF Criar Peças Finalizadas
*  
**********************************************************************/

PF_CondRet PF_CriarPecasFinalizadas()
{

	pecasFinalizadasSingleton = (PF_tppFinalizadas)malloc(sizeof(PF_tpFinalizadas));

	(pecasFinalizadasSingleton)->PecasFinalizadasPretas = LIS_CriarLista(ExcluirPeca);
	(pecasFinalizadasSingleton)->PecasFinalizadasBrancas = LIS_CriarLista(ExcluirPeca);

	return PF_OK;
}

/***************************************************************************
*	$FC Fun��o:	PF Adicionar Peça finalizada
*  
**********************************************************************/

PF_CondRet PF_AdicionarPecaFinalizada(PEC_color cor)
{
	PecaHead newPeca = NULL;
	PEC_CondRet ret = PEC_CriaPeca(cor, &newPeca);
	if(ret != PEC_ok)
	{
		printf("Erro ao criar peca finalizada\n");
		return PF_Erro;
	}
	if (cor == COLOR_White)
	{
		if(LIS_InserirElementoApos(pecasFinalizadasSingleton->PecasFinalizadasBrancas, newPeca) != LIS_CondRetOK)
		{
			printf("Erro ao inserir pe�a na lista (PF) \n");
			return PF_Erro;
		}	
	}
	else if (cor == COLOR_Black)
	{
		if(LIS_InserirElementoApos(pecasFinalizadasSingleton->PecasFinalizadasPretas, newPeca) != LIS_CondRetOK)
		{
			printf("Erro ao inserir pe�a na lista (PF) \n");
			return PF_Erro;
		}
	}
	
	return PF_OK;
}


/***************************************************************************
*	$FC Fun��o:	PF Obter Qtd Peças Finalizadas
*  
**********************************************************************/

PF_CondRet PF_ObterTamanhoPecasFinalizadas(PEC_color cor, int *tam)
{
	if(tam == NULL)
		return PF_Erro;


	if (cor == COLOR_White)
	{
		*tam = LIS_ObterTamanho(pecasFinalizadasSingleton->PecasFinalizadasBrancas);
	}
	else if (cor == COLOR_Black)
	{
		*tam = LIS_ObterTamanho(pecasFinalizadasSingleton->PecasFinalizadasPretas);
	}

	return PF_OK;
}

/***************************************************************************
*	$FC Fun��o:	PF Destruir Peças Finalizadas
*  
**********************************************************************/

PF_CondRet PF_DestruirPecasFinalizadas()
{
	LIS_DestruirLista(pecasFinalizadasSingleton->PecasFinalizadasBrancas);
	LIS_DestruirLista(pecasFinalizadasSingleton->PecasFinalizadasPretas);
	free(pecasFinalizadasSingleton);
	return PF_OK;
}




