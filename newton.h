#ifndef NEWTON_H
#define NEWTON_H

typedef struct newton *Newton;
typedef enum {ERRO, SUCESSO} Status;
typedef struct zero *Zero;

struct zero{
    Status status; // Indicará se uma raiz foi encontrada
    double zero;   // Se status==SUCESSO, conteŕa o valor da raiz encontrada
};

Newton newton_criar(double (*funcao_calculo)(double), double, int);
Zero zero_criar(int);
Status newton_procurar_zero(Newton, double*, Zero, int);
double derivada_numerica(double(*funcao)(double), double);
double newton_raphson(double, double, double);
void newton_destruir(Newton);

#endif

