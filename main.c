#include <stdio.h>
#include <stdlib.h>

// Implementa funções matemáticas
// sin(x), cos(x), exp(x), ln(x), sqrt(x)
#include "mat.h"

// Implementa método de Newton-Raphson
// Utilize uma função interna para diferenciação numérica
#include "newton.h"

// Função para a qual as raízes serão solicitadas
double f(double);

int main() {
  // Tolerância e Número máximo de passos devem ser parâmetros obrigatórios
  double tolerancia = 1e-5;
  int max_passos = 10;

  // Cria um Tipo Abstrato de Dados (TAD) com 3 parâmetros
  Newton n = newton_criar(&f, tolerancia, max_passos);

  // Define o vetor de pontos fixos
  double nr_raizes = 2;
  double x[] = {-1, 1}; // Busca de raízes em torno de x=5.0 e x=8.0

  // Observe que zeros não está inicializada
  Zero zeros = zero_criar(nr_raizes);

  // Delegamos, para a função newton_procurar_zero, a inicialização da variável "zeros"
  // Corrija, se necessário, a passagem dos parâmetros
  Status status = newton_procurar_zero(n, x, zeros, nr_raizes);

  if (status == SUCESSO) {
    for(int i = 0; i < nr_raizes; i++) {
      if(zeros[i].status == SUCESSO) {
        printf("Vizinhança de x=%g => Raiz encontrada: %.20g\n", x[i], zeros[i].zero);
      } else {
        printf("Não foi encontrada uma raiz na vizinhança de x=%.2g\n", x[i]);
      }
    }
  } else{
    for(int i = 0; i < nr_raizes; i++){
        printf("Não foi encontrada uma raiz na vizinhança de x=%.2g\n", x[i]);
    }
  }

  newton_destruir(n);

  // Isso é necessário? 
  if(zeros != NULL){
    free(zeros);
    zeros = NULL;
  }

  exit(0);
}

// Função f(x)
// Esta função utilizará as funções elementares desenvolvidas em mat.c
double f(double x) {
  return x-exp(x-2);
}