//
// Created by João Valentim on 05/01/2023.
//

#ifndef LP1_AED_BIPOLARES_LL_H
#define LP1_AED_BIPOLARES_LL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "aed_lp1_2023_proj_part1_chars.h"
#include "aed_lp1_2023_proj_part1_ints.h"


typedef struct porta_chaves {
    char **matpubchars;
    char **matprivchars;
    char **matrunchars;
    char **matpubints;
    char **matprivints;
    char **matrunints;
    int lines;
    int columns;
}PORTA_CHAVES;

typedef struct porta_chaves_node {
    PORTA_CHAVES info;
    struct porta_chaves *pnext;
}PORTA_CHAVES_NODE;

typedef struct porta_chaves_ll{
    PORTA_CHAVES_NODE *phead;
    PORTA_CHAVES_NODE *ptail;
    int n_nodes;
}PORTA_CHAVES_LL;

///////////////////////////////////////////

typedef struct cliente{
    char* nome;
    char* email;
    PORTA_CHAVES_LL *portaChavesNode;
}CLIENTE;

typedef struct cliente_node{
    CLIENTE cliente;
    struct cliente_node *pnext;
}CLIENTE_NODE;

typedef struct cliente_node_ll{
    CLIENTE_NODE *phead;
    CLIENTE_NODE *ptail;
    int n_clientes;
}CLIENTE_NODE_LL;

int main_ll_part1(int argc, char *argv[]);

#endif //LP1_AED_BIPOLARES_LL_H
