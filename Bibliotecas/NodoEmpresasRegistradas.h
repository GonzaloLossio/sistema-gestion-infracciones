//
// Created by Gonzalo on 21/11/2025.
//

#ifndef ESTRUCTURAS_LABORATORIO09_2025_1__NODOEMPRESASREGISTRADAS_H
#define ESTRUCTURAS_LABORATORIO09_2025_1__NODOEMPRESASREGISTRADAS_H
struct NodoEmpresasRegistradas {
    struct EmpresasRegistradas datoEmpresasRegistradas;
    struct NodoEmpresasRegistradas *siguiente;
};
#endif //ESTRUCTURAS_LABORATORIO09_2025_1__NODOEMPRESASREGISTRADAS_H