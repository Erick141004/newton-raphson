typedef struct newton *Newton;
typedef enum {ERRO, SUCESSO} Status;
typedef struct zero *Zero;

Newton newton_criar(double (*funcao_calculo)(double), double, int);
Status newton_procurar_zero(Newton, double*, Zero, int);
void newton_destruir(Newton);