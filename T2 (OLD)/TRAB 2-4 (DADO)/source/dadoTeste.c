/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              dadoTeste.C
*  Letras identificadoras:      TDICE
*

*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*
*	Autores:	gcmc - Gabriel Garcia Mascheroni Costa
*				rdms - Rafael Damazio Monteiro da Silva
*				fo	 - Felipe de Oliveira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data		 Observações
*       1.00   rmds   05/05/2019 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo visa o teste utilizando as funções específicas do
*      módulo de dados
*
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo árvore:
*
*     "=rolar"		    - chama a função DICE_RolarDado()
***************************************************************************/

#include<stdio.h>
#include<string.h>

#include    "../TESTES_GENERICO/TST_ESPC.H"
#include    "../TESTES_GENERICO/generico.h"
#include    "../TESTES_GENERICO/lerparm.h"

#include	"../../Source/interfaces/dado.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define ROLAR	"=rolar"

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TDICE Efetuar operações de teste específicas para peças
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     peças sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

	   DICE_CondRet CondRetObtido   = DICE_ok ;
	   DICE_CondRet CondRetEsperada = DICE_wrong ;
                                      /* inicializa para qualquer coisa */

	  int numLados = -1;
	  int value=-1;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar DICE Rolar dado */

         if ( strcmp( ComandoTeste , ROLAR ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,&numLados, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRetObtido = DICE_RolarDado(&value,numLados);

			if(value > numLados){
				return TST_CondRetErro;
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar peça." );
		
         } /* fim ativa: Testar DICE Rolar dado */
		 else{
			 return TST_CondRetNaoConhec;
		 }

   } /* Fim função: TDICE Efetuar operações de teste específicas para dado */