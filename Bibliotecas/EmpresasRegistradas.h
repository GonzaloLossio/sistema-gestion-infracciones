//
// Created by Gonzalo on 21/11/2025.
//

#ifndef ESTRUCTURAS_LABORATORIO09_2025_1__EMPRESASREGISTRADAS_H
#define ESTRUCTURAS_LABORATORIO09_2025_1__EMPRESASREGISTRADAS_H
struct EmpresasRegistradas{
    int dni;
    char *nombre;
    char *distrito;
    char *placas[10];
    int numPlacas;
    struct InfraccionCometida *infraccion;
    int cantidadDeInfracciones;
    double totalPagado;
    double totalAdeudado;
};
#endif //ESTRUCTURAS_LABORATORIO09_2025_1__EMPRESASREGISTRADAS_H