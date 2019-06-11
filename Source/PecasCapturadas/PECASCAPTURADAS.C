
/***************************************************************************
*  $MCI Módulo de implementação: Módulo peças capturadas
*
*  Arquivo gerado:              PECASCAPTURADAS.C
*  Letras identificadoras:      PCAP
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	gcmc - Gabriel Garcia Mascheroni Costa
				rdms - Rafael Damazio Monteiro da Silva
*				fo	 - Felipe de Oliveira
*
*  $HA Histórico de evolução:
*     Versão       Autor          Data         Observações
*       1.00   		fo   		10/06/2019 		Inú€io do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define PECASCAPTURADAS_OWN
#include "PECASCAPTURADAS.H"
#undef PECASCAPTURADAS_OWN
#include "PECA.h"
#include "LISTA.h"


/***********************************************************************
*
*  $TC Tipo de dados: PCAP Descritor da peça capturadas
*
*
***********************************************************************/

typedef struct PCAP_tagPecasCapturadas {

	LIS_tppLista listaPecasBrancas;
	LIS_tppLista listaPecasPretas;
	/* Lista de peças capturadas */

} PCAP_tpPecasCapturadas;

static PCAP_tpPecasCapturadas * PCAPSingleton = NULL ;

/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapsuladas no módulo *****/

void RemoverPeca(void *pPeca);

/*****  Código das funçvões exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PCAP Criar lista de peças capturadas
* 
****/
PCAP_tpCondRet PCAP_CriarListaPecasCapturadas()
{

	PCAPSingleton = (PCAP_tpPecasCapturadas *) malloc(sizeof(PCAP_tpPecasCapturadas));
	if(PCAPSingleton == NULL)
	{
		return PCAP_CondRetFaltouMemoria ;
	} /* if */

	PCAPSingleton->listaPecasBrancas = LIS_CriarLista(RemoverPeca);
	PCAPSingleton->listaPecasPretas = LIS_CriarLista(RemoverPeca);

	return PCAP_CondRetOK ;

} /* Fim função: PCAP Criar lista de peças capturadas */

/***************************************************************************
*
*  Função: PCAP Inserir peça Branca
*  
****/
PCAP_tpCondRet PCAP_InserirPecaCapBranca(PecaHead pPeca)
{
	if(PCAPSingleton== NULL) 
	{
		return PCAP_CondRetListaPecasCapturadasNaoExiste;
	} /* if */

    PEC_color CorPecaTemp;
    PEC_ObterCor (&CorPecaTemp,pPeca);		
	if(CorPecaTemp!=COLOR_White)
		return PCAP_CondRetCorErrada;

	LIS_InserirElementoAntes(PCAPSingleton->listaPecas, pPeca);
	
	return PCAP_CondRetOK;

} /* Fim função: PCAP Inserir peça */
/***************************************************************************
*
*  Função: PCAP Inserir peça Preta
*  
****/
PCAP_tpCondRet PCAP_InserirPecaCapPreta(PecaHead pPeca)
{
	if(PCAPSingleton== NULL) 
	{
		return PCAP_CondRetListaPecasCapturadasNaoExiste;
	} /* if */

    PEC_color CorPecaTemp;
    PEC_ObterCor (&CorPecaTemp,pPeca);		
	if(CorPecaTemp!=COLOR_Black)
		return PCAP_CondRetCorErrada;
	
	LIS_InserirElementoAntes(PCAPSingleton->listaPecas, pPeca);
	
	return PCAP_CondRetOK;

} /* Fim função: PCAP Inserir peça */
/***************************************************************************
*
*  Função: PCAP Remover peça
*  
****/
PCAP_tpCondRet PCAP_RemoverPeca(PEC_color CorPeca, PecaHead *pPeca)
{
	PEC_color CorPecaTemp;
	PecaHead pPecaTemp;

	if(PCAPSingleton == NULL)
	{
		return PCAP_CondRetListaPecasCapturadasNaoExiste;
	} /*if*/

	IrInicioLista(PCAPSingleton->listaPecas);

	do
	{
		pPecaTemp = (PecaHead) LIS_ObterValor(PCAPSingleton->listaPecas);

		PEC_ObterCor( &CorPecaTemp,pPecaTemp);

		if(CorPecaTemp == CorPeca)
		{
			*pPeca = pPecaTemp;
			LIS_ExcluirElemento(PCAPSingleton->listaPecas);

			return PCAP_CondRetOK;
		} /* if */
	} while(LIS_AvancarElementoCorrente(PCAPSingleton->listaPecas, 1) == LIS_CondRetOK); /* do */

	return PCAP_CondRetPecaNaoExiste;

} /* Fim função: PCAP Remover peça */

