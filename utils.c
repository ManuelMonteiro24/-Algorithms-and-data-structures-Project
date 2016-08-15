#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#define SIZE 100
#define maxWT 91111

/*************************************************************************************
 * Function: int find_fonte(int*st,int* wtmeio,int n_cidades,int cidade,FILE* fp_out)
 *
 * Arguments: st (vector short tree)
 * 			  wtmeio (vector de transportes)
 * 			  n_cidades (numero de cidades)
 * 			  cidade (cidade de destino)
 * 			  fp_out (ficheiro de saida)
 *            
 * Returns: inteiro que representa as cidades
 * 
 * Description: Funcao recursiva. Imprime as cidades do caminho optimo (desde a partida
 * 				ate a chegada), intercalado com os transportes das ligacoes entre as 
 * 				cidades.
 ************************************************************************************/
int find_fonte(int*st,int* wtmeio,int n_cidades,int cidade,FILE* fp_out){	
	char transporte [SIZE];
	if(st[cidade]!=-1){ /*enquanto nao encontrar a fonte (-1) a funcao continua a chamar-se a si mesma*/
	find_fonte(st, wtmeio, n_cidades,st[cidade],fp_out); 	
	}
	if(wtmeio[cidade]!=91111){ /*descodificacao do tipo de transporte de inteiro para string*/
		switch(wtmeio[cidade]){
			case 0:
				strcpy(transporte,"autocarro");
			 break;
			case 1:
				strcpy(transporte,"comboio");
			 break;
			case 2:
				strcpy(transporte,"aviao");
			 break;
			case 3:
				strcpy(transporte,"barco");
			 break;
			default:
			 break;
		}	
	fprintf(fp_out,"%s ",transporte);	
	}	 /*Impressao das cidades que constituem a rota e dos respectivos meios que as ligam*/
	fprintf(fp_out,"%d ",cidade+1);	/*no ficheiro de saida*/
	return cidade; 
}	

/*************************************************************************************
 * Function: check_disp(cliente* cli,viagem*t,int tempo_v)
 *
 * Arguments: cli (estrutura que contem a informacao do cliente)
 * 			  t (ligacao que se analisa)
 * 			  tempo_v (tempo actual (na cidade onde se esta a analisar)
 *            
 * Returns: inteiro que corresponde ao tempo de duracao da ligacao ou -1 em caso de erro
 * 
 * Description: Funcao que calcula o tempo de viagem entre cidades
 ************************************************************************************/
int check_disp(cliente* cli,viagem*t,int tempo_v){
	int i=0,mult=0; /*variavel multiplicidade representa o dias passados*/
	if(tempo_v==0){ /*se o tempo actual for 0 (primeira cidade a analisar)entao o tempo_v*/
	tempo_v=cli->disp; /*e igual a disponibilidade do cliente*/
	}
	while(mult!=99999){
		if(tempo_v<=((mult*1440)+(t->ti))){ /*caso o tempo actual seja inferior à primeira partida do transporte*/
			if(tempo_v==cli->disp){ /*caso seja a primeira cidade nao se subtrai o tempo actual*/
					return (((t->ti)+(mult*1440))+(t->duracao)); 
			}	
			return ((t->ti)+(mult*1440)+t->duracao-tempo_v);
		} 	
		i=t->ti;
		while(i<=(t->tf)){ /*caso o tempo actual esteja entre o tempo inicial e tempo final de partidas*/
			if(tempo_v<=(i+(mult*1440))){
				if(tempo_v==cli->disp){
				return (mult*1440)+i+t->duracao;	
				}	
				return ((mult*1440)+i+t->duracao-tempo_v);		
			}
		i=i+(t->periocidade); 
		}
	mult=mult+1; /*incremento dos dias*/
	}
printf("Erro: TEMPO\n");	
 return -1;	
}

/*************************************************************************************
 * Function: viagem_restr(viagem *t,cliente* cli,int restr_pref,int tempo_v)
 *
 * Arguments: t (ligacao que se analisa)
 * 			  cli (estrutura que contem a informacao do cliente)
 * 			  restr_pref (complementar da restricao)
 *  		  tempo_v (tempo actual (na cidade onde se esta a analisar))
 *            
 * Returns: melhor ligacao entre duas cidades
 * 
 * Description: Analisa todas as ligacoes entre duas cidades e retorna a ligacao de
 * 				menor custo
 ************************************************************************************/
