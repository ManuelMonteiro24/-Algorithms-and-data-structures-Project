#ifndef ____utils__
#define ____utils__

#include <stdio.h>
#include "fila.h"
#include "restr.h"

char* converte_meio(int meio);
int find_fonte(int*st,int* wtmeio,int n_cidades,int cidade,FILE* fp_out);
int check_disp(cliente* cli,viagem*t,int tempo_v);
viagem* viagem_restr(viagem *t,cliente* cli,int restr_pref,int tempo_v);
int peso(cliente* cli,viagem* t,int tempo_v);
int peso_inv(cliente* cli,viagem* t,int tempo_v);
grafo* open_map(char* n_ficheiro_map);
void dijkstra (int *wt,int *wt0,int *wtmeio,int*st,grafo *G,cliente* cli,fila*queue);
void open_cli(char* n_ficheiro_cli,grafo *G,char* n_ficheiro_out);
#endif
