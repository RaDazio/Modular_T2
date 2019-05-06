/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
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
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data		 Observa��es
*       1.00   rmds   05/05/2019 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo visa o teste utilizando as fun��es espec�ficas do
*      m�dulo de pe�as
*
*
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo �rvore:
*
*     "=criar"		    - chama a fun��o PEC_CriaPeca()
*     "=destroi"		- chama a fun��o PEC_DestruirPeca()
*	  "=obterCor"		- chama a fun��o PEC_ObterCor()
*
***************************************************************************/

#include<stdio.h>
#include<string.h>

#include    "../TESTES_GENERICO/TST_ESPC.H"
#include    "../TESTES_GENERICO/generico.h"
#include    "../TESTES_GENERICO/lerparm.h"

#include	"../../Source/interfaces/peca.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define CRIAR		"=criar"
#define OBTER_COR	"=obterCor"
#define DESTROI		"=destroi"

	  PecaHead peca = NULL;


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TPECA Efetuar opera��es de teste espec�ficas para pe�as
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     pe�as sendo testado.
*
*  $EP Par�metros
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

      /* Testar PEC Criar pe�a */

         if ( strcmp( ComandoTeste , CRIAR ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,&cor_inserir, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRetObtido = PEC_CriaPeca(cor_inserir,&peca);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar pe�a." );

         } /* fim ativa: Testar PEC Criar pe�a */


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
                                     "Conte�do da pe�a est� errado." ) ;

         } /* fim ativa: Testar PEC Obter cor */

      /* Testar PEC Destruir pe�a */

         else if ( strcmp( ComandoTeste , DESTROI ) == 0 )
         {
            PEC_DestruirPeca(&peca);
			peca = NULL;
			return TST_CondRetOK ;

         } /* fim ativa: Testar PEC Destruir pe�a */

		 else{
			 return TST_CondRetNaoConhec;
		 }

   } /* Fim fun��o: TPEC Efetuar opera��es de teste espec�ficas para pe�as */