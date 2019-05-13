/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              pecaTeste.C
*  Letras identificadoras:      TPEC
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
*      módulo de peças
*
*
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo peca:
*
*     "=criar"		    - chama a função PEC_CriaPeca()
*     "=destroi"		- chama a função PEC_DestruirPeca()
*	  "=obterCor"		- chama a função PEC_ObterCor()
*
***************************************************************************/

#include<stdio.h>
#include<string.h>

#include    "../TESTES_GENERICO/TST_ESPC.H"
#include    "../TESTES_GENERICO/generico.h"
#include    "../TESTES_GENERICO/lerparm.h"

#include	"../../Source/interfaces/peca.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define CRIAR		"=criar"
#define OBTER_COR	"=obterCor"
#define DESTROI		"=destroi"

/* Singleton para realização dos testes */
static PecaHead peca = NULL;


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPECA Efetuar operações de teste específicas para peças
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

	  PEC_CondRet CondRetObtido   = PEC_ok ;
	  PEC_CondRet CondRetEsperada = PEC_notEnoughMemory ;
                                      /* inicializa para qualquer coisa */


	  PEC_color cor_inserir;
	  PEC_color cor_retorno;
	  PEC_color cor_esperada;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar PEC Criar peça */

         if ( strcmp( ComandoTeste , CRIAR ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,&cor_inserir, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRetObtido = PEC_CriaPeca(cor_inserir,&peca);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar peça." );

         } /* fim ativa: Testar PEC Criar peça */


      /* Testar PEC Obter cor */

         else if ( strcmp( ComandoTeste , OBTER_COR ) == 0 )
         {

			 NumLidos = LER_LerParametros( "ii" , &cor_esperada , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PEC_ObterCor(&cor_retorno,peca) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter Cor." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */
			

			return TST_CompararInt( cor_esperada, cor_retorno,
                                     "Conteúdo da peça está errado." ) ;

         } /* fim ativa: Testar PEC Obter cor */

      /* Testar PEC Destruir peça */

         else if ( strcmp( ComandoTeste , DESTROI ) == 0 )
         {
            PEC_DestruirPeca(&peca);
			peca = NULL;
			return TST_CondRetOK ;

         } /* fim ativa: Testar PEC Destruir peça */

		 else{
			 return TST_CondRetNaoConhec;
		 }

   } /* Fim função: TPEC Efetuar operações de teste específicas para peças */
