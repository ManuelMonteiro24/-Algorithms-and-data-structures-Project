#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restr.h"
#define SIZE 100
#define maxWT 91111
/******************************************************************************
 * Function: def_restr_a (cliente*cli)
 *
 * Arguments: cli (ponteiro para a estrutura que contem a informacao do cliente)
 *            
 * Returns: Informacao relativa a restricao A
 * 
 * Description: Atraves de comparacao, se existir restricao A retorna a informacao
 * 				associada a essa restricao. Caso contrario retorna -1
 *****************************************************************************/
int def_restr_a(cliente*cli){
	if((cli->n_restr)>0){	 
		if(cli->lista_rest[0].tipo[0]== 'A'){
			return (cli->lista_rest[0].def);	
		}else{
			return -1;
		}			
	}
	return -1;
}
/******************************************************************************
 * Function: def_restr_b (cliente*cli, int* def)
 *
 * Arguments: cli (ponteiro para a estrutura que contem a informacao do cliente)
 *            def (endero do inteiro que representa a restricao tempo ou custo, B)
 * 
 * Returns: Informacao relativa a restricao B
 * 
 * Description: Atraves de comparacao, se nao existir  restricao B retorna -1
 *              se existir retorno 1 ou 2 consoante se esta for unica (1) ou se tbm existir uma
 *              restricao A (2) e na varivael def vai estar o tipo de restricao 1 ou 2. 
 *****************************************************************************/
int def_restr_b(cliente*cli,int* def){
	switch(cli->n_restr){
		case 1:
		if(cli->lista_rest[0].tipo[0]== 'B'){
			if(cli->lista_rest[0].tipo[1]== '1'){
					*def=1;
				}else{
					*def=2;
				}
			return 1;	
			}else{
			return -1;
			}
		break;
		case 2:
			if(cli->lista_rest[1].tipo[1]== '1'){
					*def=1;
				}else{
					*def=2;
				}
			return 2;
		break;
		default:
			return -1;
		break;
	}
	return -1;
}

/******************************************************************************
 * Function: cmp_b (cliente*cli, int temp_total, int cust_total)
 *
 * Arguments: cli (ponteiro para a estrutura que contem a informacao do cliente)
 *            temp_total (tempo total da viagem)
 *            cust_total (custo total da viagem)
 * 
 * Returns: 1 se a condicao, em relacao a restricao se verificar e -1 caso contrario
 * 
 * Description: Atraves de comparacao do tempo ou custo total da viagem com 
 * 				restricao imposta pelo cliente, retorna 1 se o resultado do
 * 				programa for menor que a restricao imposta e -1 caso contrario
 *****************************************************************************/
int cmp_b(cliente*cli,int temp_total,int cust_total){
int i=0,def=0;
i=def_restr_b(cli,&def);
switch(i){
	case 1:
		switch(def){
			case 1:
				if(temp_total>(cli->lista_rest[0].def)){
					return-1;
					}else{
					return 1;	
					}
			 break;
			case 2:
				if(cust_total>(cli->lista_rest[0].def)){
					return-1;
					}else{
					return 1;	
					}
			 break;
			default:
			 break;  
		}
	 break;
	case 2:
		switch(def){
			case 1:
				if(temp_total>(cli->lista_rest[1].def)){
					return-1;
					}else{
					return 1;	
					}
			 break;
			case 2:
				if(cust_total>(cli->lista_rest[1].def)){
					return-1;
					}else{
					return 1;	
					}
			 break;
			default:
			 break;  
		}
	 break;
	default:
	 return 1;
	 break;  
	}
	printf("ERROR B");
	return 3;
}					

/******************************************************************************
 * Function: check_restr_a (viagem* t_aux, int restr_pref, cliente *cli)
 *
 * Arguments: t_aux (ponteiro para a estrutura viagem em analise) 
 * 			  restr_pref (atributo da restricao A, senao existir restricao A este e -1)
 * 			  cli (ponteiro para a estrutura que contem a informacao do cliente)
 *            
 * Returns: 1 se a condicao se verificar e -1 caso contrario
 * 
 * Description: Funcao que compara a ligacao com a restricao A, se existir.
 * 				Retorna -1 caso a viagem seja restringida, caso contrario 
 *              retorna 1 (e tbm se nao houver restricao A).
 *****************************************************************************/
int check_restr_a(viagem* t_aux,int restr_pref,cliente *cli){
	if(restr_pref==-1){
	return 1;
	}	
	switch(cli->lista_rest[0].tipo[1]){
		case '1':
			if((t_aux->meio)==restr_pref){
			return -1;
			}else{
			return 1;
			}
		break;
		case '2':
			if((t_aux->duracao)>restr_pref){
			return -1;
			}else{
			return 1;
			}
		break;
		case '3':
			if((t_aux->custo)>restr_pref){
			return -1;
			}else{
			return 1;
			}
		break;
		default:
		break;	
	}
printf("Erro: restricoes");	
 return 1;	
}	
