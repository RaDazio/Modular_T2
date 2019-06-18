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
*     Comandos de teste espec�ficos para testar o m�dulo peca capturada:
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

#include	"../../Source/interfaces/PecasFinalizadas.h"
#include	"../../Source/interfaces/peca.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define CRIAR		               "=criar"
#define INSERIR_PECA			   "=inserir"
#define OBTER_QTD_PECAS			   "=contar"
#define DESTRUIR                   "=destruir"


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

	 PF_CondRet CondRetObtido   = PF_OK ;
	 PF_CondRet CondRetEsperada = PF_FaltouMemoria ;
                                      /* inicializa para qualquer coisa */


	  PEC_color cor;
	  
	  int qtd;

      int  NumLidos = -1 ;

      /* Testar PF Criar pe�aFinalizada */

         if ( strcmp( ComandoTeste , CRIAR ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRetObtido = PF_CriarPecasFinalizadas();

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar pe�aCapturada." );

         } 


      /* Testar PF Adicionar Peca */

         else if ( strcmp( ComandoTeste , INSERIR_PECA ) == 0 )
         {

			 NumLidos = LER_LerParametros( "ii" , &cor , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PF_AdicionarPecaFinalizada(cor) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao inserir pecaCapturada." );

         } 


	    /* Teste PF Obter Quantidade Pecas */

         else if ( strcmp( ComandoTeste , OBTER_QTD_PECAS ) == 0 )
         {
		  int qtd_esperada;
		  TST_tpCondRet ret;
          NumLidos = LER_LerParametros( "iii" , &cor , &qtd_esperada,  &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PF_ObterTamanhoPecasFinalizadas(cor, &qtd) ;

			ret = TST_CompararInt(qtd_esperada,qtd,"Valores diferentes");
			if(ret != TST_CondOK){
				return ret;
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter quantidade de pecas." );

         } 

      /* Testar PF Destruir pe�aFinalizadas */

         else if ( strcmp( ComandoTeste , DESTRUIR ) == 0 )
         {
            NumLidos = LER_LerParametros("i" , &CondRetEsperada);
         
            if(NumLidos != 1)
            {
               return TST_CondRetParm;
            } /* if */

			CondRetObtido = PF_DestruirPecasFinalizadas();

            return TST_CompararInt(CondRetEsperada , CondRetObtido , "Erro ao destruir pecas capturadas.");
		 } 

		 else{
			 return TST_CondRetNaoConhec;
		 }
   } /* Fim fun��o: PF Efetuar opera��es de teste espec�ficas  */
