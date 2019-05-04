#pragma once
/***************************************************************************
*
*	$MCD M�dulo de defini��o:	M�dulo Pe�as
*	
*	Arquivo gerado:			PE�A.h
*	Letras identificadoras:	PEC
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	gcmc - Gabriel Garcia Mascheroni Costa
				rdms - Rafael Damazio Monteiro da Silva
*				fo	 - Felipe de Oliveira
*
*	$HA Hist�rico e evolu��o:
*		Vers�o  Autor	Data		Observa��es
*		1.00	rdms	21/04/2019	Inicio do desnvolvimento
*
*	$ED Descri��o do m�dulo:
*		Este m�dulo implementa e gerencia a estrutura de pe�as.
*
***************************************************************************/


/***********************************************************************
*
*  $TC Tipo de dados: PEC Condi��es de retorno
*
*
***********************************************************************/

typedef enum{

	PEC_notEnoughMemory = -1,
		/* Faltou memoria */
	PEC_ok = 0,
		/* Executou corretamente */
	PEC_doNotExist = 1,
		/* N�o existe a pe�a */
	PEC_colorNotExist = 2,
		/*	A cor fornecida n�o � preta nem branca */
	PEC_alreadyExists = 3
		/*	A variavel ja possui uma pe�a associada */
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


/******* TIPOS E FUN��ES EXPORTADOS DO M�DULO *****************************/

typedef struct peca* PecaHead;

/***********************************************************************
*
*	$FC Fun��o:	PEC Cria pe�a
*
*	$ED Descri��o da fun��o:
*		Esta fun��o cria uma pe�a.
*
*	$EP Par�metros:
*		$P	color	 -	Enum de cor definida no m�dulo
*
*		$P	ret		 -	Refer�ncia de retorno da pe�a
*
***********************************************************************/

PEC_CondRet PEC_CriaPeca(PEC_color color, PecaHead* ret);

/***********************************************************************
*
*	$FC Fun��o:	PEC Obter cor
*
*	$ED Descri��o da fun��o:
*		Esta fun��o obtem a cor de uma pe�a.
*
*	$EP Par�metros:
*		$P	ret	 -	Referencia de retorno de cor de pe�a
*
*		$P	peca -	Pe�a, tipo de dado exportado pelo m�dulo.
*
***********************************************************************/

PEC_CondRet PEC_ObterCor(PEC_color *ret, PecaHead peca);

/***********************************************************************
*
*	$FC Fun��o:	PEC Destruir Pe�a
*
*	$ED Descri��o da fun��o:
*		Esta fun��o destroi uma pe�a
*
*	$EP Par�metros
*
*		$P	peca -	Pe�a, tipo de dado exportado pelo m�dulo.
*
***********************************************************************/

PEC_CondRet PEC_DestruirPeca(PecaHead peca);
