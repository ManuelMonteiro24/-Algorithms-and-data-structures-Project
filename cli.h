#ifndef ____cli__
#define ____cli__

#include <stdio.h>
#include "grafo.h"
#define SIZE 100

/******************************************************************************
 * Type: Estrutura cliente
 *
 * Elements: inteiro que representa a cidade de partida
 * 			 inteiro que representa a cidade de chegada
 * 			 inteiro correspondente a disponibilidade do cliente
 * 			 inteiro correspondente a preferencia (tempo ou custo)
 * 			 inteiro correspondente ao numero de restricoes do cliente
 * 			 vector das restricoes 			
 * 
 * Description: Estrutura com todas as caracteristicas impostas pelo cliente 
 *****************************************************************************/
typedef struct cliente{
	int origem;
	int destino;
	int disp;
	int t_rota; /*0->tempo 1->custo*/
	int n_restr;
	struct restr* lista_rest;
	
}cliente;

/******************************************************************************
 * Type: Estrutura restr
 *
 * Elements: string que representa o tipo de restricao (A1, A2, A3, B1, B2)
 * 			 inteiro que completa a informacao relativa a restricao 			
 * 
 * Description: Estrutura com a informacao relativa a restricao
 *****************************************************************************/
typedef struct restr{
	char tipo [SIZE];
	int def;  /*no A1, 0->autocarro 1->comboio 2->aviao 3->barco*/
}restr;

void print_cliente(cliente*cli);
void free_cliente(cliente*cli);
cliente* insere_rest(cliente* cli, char* rest_0,char* rest_1, 
int car_0, int car_1);
cliente* ini_cliente(int origem, int destino, int disp, char* t_rota,
int n_restr);
cliente* cli_seg(cliente* cli,int origem, int destino, int disp, char* t_rota,
int n_restr,char* aux_1, char* aux_2, char* aux_3,char* aux_4);

#endif