viagem* viagem_restr(viagem *t,cliente* cli,int restr_pref,int tempo_v){
	int flag_restr=0; /*se a flag estiver a 1 entao a ligacao esta restringida caso contrario esta a 0*/
	viagem *t_aux= NULL,*t_aux0= NULL;
	int best=91111,best_aux=91111; /*variaveis usadas para comparar o melhor custo e tempo entre ligacoes*/
	int j=0; 
	t_aux=t;
	while(t_aux!=NULL){ 
		if(t_aux->destino!=t->destino){
			return t_aux0; /*quando o destino passa a ser diferente do destino da ligacao*/
		}                  /*t a melhor ligacao t_aux e retornada*/
		if(cli->t_rota==1){ /*preferencia custo*/
			flag_restr = check_restr_a(t_aux,restr_pref,cli); /*analise das restricoes A*/
			j=check_disp(cli,t_aux,tempo_v); /*tempo de espera para apanhar o transporte + duracao da viagem*/
			if((t_aux->custo)<best && 1==flag_restr){ /*comparacao de custos*/
				t_aux0=t_aux;
				best=t_aux0->custo;
				best_aux = j;
			}else{ /*se os custos forem iguais para o mesmo destino vai se analisar os tempos*/
				if((t_aux->custo)==best && 1==flag_restr){
					if(j<=best_aux && 1==flag_restr){
						t_aux0=t_aux;
						best_aux=j;
					}	
				}
			}		
		}else{ /*preferencia tempo(mesmo metodo do que para o custo)*/
			flag_restr = check_restr_a(t_aux,restr_pref,cli);
			j=check_disp(cli,t_aux,tempo_v);
			if(j<best && 1==flag_restr){
				t_aux0=t_aux;
			    best=j;
				best_aux=t_aux0->custo;
			}else{
				if(j==best && 1==flag_restr){
					if((t_aux->custo)<=best_aux && 1==flag_restr){
						t_aux0=t_aux;
						best_aux=t_aux0->custo;
					}
				}
			}	
		}
	t_aux=t_aux->seg;			
	}
 return t_aux0;			
}

/*************************************************************************************
 * Function: dijkstra (int *wt,int *wt0,int *wtmeio,int*st,grafo *G,cliente* cli,fila*queue)
 *
 * Arguments: wt (vector dos pesos)
 * 			  wt0 (vector secundario dos pesos)
 * 			  wtmeio (vector dos meios de transporte)
 *  		  st (vector short tree)
 *            G (grafo)
 * 			  cli (estrutura que contem a informacao do cliente)
 * 			  queue (fila que recebe)
 * 
 * Returns: none
 * 
 * Description: Funcao que analisa o grafo e que gera o melhor caminho de acordo com as
 * 				preferencias e restricoes da cidade de origem a todas as outras
 ************************************************************************************/
void dijkstra (int *wt,int *wt0,int *wtmeio,int*st,grafo *G,cliente* cli,fila*queue){
	int v=0,w=0;
	int restr_pref=0;
	viagem* t = NULL,*aux_check=NULL;

	int z=0,flag=0; /*variavel z e igualada ao tempo em que se chega a ciadade em analise*/
	
	restr_pref=def_restr_a(cli); 	
	queue->elementos=0;	/*nova utilizacao do acervo, comeca-se sempre com 0 elementos*/
	for(v=0;v<G->nodes;v++){ 
		st[v] = -1;      /*preenchimento do acervo,st,wt e vectores auxiliares*/
		wt[v] = maxWT;
		wt0[v] = maxWT;
		wtmeio[v] = maxWT;
		PQinsert(queue,v,maxWT);
		}
	wt[(cli->origem)-1] = 0; /*o vertice fonte e o primeiro a ser analisado*/
	wt0[(cli->origem)-1] = 0; /*o seu peso comeca a 0 nos vectores do peso e no acervo*/
	v= procura_v(queue,((cli->origem)-1));
    queue->vect_fila[v].peso = 0;
	fixup(queue,v);
	
	while(queue->elementos != 0){ /*enquanto houver elementos no acervo*/
		v= PQdelmax(queue); /*remocao do primeiro elemento da fila (maior prioridade), ultilizacao do seu indice*/
		if(wt[v]!= maxWT){  /*se esse vertice ainda nao tiver sido analisado*/
			if(cli->t_rota==1){ /*se a preferencia for custo o vector wt0 vai conter os tempos*/
					z=wt0[v];   /*caso contrario os tempos vao estar no vector wt*/ 
				}else{
					z=wt[v];	
				}
				flag=0; /*flag usada passar saber se um determinado destino ja foi analisado*/
			for(t=G->vect_listas[v];t!=NULL;t=t->seg){
				if(flag!=t->destino){ /
				aux_check = viagem_restr(t, cli, restr_pref,z); 
				}
					 w=((t->destino)-1); /*quando a ligacao em analise for igual a melhor ligacao entre essas duas cidades*/
					if((wt[w]>(wt[v]+(peso(cli,t,wt[v])))) && t==aux_check){ /*e o peso desse destino for menor do que a soma*/
						wt[w]=wt[v]+(peso(cli,t,wt[v]));             /*do peso da origem + o custo ou o tempo(consoante preferencia) da viagem*/
						wt0[w]=wt0[v]+peso_inv(cli,t,wt0[v]);        /*ai se igualar o peso do vertice destino a soma anteriormente menciondada*/
						wtmeio[w]=t->meio;
						queue->vect_fila[procura_v(queue,w)].peso = wt[w]; /*no acervo encontra-se o vertice com o indice da cidade destino*/
						fixup(queue,procura_v(queue,w));                   /*e tbm se iguala o seu peso a soma anterior,seguido de um fixup para ordenar-lo*/
						st[w] = v;       /*actualizacao da SPT*/
					}
					flag=t->destino;   
				}
			}		
		}
}	

