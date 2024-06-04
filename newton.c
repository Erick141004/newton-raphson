#include <stdlib.h>
#include <stdio.h>
#include "newton.h"

struct newton{
  double tolerancia;
  int max_passos;
  double (*funcao_calculo)(double);  
};

struct zero{
    Status status; // Indicará se uma raiz foi encontrada
    double zero;   // Se status==SUCESSO, conteŕa o valor da raiz encontrada
};