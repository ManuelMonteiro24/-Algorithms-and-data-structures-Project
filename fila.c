#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"

/******************************************************************************
 * Function: menor(int a, int b)
 *
 * Arguments: a (valor inteiro)
 * 			  b (valor inteiro)
 *            
 * Returns: 1 ou 0
 * 
 * Description: Compara os dois valores introduzidos na funcao e se a for maior
 * 				que b retorna 1, caso contrario retorna 0
 ********************************************************************************/
int maior(int a, int b){

  return (a > b);
}
/******************************************************************************
 * Function: PQinit (int tamanho)
 *
 * Arguments: tamanho (inteiro que define o tamanho da fila)
 *            
 * Returns: Fila de prioridade (do tipo acervo)
 * 
 * Description: inicializacao da fila de prioridade com o tamanho que
 * 				recebe nos argumentos,nesta fila a prioridade e o menor peso
 ********************************************************************************/
fila* PQinit(int tamanho){
	vert *lig= NULL;
	fila *queue = NULL;
	int i =0;
	queue = (fila*)malloc(sizeof(struct fila));
	if(queue ==NULL){ /*alocacao da estrutura fila*/
		printf("erro na fila");
		exit(-5);
	}
	lig = (vert*)malloc((tamanho)*sizeof(struct vert));
	if(lig==NULL){ /*alocacao do vector do acervo*/
		printf("erro nosaasdsd vertices");
		exit(-5);
	}
	for(i=0;i<tamanho;i++){
	lig[i].ind=0;       /*preenchimento do do acervo todo a 0s, nos indices e nos pesos*/
	lig[i].peso=0;	
	}
	queue->vect_fila = lig;
	queue->size= tamanho;
	queue->elementos = 0; /*numero de elemetos da fila comeca a 0*/
	return queue;
	}

/*************************************************************************************
 * Function: fixup (fila* queue, int a)
 *
 * Arguments: queue (fila que recebe)
 * 			  a (indice do elemento do acervo a qual se vai aplicar a organizacao)
 *            
 * Returns: none
 * 
 * Description: Funcao que ordena de baixo para cima o acervo de acordo
 * 				com prioridade 
 ************************************************************************************/
void fixup(fila* queue, int a){
	vert aux;
	while( (a>0) && 1==(maior(queue->vect_fila[(a-1)/2].peso
	,queue->vect_fila[a].peso))){  /*enquanto houver elementos a analisar e o peso do pai for maior do que fo filho*/
		aux=queue->vect_fila[a];  /*o filho vai trocar de lugar com o pai */
		queue->vect_fila[a]=queue->vect_fila[(a-1)/2];/*caso contrario o acervo esta correctamento ordenado*/
		queue->vect_fila[(a-1)/2] = aux;
		a = (a-1)/2;
		}
	return;	
}
/*************************************************************************************
 * Function: fixdown (fila* queue, int a)
 *
 * Arguments: queue (fila que recebe)
 * 			  a (indice do elemento do acervo a qual se vai aplicar a organizacao)
 *            
 * Returns: none
 * 
 * Description: Funcao que ordena o acervo de cima para baixo  de acordo
 * 				com a prioridade dos elementos 
 ************************************************************************************/
void fixdown(fila*queue, int a){
	int child;
	vert aux;
	while((2*a+1)<(queue->elementos)){
	child = 2*a+1; 
	if((child+1) < (queue->elementos) && 1==maior(queue->vect_fila[child].peso,
	queue->vect_fila[child+1].peso)) child++; /*segundo filho e maior*/
	if(!maior(queue->vect_fila[a].peso,queue->vect_fila[child].peso)) break; /*elementos estao na ordem correcta*/
		aux=queue->vect_fila[a]; /*ordenacao dos elementos pois nao estao na ordem correcto*/
		queue->vect_fila[a]=queue->vect_fila[child];
		queue->vect_fila[child] = aux;
		a=child;
		
	}
	return;
}			

/*************************************************************************************
 * Function: PQinsert (fila* queue, int verti, int peso)
 *
 * Arguments: queue (fila que recebe)
 * 			  verti (numero do vertice que pretendemos inserir)
 * 			  peso (peso do vertice que pretendemos inserir)
 *            
 * Returns: none
 * 
 * Description: Funcao que acrescenta um novo elemento no acervo
 ************************************************************************************/
void PQinsert(fila* queue,int verti,int peso){
	    if(queue->elementos==queue->size){
			return; /*caso o acervo estiver cheio*/
		}
	    queue->vect_fila[(queue->elementos)].ind = verti;
	    queue->vect_fila[verti].peso = peso;
	    queue->elementos++; 
		fixup(queue,(queue->elementos-1)); /*reordenacao do acervo*/
	return;		
	}

/*************************************************************************************
 * Function: PQdelmax (fila* queue)
 *
 * Arguments: queue (fila que recebe)
 *            
 * Returns: indice do Vertice removido
 * 
 * Description: remove o elemento da fila de maior prioridade e retorna-o
 ************************************************************************************/
int PQdelmax(fila*queue){
	vert aux, aux1;
	if(queue->elementos>0){
		aux1=queue->vect_fila[0]; /*troca do primeiro elemento com o ultimo*/
		aux=queue->vect_fila[(queue->elementos)-1];
		queue->vect_fila[(queue->elementos)-1]=queue->vect_fila[0];
		queue->vect_fila[0] = aux;
		(queue->elementos)--; /*decremento o numero de elementos*/
		fixdown(queue,0);     /*reordena o acervo*/
		return (aux1.ind);
	}
	return -1;	
}	

/*************************************************************************************
 * Function: liberta_fila (fila* queue)
 *
 * Arguments: queue (fila que recebe)
 *            
 * Returns: none
 * 
 * Description: Funcao que liberta a fila
 ************************************************************************************/
void liberta_fila(fila* queue){
	free(queue->vect_fila);
	free(queue);
	return;
}

/*************************************************************************************
 * Function: procura_v(fila* queue, int origem)
 *
 * Arguments: queue (fila que recebe)
 * 			  origem (inteiro que representa o indice a procurar)
 *            
 * Returns: indice do vector do acervo onde a cidade se encontra ou -1 se nao encontrar
 * 
 * Description: Funcao que recebe o inteiro que representa a cidade a procurar e retorna
 * 				o indice da fila onde a cidade se encontra
 *  *********************************************************************************/
int procura_v(fila* queue, int origem){
	int i=0;
	for(i=0;i<(queue->elementos);i++){
		if((queue->vect_fila[i].ind) == origem){
		return i;		
		}	
	}
	return -1;
}