/*************************************************************************************
 * Function: peso(cliente* cli,viagem* t,int tempo_v)
 *
 * Arguments: cli (estrutura que contem a informacao do cliente)
 * 			  t (ligacao que se analisa)
 * 			  tempo_v (tempo actual (na cidade onde se esta a analisar))
 * 
 * Returns: Preco ou tempo
 * 
 * Description: Funcao que analisa a opcao do cliente e retorna o custo se a opcao
 * 				escolhida for o preco e tempo caso contrario
 ************************************************************************************/
int peso(cliente* cli,viagem* t,int tempo_v){
	if(cli->t_rota==1){ /*de acordo que a preferencia do cliente retorna o custo ou o tempo de uma ligacao*/
					return t->custo;
					}else{
					return check_disp(cli,t,tempo_v);
					}
}

/*************************************************************************************
 * Function: peso(cliente* cli,viagem* t,int tempo_v)
 *
 * Arguments: cli (estrutura que contem a informacao do cliente)
 * 			  t (ligacao que se analisa)
 * 			  tempo_v (tempo actual (na cidade onde se esta a analisar))
 * 
 * Returns: Preco ou tempo
 * 
 * Description: Funcao que analisa a opcao do cliente e retorna o custo se a opcao
 * 				escolhida for o tempo e tempo caso contrario
 ************************************************************************************/
int peso_inv(cliente* cli,viagem* t,int tempo_v){
	if(cli->t_rota==0){
					return t->custo; /*se a preferencia for tempo retorna o custo vice-versa*/
					}else{
					return check_disp(cli,t,tempo_v);
					}
}

/*************************************************************************************
 * Function: open_cli(char* n_ficheiro_cli,grafo *G,char* n_ficheiro_out)
 *
 * Arguments: n_ficheiro_cli (nome do ficheiro cliente)
 * 			  G (grafo)
 * 			  n_ficheiro_out (nome do ficheiro de saida)
 * 
 * Returns: none
 * 
 * Description: Retira a informacao do ficheiro do cliente, analisa a informacao atraves
 * 				das funcoes anteriores e escreve a informacao de saida num ficheiro
 ************************************************************************************/
