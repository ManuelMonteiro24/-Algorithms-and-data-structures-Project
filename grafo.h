#ifndef ____grafo__
#define ____grafo__

#include <stdio.h>
#define SIZE 100

/******************************************************************************
 * Type: Estrutura viagem
 *
 * Elements: inteiro que representa a cidade destino
 * 			 inteiro que representa o meio de transporte
 * 			 inteiro correspondente a duracao da viagem na ligacao
 * 			 inteiro correspondente ao custo da viagem na ligacao
 * 			 inteiro correspondente a primeira hora de saida do transporte
 * 			 inteiro correspondente a hora em que nao saem mais transportes
 * 			 inteiro correspondente a frequencia de saida do transporte
 * 			 ponteiro para a estrutura seguinte 			
 * 
 * Description: Estrutura com todas as caracteristicas incluidas na ligação
 * 				entre duas cidades 
 *****************************************************************************/

typedef struct viagem {
	int destino;
	int meio;
	int duracao;
	int custo;
	int ti;
	int tf;
	int periocidade;
	struct viagem* seg;
} viagem;

/******************************************************************************
 * Type: Estrutura grafo
 *
 * Elements: inteiro que representa os nós do grafo
 * 			 inteiro que representa as ligacoes do grafo
 * 			 vector de listas		
 * 
 * Description: Estrutura do grafo
 *****************************************************************************/

typedef struct grafo {
	int nodes;
	int links;
	struct viagem** vect_listas; 
} grafo;

grafo * addligacao(grafo *G,viagem *aux_0,int inic);
grafo* ini_grafo(int nt_cidades, int nt_ligacoes);
void insere_grafo(char *p_linha,grafo *G);
void destroi_grafo(grafo *G);
void print_grafo(grafo *G);
int cmp_meios(char* aux);

#endif
