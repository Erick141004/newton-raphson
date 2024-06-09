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

    for(int i = 0; i < n_raiz; i++){
        int cont = 0;
        double xi = raizes[i];
        double f_xi = n->funcao_calculo(xi);
        double derivada_xi = derivada_numerica(n->funcao_calculo, xi);
        double valor_nr = newton_raphson(xi, f_xi, derivada_xi);
        double erro_absoluto = absolute(xi - valor_nr);

        printf("Iteração %d, xi inicial: %g, f(xi): %g, derivada(xi): %g, valor_nr: %g, erro_absoluto: %g\n\n",
                i, xi, f_xi, derivada_xi, valor_nr, erro_absoluto);

        while(cont < n->max_passos && erro_absoluto > n->tolerancia){
            xi = valor_nr;
            f_xi = n->funcao_calculo(xi);
            derivada_xi = derivada_numerica(n->funcao_calculo, xi);

            if(derivada_xi == 0)
                break;

            valor_nr = newton_raphson(xi, f_xi, derivada_xi);
            erro_absoluto = absolute(xi - valor_nr);
            cont++;
            
            printf("Iteração %d, xi: %g, f(xi): %g, derivada(xi): %g, valor_nr: %g, erro_absoluto: %g\n\n",
             cont, xi, f_xi, derivada_xi, valor_nr, erro_absoluto);
        }

        if(erro_absoluto <= n->tolerancia) {
            z_func[i].status = SUCESSO;
            z_func[i].zero = valor_nr;
            achou_raiz = SUCESSO;
        } else if(derivada_xi == 0){
            printf("Erro na derivada. A derivada teve como resposta 0\n");
            z_func[i].status = ERRO;
            z_func[i].zero = 0;
        }else{
            z_func[i].status = ERRO;
            z_func[i].zero = 0;
        }
    }

    return achou_raiz;
}

double newton_raphson(double x_i, double f_xi, double derivada_xi){
    double resultado = x_i - f_xi / derivada_xi;
    printf("Newton-Raphson: x_i: %g, f_xi: %g, derivada_xi: %g, resultado: %g\n\n", x_i, f_xi, derivada_xi, resultado);
    return resultado;
}

//derivada numerica central foi a escolhida 
double derivada_numerica(double (*funcao)(double), double value){
    double h = 1e-6;
    double x1 = funcao(value + h);
    double x2 = funcao(value - h);
    printf("Valor passado: %g\n", value);
    printf("Valor de x1: %g\n", x1);
    printf("Valor de x2: %g\n", x2);

    if(x1 != VALOR_ERRO && x2 != VALOR_ERRO){
        double derivada = (x1 - x2) / (2 * h);
        printf("Derivada numérica: value: %g, derivada: %g\n\n", value, derivada);
        return derivada;
    }
    else
        return 0;
}

void newton_destruir(Newton n){
    if(n != NULL)
        free(n);

    n = NULL;

    return;
}