#include <stdlib.h>
#include <stdio.h>
#include "mat.h"

double potencia(double value, int iteracoes){ //levando em consideracao que nao tempos potencias de numeros fracionarios
    double result = 1.0;
    for(int i = 0; i < iteracoes; i++){
        result *= value;
    }

    return result;
}

double absolute(double x){
    return x > 0 ? x : -x;
}

//apos alguns testes, essa funcao generica criada para a serie de taylor não foi possivel calcular
//os valores corretamente, entao tive que pensar em outra maneira para o calculo das funcoes
double taylor(double x, int x0, double *derivadas, int qtd_derivadas){
    double valor_taylor = 0;
    long int fatorial = 0;
    int iteracoes = 15;

    for(int i = 0; i < iteracoes; i++){
        if(i == 0) 
            fatorial = 1;
        else 
            fatorial *= i;

        valor_taylor += (derivadas[i % qtd_derivadas] * potencia((x - x0), i))/fatorial;
    }

    return valor_taylor;
}

double sin(double x){
    double termo = x;
    double soma = termo;
    int cont = 1;

    //com o termo comecando com o valor que queremos encontrar, temos o somatorio 
    //da serie de taylor de sin sendo representado por: -x^2/(2*n) * (2*n + 1)
    while (absolute(termo) > TOLERANCIA_MAX) {
        termo *= -potencia(x, 2) / ((2 * cont) * (2 * cont + 1));
        soma += termo;
        cont++;
    }

    return soma;
}

double cos(double x){
    double termo = 1.0;
    double soma = termo;
    int cont = 1;

    //com o termo comecando em um, temos o somatorio da serie de taylor de cos
    //sendo representado por: -x^2/(2*n - 1) * (2*n)
    while (absolute(termo) > 1e-15) {
        termo *= -potencia(x, 2) / ((2 * cont - 1) * (2 * cont));
        soma += termo;
        cont++;
    }

    return soma;
}

double exp(double x){
    double termo = 1.0;
    double sum = termo;
    int n = 1;

    //para o exponencial, podemos fazer algo parecido, ja que com o x0 igual a 0
    //o nosso somatorio seria a multiplicacao de x/n, onde teriamos os nossos termos
    //da serie de taylor
    while (absolute(termo) > TOLERANCIA_MAX) {
        termo *= x / n;
        sum += termo;
        n++;
    }

    return sum;
}

double ln(double x){
    if (x <= 0){
        return VALOR_ERRO;
    }else{
        double soma = 0.0; 
        double termo = 1.0; 
        int cont = 1;

        //para o exponencial, podemos fazer algo parecido, ja que com o x0 igual a 0
        //o nosso somatorio seria a multiplicacao de x/n, onde teriamos os nossos termos
        //da serie de taylor
        while(absolute(termo) > TOLERANCIA_MAX){
            termo *= (x - 1) / x; 
            soma += termo / cont;
            cont++;
        }

        return soma;
    }
}

double sqrt(double x){
    if(x < 0){
        return VALOR_ERRO;
    }else{
        double soma = 0.0; 
        double termo = 1.0; 
        int cont = 1;

        //para a raiz quadrada, podemos 
        //o nosso somatorio seria a multiplicacao, onde teriamos os nossos termos
        //da serie de taylor
        while(absolute(termo) > TOLERANCIA_MAX){
            termo *= -(x * (2 * cont + 1)) / (2 * (cont + 1));
            soma += termo;
            cont++;
        }

        return soma;
    }  
}



