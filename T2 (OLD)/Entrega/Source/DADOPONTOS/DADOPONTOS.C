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
#include "DADOPONTOS.H"
#undef DADOPONTOS_OWN

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

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: DPT Criar dado de pontos
* 
****/
DPT_CondRet DPT_CriarDadoPontos(DPT_DadoHead * pDadoPontos)
{
	*pDadoPontos = (DPT_DadoHead) malloc(sizeof(DPT_DadoPontos));
	if(pDadoPontos == NULL)
	{
		return DPT_FalhaMemoria ;
	} 

	(*pDadoPontos)->Pontuacao = 1;

	return DPT_OK ;

} /* Fim função: DPT Criar dado de pontos */
/***************************************************************************
*
*  Função: DPT Atualizar jogador
*  
****/
DPT_CondRet DPT_AtualizarJogadorDobra(DPT_DadoHead pDadoPontos, PEC_color CorPeca)
{
	if(pDadoPontos == NULL) 
	{
		return DPT_NaoHaDadoPontos;
	} 

	pDadoPontos->CorPeca = CorPeca;

	return DPT_OK ;

} /* Fim função: Atualizar jogador */
/***************************************************************************
*
*  Função: DPT Dobrar pontuação da partida
*  
****/
DPT_CondRet DPT_DobrarPontuacaoPartida(DPT_DadoHead pDadoPontos, PEC_color CorPeca)
{
	if(pDadoPontos == NULL) 
	{
		return DPT_NaoHaDadoPontos;
	} 
	if(pDadoPontos->CorPeca != CorPeca)
	{
		return DPT_JogadorNaoPossuiDadoPontos;
	} /* if */

	pDadoPontos->Pontuacao *= 2;

	return DPT_OK ;
}

/***************************************************************************
*
*  Função: DPT Obter jogador que possui o dado de pontos
*  
****/
DPT_CondRet DPT_ObterJogadorDobraPartida(DPT_DadoHead pDadoPontos, PEC_color* pCorPeca)
{
	if(pDadoPontos == NULL)
	{
		return DPT_NaoHaDadoPontos;
	} /* if */

	if(pDadoPontos->Pontuacao == 1)
	{
		return DPT_NaoHaJogadorDadoPontos;
	}

	*pCorPeca = pDadoPontos->CorPeca;

	return DPT_OK ;
}


/***************************************************************************
*
*  Função: DPT Obter pontuação da partida
*  
****/
DPT_CondRet DPT_ObterPontuacaoPartida(DPT_DadoHead pDadoPontos, int* pPontuacao)
{
	if(pDadoPontos == NULL) 
	{
		return DPT_NaoHaDadoPontos;
	} /* if */

	*pPontuacao = pDadoPontos->Pontuacao;

	return DPT_OK ;
}

/***************************************************************************
*
*  Função: DPT Destruir dado de pontos
*  
****/
DPT_CondRet DPT_DestruirDadoPontos(DPT_DadoHead* pDadoPontos)
{
	if(*pDadoPontos == NULL) 
	{
		return DPT_NaoHaDadoPontos;
	} /* if */
	free(*pDadoPontos);
	*pDadoPontos = NULL;

	return DPT_OK;


} /* Fim função: DPT Destruir dado de pontos */

/********** Fim do módulo de implementação: Módulo dado de pontos **********/
