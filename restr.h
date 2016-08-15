#ifndef ____restr__
#define ____restr__

#include <stdio.h>
#include "grafo.h"
#include "cli.h"

int def_restr_a(cliente*cli);
int check_restr_a(viagem* t_aux,int restr_pref,cliente *cli);
int cmp_b(cliente*cli,int tempo_total,int cust_total);
int def_restr_b(cliente*cli,int *def);

#endif
