typedef struct newton *Newton;
typedef enum {ERRO, SUCESSO} Status;
typedef struct zero *Zero;

struct zero{
    Status status; // Indicará se uma raiz foi encontrada
    double zero;   // Se status==SUCESSO, conteŕa o valor da raiz encontrada
};

Newton newton_criar(double (*funcao_calculo)(double), double, int);
Status newton_procurar_zero(Newton, double*, Zero, int);
void newton_destruir(Newton);