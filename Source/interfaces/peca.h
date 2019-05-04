#pragma once
/***************************************************************************
*
*	$MCD Módulo de definição:	Módulo Peças
*	
*	Arquivo gerado:			PEÇA.h
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
*
*	$ED Descrição do módulo:
*		Este módulo implementa e gerencia a estrutura de peças.
*
***************************************************************************/


/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
*
***********************************************************************/

typedef enum{

	PEC_notEnoughMemory = -1,
		/* Faltou memoria */
	PEC_ok = 0,
		/* Executou corretamente */
	PEC_doNotExist = 1,
		/* Não existe a peça */
	PEC_colorNotExist = 2,
		/*	A cor fornecida não é preta nem branca */
	PEC_alreadyExists = 3
		/*	A variavel ja possui uma peça associada */
} PEC_CondRet;


/***********************************************************************
*
*  $TC Tipo de dados: PEC Cores (Preta ou Branca)
*
*
***********************************************************************/

typedef enum{
	COLOR_Black = 0,
		/* Cor preta */
	COLOR_White = 1
		/* Cor branca */
}PEC_color;


/******* TIPOS E FUNÇÕES EXPORTADOS DO MÓDULO *****************************/

typedef struct peca* PecaHead;

/***********************************************************************
*
*	$FC Função:	PEC Cria peça
*
*	$ED Descrição da função:
*		Esta função cria uma peça.
*
*	$EP Parâmetros:
*		$P	color	 -	Enum de cor definida no módulo
*
*		$P	ret		 -	Referência de retorno da peça
*
***********************************************************************/

PEC_CondRet PEC_CriaPeca(PEC_color color, PecaHead* ret);

/***********************************************************************
*
*	$FC Função:	PEC Obter cor
*
*	$ED Descrição da função:
*		Esta função obtem a cor de uma peça.
*
*	$EP Parâmetros:
*		$P	ret	 -	Referencia de retorno de cor de peça
*
*		$P	peca -	Peça, tipo de dado exportado pelo módulo.
*
***********************************************************************/

PEC_CondRet PEC_ObterCor(PEC_color *ret, PecaHead peca);

/***********************************************************************
*
*	$FC Função:	PEC Destruir Peça
*
*	$ED Descrição da função:
*		Esta função destroi uma peça
*
*	$EP Parâmetros
*
*		$P	peca -	Peça, tipo de dado exportado pelo módulo.
*
***********************************************************************/

PEC_CondRet PEC_DestruirPeca(PecaHead peca);
