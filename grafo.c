#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#define SIZE 100

/******************************************************************************
 * Function: ini_grafo(int nt_cidades, int nt_ligacoes)
 *
 * Arguments: nt_cidades (representa o numero de cidades do mapa)
 * 			  nt_ligacoes (representa o numero de ligacoes do mapa)
 *
 * Returns: o grafo, apenas com o numero de cidades e ligacoes
 * 			do mapa. O vector de listas de adjacencia vai estar vazio
 *
 * Side-Effects: none
 *
 * Description: alocacao de memoria necessaria para o grafo, de acordo com
 * 				o numero de cidades existentes
 *****************************************************************************/
grafo* ini_grafo(int nt_cidades, int nt_ligacoes){
	viagem **fonte = NULL;
	grafo *G = NULL;
	int i;
	fonte=(viagem **)malloc((nt_cidades)*sizeof(viagem*));
	if(fonte==NULL){ /*alocacao vector de listas*/
		printf("\n erro: vector de listas \n");
		exit(-1);
	}
	G =(grafo*)malloc(sizeof(struct grafo));
	if (G==NULL){ 
		printf("\n erro: alocacao do grafo \n");
		exit(-1);
	}
	
	G->nodes = nt_cidades;
	G->links = nt_ligacoes;
	G->vect_listas = fonte;
	for(i=0;i<nt_cidades;i++){
		G->vect_listas[i]= NULL;
	}
	
	return G;
}

/******************************************************************************
 * Function: addligacao(grafo *G,viagem *aux_0,int inic)
 *
 * Arguments: G (grafo onde vao ser inseridas a ligacoes lidas)
 * 			  aux_0 (ligacao a ser inserida)
 *            inic (cidade origem da ligacao)
 *
 * Returns: o grafo com a ligacao já inserida
 * 
 * Description: vai inserir a ligacao lida no grafo ordenadamente de acordo
 * 				com a cidade destino, para isso deferencia-se o caso de inserir
 * 				no inicio, no meio ou no fim
 *****************************************************************************/
grafo * addligacao(grafo *G,viagem *aux_0,int inic){
	viagem *aux = NULL,*aux1 = NULL;
	aux = G->vect_listas[(inic-1)];
	aux1 = aux;
	if (G->vect_listas[(inic-1)] == NULL){
	G->vect_listas[(inic-1)]= aux_0; /*caso ainda nao exista nenhuma ligacao associada a cidade*/
	return G;
	} 
	while(aux != NULL){
		if((aux_0->destino)<(aux->destino)){
			if (aux == G->vect_listas[(inic-1)]){
				aux_0->seg = aux; /*caso a ligacao inserida seja na primeira posicao da lista*/
				G->vect_listas[(inic-1)] = aux_0;
				return G;
			}else{
			aux_0->seg = aux; /*ligacao inserida no meio da lista*/
			aux1->seg = aux_0;
			return G;
			}
		}
		aux1 = aux; /*ligacao inserida no final da  lista*/
		aux = aux->seg;
		if(aux == NULL){
		aux1->seg = aux_0;
		return G;
		}
	}
	return G;
}

/******************************************************************************************
 * Function: insere_grafo(char *p_linha,grafo *G)
 *
 * Arguments: p_linha (linha do ficheiro .map onde se vai retirar os atributos da ligacao)
 * 			  G (grafo onde sera inserida a ligacao)
 *            
 * Returns: o grafo com as ligacoes já inseridas
 * 
 * Description: a funcao aloca 2 estruturas do tipo viagem e retira
 * 				da linha os atributos da ligacao. De seguida vai inserir os atributos
 * 				nas estruturas criadas e por fim, inserir as estruturas no grafo chamando a funcao
 *              addligacao.
 *****************************************************************************************/
void insere_grafo(char *p_linha,grafo *G){
		int inic = 0;
		char auxiliar[SIZE];
		int o=0;
		viagem *aux_0= NULL,*aux_1=NULL;
		
	    aux_0 = (viagem*)malloc(sizeof(viagem));
	    aux_1 = (viagem*)malloc(sizeof(viagem));
	    if(aux_0==NULL){
			printf("erro viagem");
			exit(-2);
		}
		if(aux_1==NULL){
			printf("erro viagem");
			exit(-2);
		}
	    aux_0->seg = NULL;
	    aux_1->seg = NULL;
		
		sscanf(p_linha, "%d %d %s %d %d %d %d %d", &inic, 
		&(aux_0->destino),auxiliar, &(aux_0->duracao), 
		&(aux_0->custo), &(aux_0->ti),&(aux_0->tf), 
		&(aux_0->periocidade));
		o =cmp_meios(auxiliar);
		aux_0->meio= o;

		aux_1->destino = inic; 
		aux_1->meio = aux_0->meio;
		aux_1->duracao = aux_0->duracao;
		aux_1->custo = aux_0->custo;
		aux_1->ti = aux_0->ti;
		aux_1->tf = aux_0->tf;
		aux_1->periocidade = aux_0->periocidade;
		
		G = addligacao(G,aux_0,inic);
		
		G = addligacao(G,aux_1,(aux_0->destino));
}
/******************************************************************************
 * Function: destroi_grafo(grafo *G)
 *
 * Arguments: G(estrutura grafo que sera libertada)
 *            
 * Returns: none
 * 
 * Description: liberta a memoria alocada para estrutura.
 * 				Primeiro liberta a parte correspondente ao vector de listas de
 * 				adjacencia e por fim a estrutura grafo
 *****************************************************************************/
void destroi_grafo(grafo *G){
	int i=0;
	viagem *aux=NULL, *aux_0=NULL;
	
	for(i=0; i< (G->nodes);i++){ 
		aux= G->vect_listas[i];
		aux_0 = aux;
		while(aux!=NULL){
			aux = aux->seg;
			free(aux_0);
			aux_0= aux;
		}
	}
	free(G->vect_listas);
	free(G);	
}
/******************************************************************************
 * Function: cmp_meios(char* aux)
 *
 * Arguments: aux (string que contem o meio de transporte da ligacao)
 *            
 * Returns: int (o numero correspondente a cada tipo de ligacao)
 * 
 * Description: a funcao vai comparar a string com os diferentes meio e depois
 * 				vai retornar o meio de transporte correspondente em numero
 * 				0->autocarro
 * 				1->comboio
 * 				2->aviao
 * 				3->barco
 *****************************************************************************/
int cmp_meios(char* aux){
	int ori=0;
	
	switch(aux[1]){
		case'o':
		ori=1;
		 break;
		case'v':
		ori=2;
		 break;
		case'u':
		ori=0;
		 break;
		case'a':
		ori=3;
		 break;
		default:
		 break;
	}	
	return (ori);	
}	
