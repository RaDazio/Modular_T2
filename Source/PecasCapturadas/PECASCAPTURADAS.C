/***************************************************************************
*  $MCI Módulo de implementação: Módulo peças capturadas
*
*  Arquivo gerado:              PECASCAPTURADAS.C
*  Letras identificadoras:      BAR
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
#include "..\interfaces\PECASCAPTURADAS.H"
#undef PECASCAPTURADAS_OWN
#include "..\interfaces\PECA.h"
#include "..\interfaces\LISTA.h"


/***********************************************************************
*
*  $TC Tipo de dados: BAR Descritor da peça capturadas
*
*
***********************************************************************/

typedef struct BAR_tagPecasCapturadas {

	LIS_tppLista listaPecas;
	/* Lista de peças capturadas */

} BAR_tpPecasCapturadas;

/* Tipo refer�ncia para a estrutura de pecas finalizadas */

typedef struct PF_tagFinalizadas * PF_tppFinalizadas;

static BAR_tpPecasCapturadas * BARSingleton = NULL ;

/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapsuladas no módulo *****/

void RemoverPeca(void *pPeca);

/*****  Código das funçvões exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: BAR Criar lista de peças capturadas
* 
****/
BAR_tpCondRet BAR_CriarListaPecasCapturadas()
{

	BARSingleton = (BAR_tpPecasCapturadas *) malloc(sizeof(BAR_tpPecasCapturadas));
	if(BARSingleton == NULL)
	{
		return BAR_CondRetFaltouMemoria ;
	} /* if */

	BARSingleton->listaPecas = LIS_CriarLista(RemoverPeca);

	return BAR_CondRetOK ;

} /* Fim função: BAR Criar lista de peças capturadas */

/***************************************************************************
*
*  Função: BAR Inserir peça
*  
****/
BAR_tpCondRet BAR_InserirPeca(PecaHead pPeca)
{
	if(BARSingleton== NULL) 
	{
		return BAR_CondRetListaPecasCapturadasNaoExiste;
	} /* if */
	
	LIS_InserirElementoAntes(BARSingleton->listaPecas, pPeca);
	
	return BAR_CondRetOK;

} /* Fim função: BAR Inserir peça */

/***************************************************************************
*
*  Função: BAR Remover peça
*  
****/
BAR_tpCondRet BAR_RemoverPeca(PEC_color CorPeca, PecaHead *pPeca)
{
	PEC_color CorPecaTemp;
	PecaHead pPecaTemp;

	if(BARSingleton == NULL)
	{
		return BAR_CondRetListaPecasCapturadasNaoExiste;
	} /*if*/

	IrInicioLista(BARSingleton->listaPecas);

	do
	{
		pPecaTemp = (PecaHead) LIS_ObterValor(BARSingleton->listaPecas);

		PEC_ObterCor( &CorPecaTemp,pPecaTemp);

		if(CorPecaTemp == CorPeca)
		{
			*pPeca = pPecaTemp;
			LIS_ExcluirElemento(BARSingleton->listaPecas);

			return BAR_CondRetOK;
		} /* if */
	} while(LIS_AvancarElementoCorrente(BARSingleton->listaPecas, 1) == LIS_CondRetOK); /* do */

	return BAR_CondRetPecaNaoExiste;

} /* Fim função: BAR Remover peça */

/***************************************************************************
*
*  Função: BAR Conta peças
*  
****/
BAR_tpCondRet BAR_ContarPecas( PEC_color CorPeca, int *pContagem)
{
	PEC_color CorPecaTemp;
	PecaHead pPecaTemp;

	if(BARSingleton == NULL) 
	{
		return BAR_CondRetListaPecasCapturadasNaoExiste;
	} /* if */

	*pContagem = 0;

	IrInicioLista(BARSingleton->listaPecas);

	if(LIS_ObterValor(BARSingleton->listaPecas) != NULL)
	{
		do
		{
			pPecaTemp = (PecaHead) LIS_ObterValor(BARSingleton->listaPecas);
			
			PEC_ObterCor(&CorPecaTemp,pPecaTemp);

			if(CorPecaTemp == CorPeca)
			{
				(*pContagem)++;
			} /* if */
		} while(LIS_AvancarElementoCorrente(BARSingleton->listaPecas, 1) == LIS_CondRetOK); /* do */
	} /* if */

	return BAR_CondRetOK ;

} /* Fim função: BAR Conta peças */

/***************************************************************************
*
*  Função: BAR Destruir lista de peças capturadas
*  
****/
BAR_tpCondRet BAR_DestruirListaPecasCapturadas()
{
	PecaHead pPecaTemp;

	if(BARSingleton == NULL) 
	{
		return BAR_CondRetListaPecasCapturadasNaoExiste;
	} /* if */

	IrInicioLista(BARSingleton->listaPecas);

	pPecaTemp = (PecaHead) LIS_ObterValor(BARSingleton->listaPecas);
	
	while(pPecaTemp != NULL)
	{
		PEC_DestruirPeca(&pPecaTemp);
		
		if(LIS_AvancarElementoCorrente(BARSingleton->listaPecas, 1) != PEC_ok)
		{
			break;
		} /* if */

		pPecaTemp = (PecaHead) LIS_ObterValor(BARSingleton->listaPecas);
	} /* while */

	free(BARSingleton);
	BARSingleton = NULL;

	return BAR_CondRetOK ;

} /* Fim função: BAR Destruir lista de peças capturadas */

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
