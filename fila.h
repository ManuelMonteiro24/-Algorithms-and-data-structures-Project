#ifndef ____fila__
#define ____fila__

#include <stdio.h>

/******************************************************************************
 * Type: Estrutura fila
 *
 * Elements: inteiro que define o tamanho da fila
 * 			 inteiro que representa o numero de elementos na fila
 * 			 vector de vertices			
 * 
 * Description: Estrutura com a informacao relativa a fila
 *****************************************************************************/
typedef struct fila{
	int size;
	int elementos;
	struct vert *vect_fila;
} fila;

/******************************************************************************
 * Type: Estrutura vert
 *
 * Elements: inteiro que representa o indice do vertice
 * 			 inteiro que representa o peso do vertice		
 * 
 * Description: Estrutura com a informacao relativa ao vertice
 *****************************************************************************/
typedef struct vert{
	int ind;
	int peso;
} vert;

void print_fila(fila* queue);
void liberta_fila(fila* queue);
int PQdelmax(fila*queue);
void PQinsert(fila* queue,int verti,int peso);
void fixdown(fila*queue, int a);
void fixup(fila* queue, int a);
fila* PQinit(int tamanho);
int maior(int a, int b);
int procura_v(fila* queue, int origem);
#endif
