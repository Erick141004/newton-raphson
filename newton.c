#include <stdlib.h>
#include <stdio.h>
#include "newton.h"
#include "mat.h"

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

Zero zero_criar(int qtd_zeros){
    return malloc(qtd_zeros * sizeof(struct zero));
}

Status newton_procurar_zero(Newton n, double* raizes, Zero z_func, int n_raiz){
    Status achou_raiz = ERRO;
    z_func = zero_criar(n_raiz);

    for(int i = 0; i < n_raiz; i++){
        int cont = 0;
        double f_xi = n->funcao_calculo(raizes[i]);
        double derivada_xi = derivada_numerica(n->funcao_calculo, raizes[i]);
        double valor_nr = newton_raphson(raizes[i], f_xi, derivada_xi);
        double erro_absoluto = absolute(raizes[i] - valor_nr);

        while(cont < n->max_passos && erro_absoluto > n->tolerancia){
            double xi = valor_nr;
            f_xi = n->funcao_calculo(xi);
            derivada_xi = derivada_numerica(n->funcao_calculo, xi);
            valor_nr = newton_raphson(xi, f_xi, derivada_xi);

            erro_absoluto = absolute(xi - valor_nr);

            cont++;
        }

        if(cont > n->max_passos){
            z_func[i].status = ERRO;
            z_func[i].zero = 0;
        }else{
            z_func[i].status = SUCESSO;
            z_func[i].zero = valor_nr;
            achou_raiz = SUCESSO;
        }
    }

    return achou_raiz;
}

double newton_raphson(double x_i, double f_xi, double derivada_xi){
    return x_i - f_xi/derivada_xi;
}

//derivada numerica central foi a escolhida 
double derivada_numerica(double (*funcao)(double), double value){
    double h = 1e-6;
    return (funcao(value + h) - funcao(value - h))/(2 * h);
}

void newton_destruir(Newton n){
    if(n != NULL)
        free(n);

    n = NULL;

    return;
}