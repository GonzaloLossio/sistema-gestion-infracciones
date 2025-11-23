//
// Created by Gonzalo on 21/11/2025.
//

#ifndef ESTRUCTURAS_LABORATORIO09_2025_1__FUNCIONESAUXILIARES_H
#define ESTRUCTURAS_LABORATORIO09_2025_1__FUNCIONESAUXILIARES_H
void leerTablaDeInfracciones(struct NodoTablaDeInfracciones *&listaTablaDeInfracciones);
char*leeCadenaExactaConDelim(ifstream &arch ,char carLim);
void pasarAMayuscula(char*cadena);
void insertarNodoTablaDeInfracciones(struct TablaDeInfracciones datoTablaDeInfracciones,
    struct NodoTablaDeInfracciones *&listaTablaDeInfracciones);
void leerEmpresasRegistradas(struct NodoEmpresasRegistradas*&listaEmpresasRegistradas);
void insertarNodoEmpresasRegistradas(struct EmpresasRegistradas datoEmpresasRegistradas,
    struct NodoEmpresasRegistradas*&listaEmpresasRegistradas);
void leerPlacasRegistradas(struct NodoEmpresasRegistradas *&listaEmpresasRegistradas);
struct NodoEmpresasRegistradas *bucarDni(struct NodoEmpresasRegistradas*listaEmpresasRegistradas,int dni);
void leerInfraccionesCometidas(struct NodoEmpresasRegistradas*&listaEmpresasRegistradas,
    struct NodoTablaDeInfracciones*listaTablaDeInfracciones);
struct NodoEmpresasRegistradas* buscarPlaca(struct NodoEmpresasRegistradas *listaEmpresasRegistradas,char*placa);
struct NodoTablaDeInfracciones *buscarInfraccion(struct NodoTablaDeInfracciones*listaTablaDeInfracciones,
    char*codigoInfracc);
int calcularFechaLarga(int &dia,int&mes,int&anho);
void insertarInfraccion(struct NodoEmpresasRegistradas*&listaEmpresasRegistradasEncontrada,int i,int fechaPago,
    char*placa,int fechaInfracc,struct NodoTablaDeInfracciones*listaTablaDeInfraccionesEncontrada,char*codigoInfracc,
    int diaPago,int mesPago,int anhoPago,int diaInfracc,int mesInfracc,int anhoInfracc);
void ordenarEmpresasRegistradasAscPorDistrito(struct NodoEmpresasRegistradas*&listaEmpresasRegistradas);
void cambiarStruct(struct EmpresasRegistradas &datoI,struct EmpresasRegistradas &datoJ);
#endif //ESTRUCTURAS_LABORATORIO09_2025_1__FUNCIONESAUXILIARES_H