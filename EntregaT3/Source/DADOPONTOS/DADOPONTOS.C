/********************************************************************************************
*	$MCI Módulo de implementação:	Módulo Dado pontos
*
*	Arquivo gerado:			DADOPONTOS.C
*	Letras identificadoras:	DPT
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
*		1.00	fo	27/04/2019	Inicio do desenvolvimento
*
*******************************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define DADOPONTOS_OWN
#include "..\interfaces\DADOPONTOS.H"
#undef DADOPONTOS_OWN
#include "..\interfaces\PECA.h"

/***********************************************************************
*
*  $TC Tipo de dados: DPT Descritor do dado de pontos
*
*  $ED Descrição do tipo
*		Descreve a organização de um dado de pontos
***********************************************************************/

typedef struct dadopontos
{
	int Pontuacao;
	/* Pontuação  do jogo no momento*/

	PEC_color CorPeca;
	/* Cor da peça do jogador que pode dobrar o jogo */

} DPT_DadoPontos;

/*****  Dados encapsulados no módulo  *****/

static DPT_DadoPontos *DadoPontosSingletoon = NULL;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: DPT Criar dado de pontos
* 
****/
DPT_CondRet DPT_CriarDadoPontos()
{
	if(DadoPontosSingletoon != NULL)
	{
		return DPT_JaExisteDadoPontos;
	}
	DadoPontosSingletoon = (DPT_DadoPontos*) malloc(sizeof(DPT_DadoPontos));
	if(DadoPontosSingletoon == NULL)
	{
		return DPT_FalhaMemoria ;
	} 

	DadoPontosSingletoon->Pontuacao = 1;

	return DPT_OK ;

} /* Fim função: DPT Criar dado de pontos */
/***************************************************************************
*
*  Função: DPT Atualizar jogador
*  
****/
DPT_CondRet DPT_AtualizarJogadorDobra(PEC_color CorPeca)
{
	if(DadoPontosSingletoon == NULL) 
	{
		return DPT_NaoHaDadoPontos;
	} 

	(DadoPontosSingletoon)->CorPeca = CorPeca;

	return DPT_OK ;

} /* Fim função: Atualizar jogador */

/***************************************************************************
*
*  Função: DPT Atualizar pontuação da partida
* ARGUMENTACAO DE CORRETUDE:
*  AE: existe uma variavel do tipo inteiro inicializada pelo usuaria que sera passada como parametro para funcao.
*-
****/
DPT_CondRet DPT_AtualizarPontuacaoPartida(int Pontuacao)
{	
	/*AE1=AE*/
	if(DadoPontosSingletoon == NULL) 
	{
		return DPT_NaoHaDadoPontos;
	} /* if */
	/*AS1: Se a condicao for verdadeira,a funcao sera encerrada e sera retornado um valor que indica que nao ha dado de pontos, valendo a AS
	 * Caso a condicao seja falsa, ou seja, DadoPontosSingletoon seja diferente de NULL, vale a AS*/

	DadoPontosSingletoon->Pontuacao = Pontuacao;

	return DPT_OK ;
} /* Fim função: Atualizar Pontuacao
AS: Caso Dadopontossingletoon nao seja null, a area dadopontossingleton->pontuacao que e designada para guardar a pontuacao do dado de pontos devera ser atualizda com o valor passado.
/***************************************************************************
*
*  Função: DPT Dobrar pontuação da partida
*  
****/
DPT_CondRet DPT_DobrarPontuacaoPartida(PEC_color CorPeca)
{
	if(DadoPontosSingletoon == NULL) 
	{
		return DPT_NaoHaDadoPontos;
	} 
	if(DadoPontosSingletoon->CorPeca != CorPeca)
	{
		return DPT_JogadorNaoPossuiDadoPontos;
	} /* if */
	if( DadoPontosSingletoon->Pontuacao < 64){
		DadoPontosSingletoon->Pontuacao *= 2;
	}

	return DPT_OK ;
}

/***************************************************************************
*
*  Função: DPT Obter jogador que possui o dado de pontos
*  
****/
DPT_CondRet DPT_ObterJogadorDobraPartida(PEC_color* pCorPeca)
{
	if(DadoPontosSingletoon == NULL)
	{
		return DPT_NaoHaDadoPontos;
	} /* if */

	if(DadoPontosSingletoon->Pontuacao == 1)
	{
		return DPT_NaoHaJogadorDadoPontos;
	}

	*pCorPeca = DadoPontosSingletoon->CorPeca;

	return DPT_OK ;
}


/***************************************************************************
*
*  Função: DPT Obter pontuação da partida
*  
****/
DPT_CondRet DPT_ObterPontuacaoPartida(int* pPontuacao)
{
	if(DadoPontosSingletoon == NULL) 
	{
		return DPT_NaoHaDadoPontos;
	} /* if */

	*pPontuacao = DadoPontosSingletoon->Pontuacao;

	return DPT_OK ;
}

/***************************************************************************
*
*  Função: DPT Destruir dado de pontos
*  
****/
DPT_CondRet DPT_DestruirDadoPontos()
{
	if(DadoPontosSingletoon == NULL) 
	{
		return DPT_OK;
	} /* if */
	free(DadoPontosSingletoon);
	DadoPontosSingletoon = NULL;

	return DPT_OK;

} /* Fim função: DPT Destruir dado de pontos */

/********** Fim do módulo de implementação: Módulo dado de pontos **********/
