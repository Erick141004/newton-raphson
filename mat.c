#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

double potencia(double value, int iteracoes){ //levando em consideracao que nao tempos potencias de numeros fracionarios
    double result = 1.0;
    for(int i = 0; i < iteracoes - 1; i++){
        result *= value;
    }

    return result;
}

double absolute(double x){
    return x > 0 ? x : -x;
}

double taylor(double x, int x0, double *derivadas, int qtd_derivadas){
    double valor_taylor = 0;
    long int fatorial = 0;
    int iteracoes = 15; //melhor valor possivel encontrado para a quantidade de iteracoes

    for(int i = 0; i < iteracoes; i++){
        if(i == 0) 
            fatorial = 1;
        else 
            fatorial *= i;

        valor_taylor += (derivadas[i % qtd_derivadas] * potencia((x - x0), i))/fatorial;
    }

    return valor_taylor;
}

double *derivada_sqrt(int qtd_derivadas){ //essa funcao ja esta subentendida que usaremos raiz de x em torno do ponto 1
    double *derivadas = malloc(qtd_derivadas * sizeof(double));
    derivadas[0] = 1;
    derivadas[1] = 0.5;

    for(int i = 2; i < qtd_derivadas; i++){
        derivadas[i] = derivadas[i - 1] * (0.5 - (i - 1));
    }

    return derivadas;
}

double *derivadas_ln(int qtd_derivadas){ //essa funcao ja esta subentendida que usaremos ln x em torno do ponto 1
    double* derivadas = malloc(qtd_derivadas * sizeof(double));

    derivadas[0] = 0;
    derivadas[1] = 1;

    for(int i = 2; i < qtd_derivadas; i++){
        derivadas[i] = (i - 1) * derivadas[i - 1] * -1;
    }

    return derivadas;
}

double sin(double x){
    double derivadas_sin[4] = {0, 1, 0, -1};
    return taylor(x, 0, derivadas_sin, 4);
}

double cos(double x){
    double derivadas_cos[4] = {1, 0, -1, 0};
    return taylor(x, 0, derivadas_cos, 4);
}

double exp(double x){
    double derivadas_e[1] = {1}; 
    return taylor(x, 0, derivadas_e, 1);
}

double ln(double x){
    if (x <= 0){
        return -1;
    }else{
        double *derivadas = derivadas_ln(15);
        double value = taylor(x, 1, derivadas, 15);
        free(derivadas);

        return value;
    }
}

double sqrt(double x){
    if(x < 0){
        return -1;
    }else{
        double *derivadas = derivada_sqrt(15);
        double value= taylor(x, 1, derivadas, 15);
        free(derivadas);

        return value;
    }  
}



