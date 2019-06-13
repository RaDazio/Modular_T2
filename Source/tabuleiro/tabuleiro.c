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

static Tabuleiro * tabuleiroSingleton = NULL ;

static void ExcluirCasa(void* casa);
static void ExcluirPeca(void* pPeca);

/*******************************************************/
/*****  Código das funções exportadas pelo módulo  *****/
/*******************************************************/

/***************************************************************************
*	$FC Fun��o:	TBL Create Board
*  
**********************************************************************/

TBL_CondRet TBL_CriarTabuleiro()
{
	int i, addBranca = 0,addPreta = 0;
	LIS_tppLista casasTabuleiro[24]; 
	PecaHead pecasBrancas[15]; 
	PecaHead pecasPretas[15]; 

	if(tabuleiroSingleton != NULL){
		TBL_DestruirTabuleiro();
	}

	tabuleiroSingleton = (Tabuleiro *)malloc(sizeof(Tabuleiro));
	(tabuleiroSingleton)->Casas = LIS_CriarLista( ExcluirCasa );

	/* Criação das peças */
	for(i = 0; i < 15; i++)
	{	
		pecasBrancas[i] = NULL;
		if(PEC_CriaPeca(COLOR_White, &pecasBrancas[i]) != PEC_ok)
			return TBL_erro;

		pecasPretas[i] = NULL;
		if(PEC_CriaPeca(COLOR_Black, &pecasPretas[i]) != PEC_ok)
			return TBL_erro;
	}

	/* Criação das casas*/
	for(i = 0; i < 24; i++)
	{
		casasTabuleiro[i] = NULL;
		casasTabuleiro[i] = LIS_CriarLista(ExcluirPeca);
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
		LIS_InserirElementoApos((tabuleiroSingleton)->Casas, casasTabuleiro[i]);

	return TBL_ok;
}

/***************************************************************************
*	$FC Fun��o:	TBL Destruir Tabuleiro
*  
**********************************************************************/

TBL_CondRet TBL_DestruirTabuleiro ()
{
	if(tabuleiroSingleton == NULL){
		return TBL_tabNaoExiste;
	}
	
	LIS_DestruirLista(tabuleiroSingleton->Casas);
	free(tabuleiroSingleton);
	tabuleiroSingleton = NULL;
	return TBL_ok;
}

/***************************************************************************
*	$FC Fun��o:	TBL Obter Casas
*  
**********************************************************************/

TBL_CondRet TBL_ObterCasas(LIS_tppLista* casas)
{
	if(tabuleiroSingleton == NULL)
		return TBL_tabNaoExiste;

	*casas = tabuleiroSingleton->Casas;
	return TBL_ok;
}

/***************************************************************************
*	$FC Fun��o:	TBL Mover Peca
*  
***************************************************************************/

TBL_CondRet TBL_MoverPeca(int casaInicio, int casaFim ) 
{
	LIS_tppLista listaAux;
	PecaHead pecaAux1, pecaAux2;
	PEC_color color;

	if(tabuleiroSingleton == NULL){
		return TBL_tabNaoExiste;
	}

	// Pegar lista de peças na casa inicial
	IrInicioLista(tabuleiroSingleton->Casas);
	LIS_AvancarElementoCorrente(tabuleiroSingleton->Casas, casaInicio);
	listaAux = (LIS_tppLista)LIS_ObterValor(tabuleiroSingleton->Casas);

	// pegar uma peça da casa inicial
	pecaAux1 = (PecaHead)LIS_ObterValor(listaAux);

	// se a casa não estiver vazia, buscar cor da peça, senão dar throw
	if(pecaAux1 != NULL)
	{
		PEC_ObterCor(&color, pecaAux1);
	}
	else 
	{
		return TBL_erro;
	}

	// remover peça da casa inicial
	if(LIS_ExcluirElemento(listaAux) != LIS_CondRetOK)
		return TBL_erro;

	// Pegar lista de peças na casa final
	IrInicioLista(tabuleiroSingleton->Casas);
	LIS_AvancarElementoCorrente(tabuleiroSingleton->Casas, casaFim);
	listaAux = (LIS_tppLista)LIS_ObterValor(tabuleiroSingleton->Casas);

	// Criar nova peça
	pecaAux2 = NULL; 
	if(PEC_CriaPeca(color, &pecaAux2) != PEC_ok)
		return TBL_erro;

	// Adicionar nova peça na casa
	if(LIS_InserirElementoApos(listaAux, pecaAux2) != LIS_CondRetOK)
		return TBL_erro;

	return TBL_ok;
}

/***************************************************************************
*	$FC Fun��o:	TBL Quantidade de peças na casa
*	Retorna quantidade de peças em determinada casa
*  
**********************************************************************/

TBL_CondRet  TBL_QuantidadePecasCasa(int* quantidade, int casa)
{
	LIS_tppLista listaAux;

	IrInicioLista(tabuleiroSingleton->Casas);
	LIS_AvancarElementoCorrente(tabuleiroSingleton->Casas, casa);
	listaAux = (LIS_tppLista)LIS_ObterValor(tabuleiroSingleton->Casas);

	*quantidade = LIS_ObterTamanho(listaAux);

	return TBL_ok;
}

/***************************************************************************
*	$FC Fun��o:	TBL Cor peças na casa
*	Retorna a cor das peças de uma casa (dono)
*  
***************************************************************************/

TBL_CondRet  TBL_CorPecasCasa(PEC_color* color, int casa)
{
	LIS_tppLista listaAux;
	PecaHead pecaAux1;

	IrInicioLista(tabuleiroSingleton->Casas);
	LIS_AvancarElementoCorrente(tabuleiroSingleton->Casas, casa);
	listaAux = (LIS_tppLista)LIS_ObterValor(tabuleiroSingleton->Casas);

	// pegar uma peça da casa inicial
	pecaAux1 = (PecaHead)LIS_ObterValor(listaAux);

	// se a casa não estiver vazia, buscar cor da peça, senão dar throw
	if(pecaAux1 != NULL)
	{
		PEC_ObterCor(color, pecaAux1);
	}
	else 
	{
		*color = COLOR_Colorless;
		return TBL_ok;
	}

	return TBL_ok;
}

/***************************************************************************
*	$FC Fun��o:	TBL Cor peças na casa
*	Preenche um vetor com as casas de uma peça e retorna o número de casas
*	encontrada
*  
***************************************************************************/

TBL_CondRet TBL_ObterCasasPorDono(PEC_color color_a_procurar, int vector[24], int* num_casa){
	LIS_tppLista casas;
	TBL_CondRet tab_ret = TBL_ObterCasas(&casas);
	PEC_color color_aux;

	int aux_n_casas = 0;
	int aux_vector[24] = {0} ;	
	int idx;

	if( tab_ret != TBL_ok ) return TBL_erro;

	// Inicialização
	IrInicioLista(casas);

	//Contar o número de casas de cada cor e preenchendo o vetor auxilixar
	for(idx = 0; idx<24; idx++){
		tab_ret = TBL_CorPecasCasa(&color_aux,idx);
		if(tab_ret != TBL_erro){
			if(color_a_procurar == color_aux){
				aux_vector[aux_n_casas] = idx;
				aux_n_casas += 1;
			}
		}
	}
	for(idx=0 ; idx < aux_n_casas; idx++){
		vector[idx] = aux_vector[idx]+1;
	}	
	
	*num_casa = aux_n_casas;
	return TBL_ok;
}

/***************************************************************************
*	$FC Fun��o:	TBL RetirarPecaDoTabuleiro
*  
***************************************************************************/

TBL_CondRet RetirarPecaDoTabuleiro(PEC_color* ret, int casa){
	LIS_tppLista listaAux;
	PecaHead pecaAux1;
	PEC_color color;

	IrInicioLista(tabuleiroSingleton->Casas);
	LIS_AvancarElementoCorrente(tabuleiroSingleton->Casas, casa);
	listaAux = (LIS_tppLista)LIS_ObterValor(tabuleiroSingleton->Casas);

	pecaAux1 = (PecaHead)LIS_ObterValor(listaAux);

	if(pecaAux1 != NULL)
	{
		PEC_ObterCor(&color, pecaAux1);
	}
	else 
	{
		return TBL_erro;
	}

	if(LIS_ExcluirElemento(listaAux) != LIS_CondRetOK){
		return TBL_erro;
	}
	*ret = color;
	return TBL_ok;
}

/***************************************************************************
*	$FC Fun��o:	TBL InserirPecaNoTabuleiro
*  
***************************************************************************/

TBL_CondRet InserirPecaNoTabuleiro(PEC_color color,int casa){
	LIS_tppLista listaAux;
	PecaHead pecaAux1;

	IrInicioLista(tabuleiroSingleton->Casas);
	LIS_AvancarElementoCorrente(tabuleiroSingleton->Casas, casa);
	listaAux = (LIS_tppLista)LIS_ObterValor(tabuleiroSingleton->Casas);
	
	pecaAux1 = NULL; 
	if(PEC_CriaPeca(color, &pecaAux1) != PEC_ok)
		return TBL_erro;

	// Adicionar nova peça na casa
	if(LIS_InserirElementoApos(listaAux, pecaAux1) != LIS_CondRetOK)
		return TBL_erro;

	return TBL_ok;
}


void ExcluirCasa(void *pCasa)
{
	LIS_tppLista pCasaTemp = (LIS_tppLista) pCasa;
	LIS_DestruirLista(pCasaTemp);
}

void ExcluirPeca(void *pPeca)
{
	PecaHead* pPecaTemp = (PecaHead*) pPeca;
	PEC_DestruirPeca(pPecaTemp);
}

