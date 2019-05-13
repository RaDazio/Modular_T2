/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              tabuleiroTeste.C
*  Letras identificadoras:      TTBL
*

*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*
*	Autores:	gmc - Gabriel Garcia Mascheroni Costa
*				rdms - Rafael Damazio Monteiro da Silva
*				fo	 - Felipe de Oliveira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data		 Observações
*       1.00   gmc   08/05/2019 Início do desenvolvimento
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
*     "=criar"		    - chama a função TBL_CriarTabuleiro()
*     "=destruir"		- chama a função TBL_DestruirTabuleiro()
*	  "=obterCasas"		- chama a função TBL_ObterCasas()
*	  "=moverPeca"		- chama a função TBL_MoverPeca()
*
***************************************************************************/

#include<stdio.h>
#include<string.h>

#include    "../TESTES_GENERICO/TST_ESPC.H"
#include    "../TESTES_GENERICO/generico.h"
#include    "../TESTES_GENERICO/lerparm.h"

#include	"../../Source/interfaces/tabuleiro.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define CRIAR		"=criar"
#define DESTRUIR	"=destruir"
#define OBTER_CASAS	"=obterCasas"
#define MOVER_PECA	"=moverPeca"



/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TTABULEIRO Efetuar operações de teste específicas para peças
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

	  TBL_CondRet CondRetObtido   = TBL_ok ;
	  TBL_CondRet CondRetEsperada = TBL_notEnoughMemory ;
                                      /* inicializa para qualquer coisa */



      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar TBL Criar tabuleiro */

         if ( strcmp( ComandoTeste , CRIAR ) == 0 )
         {

            NumLidos = LER_LerParametros("i", &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } 
			CondRetObtido = TBL_CriarTabuleiro();

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao utilizar tabuleiro." );

         } /* fim ativa: Testar PEC Criar peça */

		/* Testar TBL Destruir Tabuleiro */

         else if ( strcmp( ComandoTeste , DESTRUIR ) == 0 )
         {
			 NumLidos = LER_LerParametros("i", &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } 
            CondRetObtido = TBL_DestruirTabuleiro();
			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar peça." );

         } /* fim ativa: Testar TBL Destruir Tabuleiro */
		 
		 /* Testar TBL Obter Casas */
		 
		 else if ( strcmp( ComandoTeste , OBTER_CASAS ) == 0 )
         {
			LIS_tppLista casas = NULL;
			 NumLidos = LER_LerParametros("i", &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } 
			
            CondRetObtido = TBL_ObterCasas(&casas);
			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar peça." );

         } /* fim ativa: Testar TBL Obter Casas */
		 
		 /* Testar TBL Mover Peca */
		 
		 else if ( strcmp( ComandoTeste , MOVER_PECA ) == 0 )
         {
			int casaInicio, casaFim = 0;
			NumLidos = LER_LerParametros("iii", &casaInicio, &casaFim, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } 
            CondRetObtido = TBL_MoverPeca(casaInicio, casaFim);
			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar peça." );

         } /* fim ativa: TBL Mover Peca */

		 else{
			 return TST_CondRetNaoConhec;
		 }

   } /* Fim função: TPEC Efetuar operações de teste específicas para tabuleiro */
