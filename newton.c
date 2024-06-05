#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "newton.h"

struct newton{
  double tolerancia;
  int max_passos;
  double (*funcao_calculo)(double);  
};

Newton newton_criar(double (*func)(double), double tol, int max_passos){
    Newton n = malloc(sizeof(struct newton));
    n->funcao_calculo = func;
    n->tolerancia = tol;
    n->max_passos = max_passos;

    return n;
}

Status newton_procurar_zero(Newton n, double* raizes, Zero z_func, int n_raiz){
    bool achou_raiz = false;

    
    if (achou_raiz)
        return SUCESSO;
    else 
        return ERRO;
}

void newton_destruir(Newton n){
    if(n != NULL)
        free(n);

    n = NULL;

    return;
}