/***************************************************************************
*
*  Função: PCAP Conta peças brancas
*  
****/
PCAP_tpCondRet PCAP_ObterPecasCapBrancas( int *pContagem)
{
	PEC_color CorPecaTemp;
	PecaHead pPecaTemp;

	if(PCAPSingleton == NULL) 
	{
		return PCAP_CondRetListaPecasCapturadasNaoExiste;
	} /* if */

	*pContagem = 0;

	IrInicioLista(PCAPSingleton->listaPecas);

	if(LIS_ObterValor(PCAPSingleton->listaPecas) != NULL)
	{
		do
		{
			pPecaTemp = (PecaHead) LIS_ObterValor(PCAPSingleton->listaPecas);
			
			PEC_ObterCor(&CorPecaTemp,pPecaTemp);

			if(CorPecaTemp == COLOR_White)
			{
				(*pContagem)++;
			} /* if */
		} while(LIS_AvancarElementoCorrente(PCAPSingleton->listaPecas, 1) == LIS_CondRetOK); /* do */
	} /* if */

	return PCAP_CondRetOK ;

} /* Fim função: PCAP Conta peças */

/***************************************************************************
*
*  Função: PCAP Conta peças pretas
*  
****/
PCAP_tpCondRet PCAP_ObterPecasCapPretas( int *pContagem)
{
	PEC_color CorPecaTemp;
	PecaHead pPecaTemp;

	if(PCAPSingleton == NULL) 
	{
		return PCAP_CondRetListaPecasCapturadasNaoExiste;
	} /* if */

	*pContagem = 0;

	IrInicioLista(PCAPSingleton->listaPecas);

	if(LIS_ObterValor(PCAPSingleton->listaPecas) != NULL)
	{
		do
		{
			pPecaTemp = (PecaHead) LIS_ObterValor(PCAPSingleton->listaPecas);
			
			PEC_ObterCor(&CorPecaTemp,pPecaTemp);

			if(CorPecaTemp == COLOR_Black)
			{
				(*pContagem)++;
			} /* if */
		} while(LIS_AvancarElementoCorrente(PCAPSingleton->listaPecas, 1) == LIS_CondRetOK); /* do */
	} /* if */

	return PCAP_CondRetOK ;

}
/***************************************************************************
*
*  Função: PCAP Destruir lista de peças capturadas
*  
****/
PCAP_tpCondRet PCAP_DestruirListaPecasCapturadas()
{
	PecaHead pPecaTemp;

	if(PCAPSingleton == NULL) 
	{
		return PCAP_CondRetListaPecasCapturadasNaoExiste;
	} /* if */

	IrInicioLista(PCAPSingleton->listaPecas);

	pPecaTemp = (PecaHead) LIS_ObterValor(PCAPSingleton->listaPecas);
	
	while(pPecaTemp != NULL)
	{
		PEC_DestruirPeca(&pPecaTemp);
		
		if(LIS_AvancarElementoCorrente(PCAPSingleton->listaPecas, 1) != PEC_ok)
		{
			break;
		} /* if */

		pPecaTemp = (PecaHead) LIS_ObterValor(PCAPSingleton->listaPecas);
	} /* while */

	free(PCAPSingleton);
	PCAPSingleton = NULL;

	return PCAP_CondRetOK ;

} /* Fim função: PCAP Destruir lista de peças capturadas */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: Remove peça
*
*  $ED Descrição da função
*     Função chamada ao remover uma peça da lista.
*
***********************************************************************/
void RemoverPeca(void* pPeca)
{
	PecaHead* pPecaTemp = (PecaHead*) pPeca;
	PEC_DestruirPeca(pPecaTemp);
}

/********** Fim do módulo de implementação: Módulo peças capturadas **********/