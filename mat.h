#ifndef MAT_H
#define MAT_H

#define TOLERANCIA_MAX 1e-15
#define VALOR_ERRO 1e-90

double potencia(double, int);
double absolute(double);
double taylor(double, int, double *, int);

double sin(double);
double cos(double);
double ln(double);
double exp(double);
double sqrt(double);

#endif