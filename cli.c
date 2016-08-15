#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#define SIZE 100

/******************************************************************************
 * Function: free_cliente (cliente*cli)
 *
 * Arguments: cli (estrutura que contem a informacao do cliente)
 *            
 * Returns: none
 * 
 * Description: Liberta a memoria alocada para a estrutura cliente
 *****************************************************************************/
void free_cliente(cliente*cli){
	if(cli->n_restr>=1){
	free(cli->lista_rest);
	}
	free(cli);
}

/**************************************************************************************
 * Function: ini_cliente (int origem, int destino, int disp, char* t_rota, int n_restr)
 *
 * Arguments: origem (cidade origem do cliente)
 * 			  destino (cidade destino do cliente)
 * 			  disp (disponibilidade do cliente)
 * 			  t_rota (preferencia de tempo ou custo)
 * 			  n_restr (numero de restricoes do cliente) 
 *            
 * Returns: Estrutura do tipo cliente
 * 
 * Description: Alocacao da estrutura cliente e preenchimento desta com a informacao recebida da linhas
 * 				do ficheiro clientem, alocacao do vector de restricoes. 
 *************************************************************************************/
cliente* ini_cliente(int origem, int destino, int disp, char* t_rota,
int n_restr){
	cliente *cli = (cliente*)malloc(sizeof(struct cliente));
	restr *vect= NULL;
	cli->origem = origem;  /*preenchimento dos atributos do cliente*/
	cli->destino = destino;
	cli->disp = disp;
	if(strcmp(t_rota,"tempo")==0){ /*codificao da preferencia para numero*/
	cli-> t_rota =0;               /*1=custo , 0=tempo*/
	}else{ 
	cli-> t_rota =1;
	}
	cli->n_restr = n_restr; /*numero de restricoes maximo e 2 logo allocamos na memoria um vector*/
	vect = (restr*)malloc(2*sizeof(struct restr)); /*de 2 posicoes do tipo restr(estrutura das restricoes)*/
	cli->lista_rest = vect;
	return (cli); /*retorno da estrutura cliente preenchida expecto na parte das restricoes*/
}

/*************************************************************************************
 * Function: cli_seg(cliente* cli,int origem, int destino, int disp, char* t_rota,
 *			 int n_restr,char* aux_1, char* aux_2, char* aux_3,char* aux_4)
 *
 * Arguments: cli (ponteiro para a estrutura cliente)
 * 			  origem (cidade origem do cliente)
 * 			  destino (cidade destino do cliente)
 * 			  disp (disponibilidade do cliente)
 * 			  t_rota (preferencia de tempo ou custo)
 * 			  n_restr (numero de restricoes do cliente)
 * 			  aux_1 (string do tipo de restricao)
 * 			  aux_2 (string do valor complementar a restricao)
 * 			  aux_3 (string do tipo de restricao)
 * 			  aux_4 (string do valor complementar a restricao)
 *            
 * Returns: Estrutura cliente
 * 
 * Description: Funcao modifica a estrutura cliente do cliente anterior, para o cliente
 * 				seguinte.
 ************************************************************************************/
cliente* cli_seg(cliente* cli,int origem, int destino, int disp, char* t_rota,
int n_restr,char* aux_1, char* aux_2, char* aux_3,char* aux_4){
	int aux1=0,aux2=0;  
	cli->origem=origem;
	cli->destino=destino;
	cli->disp=disp;
	if(strcmp(t_rota,"tempo")==0){ 
	cli-> t_rota =0;
	}else{
	cli-> t_rota =1;
	}
	if(n_restr>0){
			if(strcmp(aux_1,"A1")==0){ /*caso da restricao A codificao do meio de transporte*/
					aux1 =cmp_meios(aux_2);	
					if(n_restr==2){	/*resto das restricoes, passagem da string lida*/	
						aux2 =atoi(aux_4); /*para inteiro atraves da funcao atoi */
					}	
			}else{
					aux1= atoi(aux_2);
					if(n_restr==2){		
						aux2 =atoi(aux_4);
				}
			}
		}
	switch(cli->n_restr){ /*numero das restricoes do cliente anterior*/
		case 0:           /*modificacao para restricoes do cliente actual*/
			if(n_restr > 0){
				cli->n_restr = n_restr;
				cli=insere_rest(cli,aux_1,aux_3,aux1,aux2);
			}  
		 break;
		case 1:
		    switch (n_restr){
				case 0:
				    cli->n_restr = n_restr;
				 break;
				case 1:
				    cli->n_restr = n_restr;
					cli=insere_rest(cli,aux_1,aux_3,aux1,aux2);	
			     break;
				case 2:
				    cli->n_restr = n_restr;	
					cli=insere_rest(cli,aux_1,aux_3,aux1,aux2);
				break;
				default:
				break;
			}
		 break;
		case 2:
			switch (n_restr){
				case 0:
				    cli->n_restr = n_restr;
				 break;
				case 1:
				    cli->n_restr = n_restr;
					cli=insere_rest(cli,aux_1,aux_3,aux1,aux2);		
			     break;
				case 2:
				    cli->n_restr = n_restr;	
					cli=insere_rest(cli,aux_1,aux_3,aux1,aux2);
				 break;
				default:
				 break;
			}
		  break;
		 default:
		  break;
	}
	return cli;
}

/*************************************************************************************
 * Function: insere_rest(cliente* cli, char* rest_0,char* rest_1, int car_0, int car_1)
 *
 * Arguments: cli (ponteiro para a estrutura cliente)
 * 			  rest_0 (string da restricao que se coloca na primeira posicao do vector de restricoes)
 * 			  rest_1 (string da restricao que se coloca na segunda posicao do vector de restricoes)
 * 			  car_0 (inteiro complementar a primeira restricao)
 * 			  car_1 (inteiro complementar a segunda restricao)
 *            
 * Returns: Estrutura cliente
 * 
 * Description: Funcao que insere as restricoes na estrutura cliente
 ************************************************************************************/
cliente* insere_rest(cliente* cli, char* rest_0,char* rest_1, 
int car_0, int car_1){
	switch(cli->n_restr){ 
		case 1:
		strcpy(cli->lista_rest[0].tipo,rest_0); /*tipo de restricao*/
		cli->lista_rest[0].def=car_0;           /*atributo da restricao*/
		break;
		case 2:
		strcpy(cli->lista_rest[0].tipo,rest_0);
		cli->lista_rest[0].def=car_0;
		strcpy(cli->lista_rest[1].tipo,rest_1);
		cli->lista_rest[1].def=car_1;
		break;
		default:
		break;
		}
 return(cli);	 
}
