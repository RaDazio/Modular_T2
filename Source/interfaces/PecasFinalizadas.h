#pragma once
/***************************************************************************
*
*	$MCD M�dulo de definição:	Módulo Pecas Finalizadas
*	
*	Arquivo gerado:			TABULEIRO.h
*	Letras identificadoras:	PF
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	   rdms - Rafael Damazio Monteiro da Silva
*               gmc - Gabriel Garcia Mascheroni Costa
*				    svp - Stefano Vivacqua Pereira
*
*
*	$HA Hist�rico e evolu��o:
*		Vers�o  Autor	Data		Observa��es
*		1.00	rdms	14/06/2019	Inicio do desenvolvimento
*     2.00  svp   17/06/2019  Ajuste retornos
*
*	$ED Descri��o do m�dulo:
*		Este m�dulo implementa a lista de peças finalizadas do jogo de gamão
*
***************************************************************************/
 
#include "peca.h"

/***** Declara��es exportadas pelo m�dulo *****/


/***********************************************************************
*
*  $TC Tipo de dados: PF Condi��es de retorno
*
*
***********************************************************************/

   typedef enum {

         PF_OK ,
               /* Concluiu corretamente */

         PF_Vazia ,
               /* PF n�o cont�m elementos */

		 PF_Erro,
				/* N�o concluiu corretamente */

         PF_FaltouMemoria
               /* Faltou mem�ria ao tentar criar a estrutura*/

   } PF_CondRet ;

/***********************************************************************
*
*  $FC Fun��o: PF &Criar estrutura de pe�as Finalizadas

*  $ED Descri��o da fun��o
*     Cria uma estrutura para as pe�as Finalizadas do jogo de gam�o
*
*  $EP Par�metros
*  AS: Caso não exista erro de memória, a estrutura será criada
*
*
***********************************************************************/

   PF_CondRet PF_CriarPecasFinalizadas() ;

/***********************************************************************
*
*  $FC Fun��o: PF Adicionar uma peça finalizada a lista
*
*  $ED Descri��o da fun��o
*		Adiciona uma pe�a da cor especificada na lista de pe�as finalizadas
*
*  $EP Par�metros
*	  cor			- A cor da peça adicionada
* AE: Será passado como parâmetro uma variável do tipo PEC_Color que indica a cor da peça a ser adicionada
* AS: Caso exista a estrutura, uma peça com essa cor será adicionada ao final
*
***********************************************************************/

   PF_CondRet PF_AdicionarPecaFinalizada(PEC_color cor) ;

/***********************************************************************
*
*  $FC Fun��o: PF Obter tamanho da lista de pe�as finalizadas
*
*  $ED Descri��o da fun��o
*		Obtem a quantidade de peças da determinada cor na lista
*
*  $EP Par�metros
*	  cor			- A cor que retornará a quantidade
*	  *tam			- Ponteiro de referencia para o tamanho da PF
*
* AE: Serão passados como parâmetro uma variável do tipo PEC_Color que indica a cor de que queremos a quantidade
* e um ponteiro que aponta para uma área de memória do tipo int que será passada como referência
* AS: Caso exista a estrutura, a variável tam será atualizada com a quantidade de peças na estrutura que possuem a cor passada.
***********************************************************************/

   PF_CondRet PF_ObterTamanhoPecasFinalizadas(PEC_color cor, int *tam) ;


/***********************************************************************
*
*  $FC Fun��o: PF Destruir PF
*
*  $ED Descri��o da fun��o
*		Destroi a lista de pe�as finalizadas
*
*  $EP Par�metros
* AS: Caso exista a estrutura, a mesma será destruída
*
***********************************************************************/

   PF_CondRet PF_DestruirPecasFinalizadas() ;