void open_cli(char* n_ficheiro_cli,grafo *G,char* n_ficheiro_out){
	FILE *fp_cli=NULL,*fp_out=NULL;
	char p_linha [SIZE],aux_0 [SIZE],aux_1 [SIZE]
	,aux_2 [SIZE],aux_3 [SIZE],aux_4 [SIZE];
	int i=0, nt_clientes=0, aux=0,aux1=0,aux2=0, dest=0, ori=0,disp=0,rest=0;
	int flag_cli=0,j=0,j_0=0,j_1=0;
	cliente *cli=NULL;
	fila*queue= NULL;
	int *st=NULL,*wt=NULL,*wt0=NULL,*wtmeio=NULL;
	
	fp_cli = fopen(n_ficheiro_cli,"r");
		if(fp_cli==NULL){
			printf("\n nah ficheiro .cliente \n");
			exit(-1);
		}	
	i=strlen(n_ficheiro_cli); /*utilizacao do nome do ficheiro cliente para gerar o ficheiro de saida*/
    n_ficheiro_cli[i-4] = '\0';
    strcpy(n_ficheiro_out,n_ficheiro_cli);
    strcat(n_ficheiro_out, ".sol");	
	
	fp_out = fopen(n_ficheiro_out, "w");
		if(fp_out==NULL){
			printf("\n nao ha ficheiro .map \n");
			exit(-1);
		}
	wt = (int*)malloc((G->nodes) * sizeof(int)); 
	wt0 = (int*)malloc((G->nodes) * sizeof(int));
	wtmeio = (int*)malloc((G->nodes) * sizeof(int));
	st = (int*)malloc((G->nodes) * sizeof(int));
			
	queue = PQinit(G->nodes);
		
	if(fgets(p_linha,SIZE,fp_cli)!=NULL){ /*ler a primeira linha, numero de clientes*/
	sscanf(p_linha,"%d",&nt_clientes);
	}else{
	printf("erro scanf");	
	exit(-4);	
	}
	
	i=1;
	while(fgets(p_linha,SIZE,fp_cli)!=NULL){ /*ler o resto das linhas*/
		sscanf(p_linha,"%d %d %d %d %s %d %s %s %s %s",&aux,&ori,&dest,&disp
		,aux_0,&rest,aux_1,aux_2,aux_3,aux_4);
		if(flag_cli==0){ /*caso seja a primeira linha de cliente lida*/
			flag_cli=1;	
			cli=ini_cliente(ori,dest,disp,aux_0,rest);
		if(rest>0){ 
			if(strcmp(aux_1,"A1")==0){ /*caso restricao A1 onde e preciso fazer a conversao de string para int*/
					aux1 =cmp_meios(aux_2);	
					if(rest==2){		
						aux2 =atoi(aux_4);
					}	
			}else{
					aux1= atoi(aux_2);
					if(rest==2){		
						aux2 =atoi(aux_4);
				}
			}
		}	
			cli=insere_rest(cli,aux_1,aux_3,aux1,aux2); /*insercao das restricoes na estrutura cliente*/
		}else{                                  /*linhas de cliente seguintes*/
		cli=cli_seg(cli,ori,dest,disp,aux_0,rest,aux_1,aux_2,aux_3,aux_4);	
		}                                      
			dijkstra (wt,wt0,wtmeio,st,G,cli,queue);
			
            if(cli->t_rota==1){
				j_1=wt[((cli->destino)-1)]; /*custo total*/
				j_0=(wt0[((cli->destino)-1)]-cli->disp); /*tempo total*/
			}else{                 /*contrario da condicao de cima*/
				j_1=wt0[((cli->destino)-1)]; 
				j_0=(wt[((cli->destino)-1)]-cli->disp);	
			}
			
            j=cmp_b(cli,j_0,j_1); /*verificacao das restricoes B*/
            fprintf(fp_out,"%d ",i); /*impressao do numero de cliente no ficheiro de saida*/
            
            if(j==-1 || st[cli->destino-1]==-1){
				fprintf(fp_out,"-1"); /*caso nao houver ligacao possivel */
			}else{
				find_fonte(st,wtmeio,G->nodes,(cli->destino-1),fp_out);	/*impressao da rota no ficheiro de saida*/
				fprintf(fp_out,"%d ",j_0); /*impressao tempo e custo total no ficheiro de saida*/
				fprintf(fp_out,"%d",j_1);
			}
			
			fprintf(fp_out,"\n");
			i++; /*incremento do numero de cliente*/
			}
	liberta_fila(queue);		
	free_cliente(cli);		
	fclose(fp_cli);
	fclose(fp_out);
	free(wt);
	free(st);
	free(wt0);
	free(wtmeio);
}

/*************************************************************************************
 * Function: open_map(char* n_ficheiro_map)
 *
 * Arguments: n_ficheiro_map (nome do ficheiro mapa)
 * 
 * Returns: Grafo
 * 
 * Description: Funcao que recebe o ficheiro com o mapa e constroi o grafo a partir
 * 				das informacoes recolhidas
 ************************************************************************************/
grafo* open_map(char* n_ficheiro_map){
	
	FILE *fp_map=NULL;
	char p_linha [SIZE];
	int nt_ligacoes=0, nt_cidades=0;
    grafo *G=NULL;
	
	fp_map = fopen(n_ficheiro_map,"r");
		if(fp_map==NULL){
			printf("\n nah ficheiro .map \n");
			exit(-1);
		}
		
	if(fgets(p_linha,SIZE,fp_map)!=NULL){ /*ler a primeira linha ,cidades e ligacoes*/
	sscanf(p_linha,"%d %d",&nt_cidades,&nt_ligacoes);
	}
	G = ini_grafo(nt_cidades, nt_ligacoes);
	
	while(fgets(p_linha,SIZE, fp_map) != NULL){ /*leitura do resto do mapa e insercao das ligacoes no grafo*/
		insere_grafo(p_linha, G);
	}		
fclose(fp_map);

return G;	
}
