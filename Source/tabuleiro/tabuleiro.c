/********************************************************************************************
*	$MCI Módulo de implementação:	Tabuleiro para Gamão
*
*	Arquivo gerado:			TABULEIRO.c
*	Letras identificadoras:	TBL
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
*		1.00	gmc	03/05/2019	Inicio do desenvolvimento
*		1.00	gmc	05/05/2019	Finalização do desenvolvimento
*
*******************************************************************************************/

#include "../interfaces/tabuleiro.h"
#include "../interfaces/LISTA.H"
#include "../interfaces/peca.h"

#include <stdio.h>
#include <stdlib.h>

/***********************************************************************
*
*  $TC Tipo de dados: TBL Tabuleiro
*
*  $ED Descri��o do tipo
*		Lista de lista com as casas e peças do tabuleiro
*
***********************************************************************/

typedef struct tabuleiro {

	LIS_tppLista Casas;


} Tabuleiro;


/*******************************************************/
/*****  Código das funções exportadas pelo módulo  *****/
/*******************************************************/

/***************************************************************************
*	$FC Fun��o:	TBL Create Board
*  
**********************************************************************/

TBL_CondRet TBL_CriarTabuleiro(TabuleiroHead * tabuleiro)
{
	int i, addBranca = 0,addPreta = 0;
	LIS_tppLista casasTabuleiro[24]; 
	PecaHead pecasBrancas[15]; 
	PecaHead pecasPretas[15]; 

	*tabuleiro = (TabuleiroHead)malloc(sizeof(Tabuleiro));
	(*tabuleiro)->Casas = LIS_CriarLista(LIS_DestruirLista);

	/* Criação das peças */
	for(i = 0; i < 15; i++)
	{	
		pecasBrancas[i] = NULL;
		if(Pec_CriarPeca(COLOR_White, &pecasBrancas[i]) != PEC_ok)
			return TBL_erroCriarPeca;

		pecasPretas[i] = NULL;
		if(Pec_CriarPeca(COLOR_Black, &pecasPretas[i]) != PEC_ok)
			return TBL_erroCriarPeca;
	}

	/* Criação das casas*/
	for(i = 0; i < 24; i++)
	{
		casasTabuleiro[i] = NULL;
		casasTabuleiro[i] = LIS_CriarLista(PEC_DestruirPeca);
	}

	// Preencher as casas com as posições iniciais das peças
	LIS_InserirElementoApos(casasTabuleiro[0], pecasBrancas[addBranca]); addBranca++;
	LIS_InserirElementoApos(casasTabuleiro[0], pecasBrancas[addBranca]); addBranca++;
	LIS_InserirElementoApos(casasTabuleiro[23], pecasPretas[addPreta]); addPreta++;
	LIS_InserirElementoApos(casasTabuleiro[23], pecasPretas[addPreta]); addPreta++;

	for(i = 0; i < 5; i++)
	{
		LIS_InserirElementoApos(casasTabuleiro[11], pecasBrancas[addBranca]); addBranca++;
		LIS_InserirElementoApos(casasTabuleiro[18], pecasBrancas[addBranca]); addBranca++;

		LIS_InserirElementoApos(casasTabuleiro[5], pecasPretas[addPreta]); addPreta++;
		LIS_InserirElementoApos(casasTabuleiro[12], pecasPretas[addPreta]); addPreta++;
	}

	for(i = 0; i < 3; i++)
	{
		LIS_InserirElementoApos(casasTabuleiro[16], pecasBrancas[addBranca]); addBranca++;
		LIS_InserirElementoApos(casasTabuleiro[7], pecasPretas[addPreta]); addPreta++;		
	}

	// Criar lista de casas no tabuleiro
	for(i = 0; i < 24; i++)
		LIS_InserirElementoApos((*tabuleiro)->Casas, casasTabuleiro[i]);

	return TBL_ok;
}

/***************************************************************************
*	$FC Fun��o:	TBL Destruir Tabuleiro
*  
**********************************************************************/

TBL_CondRet TBL_DestruirTabuleiro (TabuleiroHead tabuleiro)
{
	LIS_DestruirLista(tabuleiro->Casas);
	free(tabuleiro);
	tabuleiro = NULL;
	return TBL_ok;
}

/***************************************************************************
*	$FC Fun��o:	TBL Obter Casas
*  
**********************************************************************/

TBL_CondRet TBL_ObterCasas(LIS_tppLista *casas, TabuleiroHead tabuleiro)
{
	*casas = tabuleiro->Casas;
	return TBL_ok;
}

/***************************************************************************
*	$FC Fun��o:	TBL Mover Peca
*  
**********************************************************************/

TBL_CondRet TBL_MoverPeca(TabuleiroHead tabuleiro, int casaInicio, int casaFim ) 
{
	LIS_tppLista listaAux;
	PecaHead pecaAux1, pecaAux2;
	PEC_color color;

	// Pegar lista de peças na casa inicial
	IrInicioLista(tabuleiro->Casas);
	LIS_AvancarElementoCorrente(tabuleiro->Casas, casaInicio);
	listaAux = (LIS_tppLista)LIS_ObterValor(tabuleiro->Casas);

	// pegar uma peça da casa inicial
	pecaAux1 = (PecaHead)LIS_ObterValor(listaAux);

	// se a casa não estiver vazia, buscar cor da peça, senão dar throw
	if(pecaAux1 != NULL)
	{
		Pec_ObterCor(&color, pecaAux1);
	}
	else 
	{
		return TBL_erroMovimentarPeca;
	}

	// remover peça da casa inicial
	if(LIS_ExcluirElemento(listaAux) != LIS_CondRetOK)
		return TBL_erroMovimentarPeca;

	// Pegar lista de peças na casa final
	IrInicioLista(tabuleiro->Casas);
	LIS_AvancarElementoCorrente(tabuleiro->Casas, casaFim);
	listaAux = (LIS_tppLista)LIS_ObterValor(tabuleiro->Casas);

	// Criar nova peça
	if(Pec_CriarPeca(color, &pecaAux2) != PEC_ok)
		return TBL_erroCriarPeca;

	// Adicionar nova peça na casa
	if(LIS_InserirElementoApos(listaAux, pecaAux2) != LIS_CondRetOK)
		return TBL_erroMovimentarPeca;

	return TBL_ok;
}


