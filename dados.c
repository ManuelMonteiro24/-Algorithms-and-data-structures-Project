#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
#include "utils.h"

int main(int argc,  const char* argv[]){
    char *n_ficheiro_map, *n_ficheiro_cli, *n_ficheiro_out;
    grafo *G=NULL;
   
    if (argc != 3){ printf("entrada mal declarada");
		exit(-1); /*caso a linha de comando for mal declarada*/
		}
    n_ficheiro_map = (char *) malloc((strlen(argv[1])+1)*sizeof(char));
    n_ficheiro_cli = (char *) malloc((strlen(argv[2])+1)*sizeof(char));
    n_ficheiro_out = (char *) malloc((strlen(argv[2])+1)*sizeof(char));        
    strcpy(n_ficheiro_map, argv[1]);
    strcpy(n_ficheiro_cli, argv[2]);
    /*criacao duas string uma com o nome do ficheiro mapa outra com */
    /*o nome do ficheiro cliente, que vao ser usadas na abertura destes*/
	/*dois ficheiros*/
	G = open_map(n_ficheiro_map);
	
    open_cli(n_ficheiro_cli,G,n_ficheiro_out);	
    
	destroi_grafo(G);
    free(n_ficheiro_map);
    free(n_ficheiro_cli);
    free(n_ficheiro_out);
    exit(0);
}
