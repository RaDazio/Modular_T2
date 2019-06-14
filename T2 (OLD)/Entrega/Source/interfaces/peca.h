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
*		2.00	rdms	05/05/2019	Modificação na assinatura da função de destruir uma peça.
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

	PEC_ok = 0,
		/* Executou corretamente */
	PEC_doNotExist = 1,
		/* Não existe a peça */
	PEC_colorNotExist = 2,
		/*	A cor fornecida não é preta nem branca */
	PEC_alreadyExists = 3,
		/*	A variavel ja possui uma peça associada */
	PEC_notEnoughMemory = 4,
		/* Faltou memoria */
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
*	Assertiva de entrada:
*		Deve existir um ponteiro para qual a peça criada será retornada por
*		referência.
*		A cor passada deve ser um enum exportado pelo módulo.
*	Assertiva de saída:
*			A peça criada com a cor passada será salva no ponteiro passado por
*			referência.
*
*	$ED Descrição da função:
*		Esta função cria uma peça.
*
*	$EP Parâmetros:
*		$P	color	 -	Enum de cor definida no módulo
*
*		$P	ret		 -	Referência de retorno da peça]
*
*	$FV Valor retornado:
*		PEC_alreadyExists	-	Caso a variavel passada já possua uma peça alocada
*		PEC_colorNotExist	-	Caso a cor passada para criar a peça não seja suportada
*		PEC_notEnoughMemory	-	Caso falhe ao alocar espaço
*		PEC_ok				-	Caso a função ocorra normalmente
*
***********************************************************************/

PEC_CondRet PEC_CriaPeca(PEC_color color, PecaHead* ret);

/***********************************************************************
*
*	$FC Função:	PEC Obter cor
*
*	Assertiva de entrada:
*			Deve existir uma área de memória do tipo PEC_Color para qual
*	 		será retornado o tipo da cor.
*	Assertiva de saída:
*			Caso não exista a peça a função não retornará a cor na área de memória
*			do retorno da cor
*
*	$ED Descrição da função:
*		Esta função obtem a cor de uma peça.
*
*	$EP Parâmetros:
*		$P	ret	 -	Referencia de retorno de cor de peça
*
*		$P	peca -	Peça, tipo de dado exportado pelo módulo.
*
*	$FV Valor retornado:
*		PEC_doNotExist	-	Caso a variavel passada aponte para NULL
*		PEC_ok			-	Caso a função ocorra normalmente
*
***********************************************************************/

PEC_CondRet PEC_ObterCor(PEC_color *ret, PecaHead peca);

/***********************************************************************
*
*	$FC Função:	PEC Destruir Peça
*
*	Assertiva de entrada:
*			O espaço de dados passado deve possuir uma peça alocada
*	Assertiva de Saída
*			Após a destruição da peça, o ponteiro passado terá o valor de NULL.
*
*	$ED Descrição da função:
*		Esta função destroi uma peça
*
*	$EP Parâmetros
*
*		$P	peca -	Peça, tipo de dado exportado pelo módulo.
*
*	$FV Valor retornado:
*		PEC_ok
*
***********************************************************************/

PEC_CondRet PEC_DestruirPeca(PecaHead *peca);

