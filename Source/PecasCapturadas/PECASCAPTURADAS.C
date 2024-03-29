
/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo pe�as capturadas
*
*  Arquivo gerado:              PECASCAPTURADAS.C
*  Letras identificadoras:      PCAP
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	fo	 - Felipe de Oliveira
*				svp  - stefano vivacqua pereira
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data         Observa��es
*       1.00   		fo   		10/06/2019 		In��io do desenvolvimento
*		2.00		svp			14/06/2019		Mudanca de approach para semelhante ao PecasFinalizadas
*		3.00		svp			15/06/2019		Ajustes no retorno
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define PECASCAPTURADAS_OWN
#include "../interfaces/PECASCAPTURADAS.H"
#undef PECASCAPTURADAS_OWN

#include "../interfaces/peca.h"
#include "../interfaces/LISTA.h"


/***********************************************************************
*
*  $TC Tipo de dados: PCAP Descritor da pe�a capturadas
*
*
***********************************************************************/

typedef struct PCAP_tagPecasCapturadas {

	LIS_tppLista listaPecasBrancas;
	LIS_tppLista listaPecasPretas;
	/* Lista de pe�as capturadas */

} PCAP_tpPecasCapturadas;

/*****  Dados encapsulados no m�dulo  *****/

static PCAP_tpPecasCapturadas * PCAPSingleton = NULL ;

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***************************************************************************
*
*  Fun��o: PCAP Criar lista de pe�as capturadas
* 
****/

static void ExcluirPecaCapturada(void *pPeca){
	PecaHead pPecaTemp = (PecaHead) pPeca;
	PEC_DestruirPeca(pPecaTemp);
}

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: PCAP Criar lista de pe�as capturadas
* 
****/
PCAP_CondRet PCAP_CriarListasPecasCapturadas(){

	if(PCAPSingleton != NULL){
		return PCAP_CondRetPecasCapturadasJaExiste;
	}

	PCAPSingleton = (PCAP_tpPecasCapturadas *) malloc(sizeof(PCAP_tpPecasCapturadas));

	// TESTE ALOCACAO //
	if(PCAPSingleton == NULL)
	{
		return PCAP_CondRetFaltouMemoria ;
	} /* if */

	// CRIACAO LISTAS //
	PCAPSingleton->listaPecasBrancas = LIS_CriarLista(ExcluirPecaCapturada);
	PCAPSingleton->listaPecasPretas = LIS_CriarLista(ExcluirPecaCapturada);

	return PCAP_CondRetOK ;

} /* Fim fun��o: PCAP Criar lista de pe�as capturadas */

/***************************************************************************
*
*  Fun��o: PCAP Inserir peca capturada
*  
****/

PCAP_CondRet PCAP_InserirPecaCapturada(PEC_color cor){

	// CRIA PE�A A SER INSERIDA (JA COM A COR DESEJADA) //
	PecaHead novaPeca = NULL;
	PEC_CondRet pec_ret = PEC_CriaPeca(cor, &novaPeca);
	//***//

	// CHECA SE SINGLETON EXISTE //
	if(PCAPSingleton == NULL){
		printf("Singleton pecas capturadas nao existe.\n");
		return PCAP_CondRetErroNaoExisteSingleton;
	}

	// INSERCAO BRANCA //
	if(cor == COLOR_White){
		if(LIS_InserirElementoApos(PCAPSingleton->listaPecasBrancas, novaPeca) != LIS_CondRetOK){
			printf("Erro ao inserir peca na lista de capturadas (brancas).\n");
			return PCAP_CondRetErroInsercaoListaBranca;
		}

	}// Fim insercao branca //
	// INSERCAO PRETA //
	else if(cor == COLOR_Black){
		if(LIS_InserirElementoApos(PCAPSingleton->listaPecasPretas, novaPeca) != LIS_CondRetOK){
			printf("Erro ao inserir peca na lista de capturadas (pretas).\n");
			return PCAP_CondRetErroInsercaoListaPreta;
		}
	}
	// INSERCAO DE COR DESCONHECIDA //
	else{
		return PCAP_CondRetCorInexistente;
	}

	return PCAP_CondRetOK;

} /* Fim fun��o: PCAP Inserir pe�a */

/***************************************************************************
*
*  Fun��o: PCAP Remover pe�a
*  
****/
PCAP_CondRet PCAP_RemoverPecaCapturada(PEC_color cor){

	if(PCAPSingleton == NULL){
		printf("Singleton pecas capturadas nao existe.\n");
		return PCAP_CondRetErroNaoExisteSingleton;
	}

	if(cor == COLOR_White){
		if(LIS_ExcluirElemento(PCAPSingleton->listaPecasBrancas) != LIS_CondRetOK)
			return PCAP_CondRetErroRemocaoPecaBranca;
	}
	else if(cor == COLOR_Black){
		if(LIS_ExcluirElemento(PCAPSingleton->listaPecasPretas) != LIS_CondRetOK)
			return PCAP_CondRetErroRemocaoPecaPreta;
	}
	else{
		return PCAP_CondRetCorInexistente;
	}

	return PCAP_CondRetOK;

} /* Fim fun��o: PCAP Remover pe�a */

/***************************************************************************
*
*  Fun��o: PCAP Obter Quantidade Pe�as Capturadas
*  
****/

PCAP_CondRet PCAP_ObterQuantidadePecasCapturadas(PEC_color cor, int *qtd){

	// CHECA SE SINGLETON EXISTE //
	if(PCAPSingleton == NULL){
		printf("Singleton pecas capturadas nao existe.\n");
		return PCAP_CondRetErroNaoExisteSingleton;
	}

	if(cor == COLOR_White){
		*qtd = LIS_ObterTamanho(PCAPSingleton->listaPecasBrancas);
	}
	else if(cor == COLOR_Black){
		*qtd = LIS_ObterTamanho(PCAPSingleton->listaPecasPretas);
	}
	else{
		return PCAP_CondRetCorInexistente;
	}

	return PCAP_CondRetOK;
} /* Fim funcao: PCAP Obter Quantidade Pe�as Capturadas */

/***************************************************************************
*
*  Fun��o: PCAP Destruir lista de pe�as capturadas
*  
****/
PCAP_CondRet PCAP_DestruirPecasCapturadas(){

	if(PCAPSingleton == NULL){
		printf("Singleton pecas capturadas nao existe.\n");
		return PCAP_CondRetErroNaoExisteSingleton;
	}

	LIS_DestruirLista(PCAPSingleton->listaPecasBrancas);
	LIS_DestruirLista(PCAPSingleton->listaPecasPretas);

	free(PCAPSingleton);
	PCAPSingleton = NULL;

	return PCAP_CondRetOK;
} /* Fim funcao: PCAP Destruir lista de pe�as capturadas */

/********** Fim do m�dulo de implementa��o: M�dulo pe�as capturadas **********/