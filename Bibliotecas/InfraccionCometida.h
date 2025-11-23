//
// Created by Gonzalo on 21/11/2025.
//

#ifndef ESTRUCTURAS_LABORATORIO09_2025_1__INFRACCIONCOMETIDA_H
#define ESTRUCTURAS_LABORATORIO09_2025_1__INFRACCIONCOMETIDA_H
struct InfraccionCometida {
    struct Fecha fechaDeInfraccion;
    char *placa;
    char *codigoDeLaInfraccion;
    double multa;
    char *descripcion;
    bool multaPagada;
    struct Fecha fechaDePago;
};
#endif //ESTRUCTURAS_LABORATORIO09_2025_1__INFRACCIONCOMETIDA_H