//
// Created by Gonzalo on 21/11/2025.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Fecha.h"
#include "TablaDeInfracciones.h"
#include "InfraccionCometida.h"
#include "EmpresasRegistradas.h"

#include "NodoTablaDeInfracciones.h"
#include "NodoEmpresasRegistradas.h"

#include "FuncionesAuxiliares.h"

#define NO_ENCONTRADO -1

#define MAX_PLACAS 10
#define MAX_INFRACCIONES 40

void leerTablaDeInfracciones(struct NodoTablaDeInfracciones *&listaTablaDeInfracciones) {
    ifstream archTablaDeInfracciones("ArchivosDeDatos/TablaDeInfracciones.csv",ios::in);
    if (not archTablaDeInfracciones.is_open()) {
        cout<<"Error al abrir el archivo ArchivosDeDatos/TablaDeInfracciones.csv"<<endl;
        exit(1);
    }
    listaTablaDeInfracciones=nullptr;
    struct TablaDeInfracciones datoTablaDeInfracciones;
    while (true) {
        datoTablaDeInfracciones.codigo=leeCadenaExactaConDelim(archTablaDeInfracciones,',');
        if (archTablaDeInfracciones.eof()) break;
        archTablaDeInfracciones>>datoTablaDeInfracciones.multa;
        archTablaDeInfracciones.get();
        datoTablaDeInfracciones.descripcion=leeCadenaExactaConDelim(archTablaDeInfracciones,'\n');
        insertarNodoTablaDeInfracciones(datoTablaDeInfracciones,listaTablaDeInfracciones);
    }
}
char*leeCadenaExactaConDelim(ifstream &arch ,char carLim) {
    char *ptr,cadena[500];
    arch.getline(cadena,500,carLim);
    if (arch.eof()) return nullptr;
    pasarAMayuscula(cadena);
    ptr= new char [strlen(cadena)+1];
    strcpy(ptr,cadena);
    return ptr;
}
void pasarAMayuscula(char*cadena) {
    for (int i=0;cadena[i];i++) {
        if (cadena[i]>='a' and cadena[i]<='z') {
            cadena[i]-=('A'-'a');
        }
    }
}
void insertarNodoTablaDeInfracciones(struct TablaDeInfracciones datoTablaDeInfracciones,
    struct NodoTablaDeInfracciones *&listaTablaDeInfracciones) {
    struct NodoTablaDeInfracciones *nodoNuevo;
    nodoNuevo=new struct NodoTablaDeInfracciones;
    nodoNuevo->datoTablaDeInfracciones=datoTablaDeInfracciones;
    nodoNuevo->siguiente=listaTablaDeInfracciones;
    listaTablaDeInfracciones=nodoNuevo;
}
void leerEmpresasRegistradas(struct NodoEmpresasRegistradas*&listaEmpresasRegistradas) {
    ifstream archEmpresasRegistradas("ArchivosDeDatos/EmpresasRegistradas.csv",ios::in);
    if (not archEmpresasRegistradas.is_open()) {
        cout<<"Error al abrir el archivo ArchivosDeDatos/EmpresasRegistradas.csv"<<endl;
        exit(1);
    }
    listaEmpresasRegistradas=nullptr;
    struct EmpresasRegistradas datoEmpresasRegistradas{};
    while (true) {
        archEmpresasRegistradas>>datoEmpresasRegistradas.dni;
        if (archEmpresasRegistradas.eof()) break;
        archEmpresasRegistradas.get();
        datoEmpresasRegistradas.nombre=leeCadenaExactaConDelim(archEmpresasRegistradas,',');
        datoEmpresasRegistradas.distrito=leeCadenaExactaConDelim(archEmpresasRegistradas,'\n');
        datoEmpresasRegistradas.infraccion=new struct InfraccionCometida [MAX_INFRACCIONES];
        insertarNodoEmpresasRegistradas(datoEmpresasRegistradas,listaEmpresasRegistradas);
    }
}
void insertarNodoEmpresasRegistradas(struct EmpresasRegistradas datoEmpresasRegistradas,
    struct NodoEmpresasRegistradas*&listaEmpresasRegistradas) {
    struct NodoEmpresasRegistradas *nodoNuevo;
    nodoNuevo=new struct NodoEmpresasRegistradas;
    nodoNuevo->datoEmpresasRegistradas=datoEmpresasRegistradas;
    nodoNuevo->siguiente=listaEmpresasRegistradas;
    listaEmpresasRegistradas=nodoNuevo;
}
void leerPlacasRegistradas(struct NodoEmpresasRegistradas *&listaEmpresasRegistradas) {
    ifstream archPlacasRegistradas("ArchivosDeDatos/PlacasRegistradas.csv",ios::in);
    if (not archPlacasRegistradas.is_open()) {
        cout<<"Error al abrir el archivo ArchivosDeDatos/PlacasRegistradas.csv"<<endl;
        exit(1);
    }
    int dni;
    char *placa;
    struct NodoEmpresasRegistradas *listaEmpresasRegistradasEncontrada;
    while (true) {
        archPlacasRegistradas>>dni;
        if (archPlacasRegistradas.eof()) break;
        listaEmpresasRegistradasEncontrada=bucarDni(listaEmpresasRegistradas,dni);
        if (listaEmpresasRegistradasEncontrada!=nullptr) {
            archPlacasRegistradas.get();
            int i=listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.numPlacas;
            placa=leeCadenaExactaConDelim(archPlacasRegistradas,'\n');
            // archPlacasRegistradas>>placa;
            // listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.placas[i]=
            //     leeCadenaExactaConDelim(archPlacasRegistradas,'\n');
            listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.placas[i]=placa;
            listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.numPlacas++;
        }else {
            while (archPlacasRegistradas.get()!='\n');
        }
    }
}
struct NodoEmpresasRegistradas *bucarDni(struct NodoEmpresasRegistradas*listaEmpresasRegistradas,int dni) {
    struct NodoEmpresasRegistradas*ptrAux=listaEmpresasRegistradas;
    while (ptrAux!=nullptr) {
        if (ptrAux->datoEmpresasRegistradas.dni==dni) {
            return ptrAux;
        }
        ptrAux=ptrAux->siguiente;
    }
    return nullptr;
}
void leerInfraccionesCometidas(struct NodoEmpresasRegistradas*&listaEmpresasRegistradas,
    struct NodoTablaDeInfracciones*listaTablaDeInfracciones) {
    ifstream archInfraccionesCometidas("ArchivosDeDatos/InfraccionesCometidas.csv",ios::in);
    if (not archInfraccionesCometidas.is_open()) {
        cout<<"Error al abrir el archivo ArchivosDeDatos/InfraccionesCometidas.csv"<<endl;
        exit(1);
    }
    int diaInfracc,mesInfracc,anhoInfracc,fechaInfracc,diaPago,mesPago,anhoPago,fechaPago;
    char placa[9],codigoInfracc[6],carPago,car;
    struct NodoEmpresasRegistradas *listaEmpresasRegistradasEncontrada;
    struct NodoTablaDeInfracciones *listaTablaDeInfraccionesEncontrada;
    while (true) {
        archInfraccionesCometidas>>diaInfracc;
        if (archInfraccionesCometidas.eof()) break;
        archInfraccionesCometidas>>car>>mesInfracc>>car>>anhoInfracc>>car>>placa>>car>>codigoInfracc>>car>>carPago;
        listaEmpresasRegistradasEncontrada=buscarPlaca(listaEmpresasRegistradas,placa);
        listaTablaDeInfraccionesEncontrada=buscarInfraccion(listaTablaDeInfracciones,codigoInfracc);
        if (listaEmpresasRegistradasEncontrada!=nullptr and listaTablaDeInfraccionesEncontrada!=nullptr) {
            int i=listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.cantidadDeInfracciones;
            fechaInfracc=calcularFechaLarga(diaInfracc,mesInfracc,anhoInfracc);
            if (carPago=='P') {
                archInfraccionesCometidas>>car>>diaPago>>car>>mesPago>>car>>anhoPago;
                fechaPago=calcularFechaLarga(diaPago,mesPago,anhoPago);
                listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.totalPagado+=
                    listaTablaDeInfraccionesEncontrada->datoTablaDeInfracciones.multa;
                listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].multaPagada=true;
            }else {
                anhoPago=0;
                diaPago=0;
                mesPago=0;
                fechaPago=0;
                listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].multaPagada=false;
                listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.totalAdeudado+=
                    listaTablaDeInfraccionesEncontrada->datoTablaDeInfracciones.multa;
            }
            insertarInfraccion(listaEmpresasRegistradasEncontrada,i,fechaPago,placa,fechaInfracc,
                listaTablaDeInfraccionesEncontrada,codigoInfracc,diaPago,mesPago,anhoPago,diaInfracc,mesInfracc,
                anhoInfracc);

            listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.cantidadDeInfracciones++;
        }else {
            while (archInfraccionesCometidas.get()!='\n');
        }
    }
}
struct NodoEmpresasRegistradas* buscarPlaca(struct NodoEmpresasRegistradas *listaEmpresasRegistradas,char*placa) {
    struct NodoEmpresasRegistradas *ptrAux=listaEmpresasRegistradas;
    while (ptrAux!=nullptr) {
        for (int i=0;i<ptrAux->datoEmpresasRegistradas.numPlacas;i++) {
            if (strcmp(ptrAux->datoEmpresasRegistradas.placas[i],placa)==0) {
                return ptrAux;
            }
        }
        ptrAux=ptrAux->siguiente;
    }
    return nullptr;
}
struct NodoTablaDeInfracciones *buscarInfraccion(struct NodoTablaDeInfracciones*listaTablaDeInfracciones,
    char*codigoInfracc) {
    struct NodoTablaDeInfracciones *ptrAux=listaTablaDeInfracciones;
    while (ptrAux!=nullptr) {
        if (strcmp(ptrAux->datoTablaDeInfracciones.codigo,codigoInfracc)==0) {
            return ptrAux;
        }
        ptrAux=ptrAux->siguiente;
    }
    return nullptr;
}
int calcularFechaLarga(int &dia,int&mes,int&anho) {
    return anho*10000+mes*100+dia;
}
void insertarInfraccion(struct NodoEmpresasRegistradas*&listaEmpresasRegistradasEncontrada,int i,int fechaPago,
    char*placa,int fechaInfracc,struct NodoTablaDeInfracciones*listaTablaDeInfraccionesEncontrada,char*codigoInfracc,
    int diaPago,int mesPago,int anhoPago,int diaInfracc,int mesInfracc,int anhoInfracc) {
    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].placa=new char [strlen(placa)+1];
    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].codigoDeLaInfraccion=
        new char [strlen(codigoInfracc)+1];
    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].descripcion=
        new char [strlen(listaTablaDeInfraccionesEncontrada->datoTablaDeInfracciones.descripcion)+1];
    strcpy(listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].placa,placa);
    strcpy(listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].codigoDeLaInfraccion,
        codigoInfracc);
    strcpy(listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].descripcion,
       listaTablaDeInfraccionesEncontrada->datoTablaDeInfracciones.descripcion);
    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].multa=
        listaTablaDeInfraccionesEncontrada->datoTablaDeInfracciones.multa;

    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].fechaDeInfraccion.fecha=fechaInfracc;
    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].fechaDePago.fecha=fechaPago;

    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].fechaDeInfraccion.aa=anhoInfracc;
    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].fechaDeInfraccion.mm=mesInfracc;
    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].fechaDeInfraccion.dd=diaInfracc;

    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].fechaDePago.aa=anhoPago;
    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].fechaDePago.mm=mesPago;
    listaEmpresasRegistradasEncontrada->datoEmpresasRegistradas.infraccion[i].fechaDePago.dd=diaPago;
}
void ordenarEmpresasRegistradasAscPorDistrito(struct NodoEmpresasRegistradas*&listaEmpresasRegistradas) {

    for (struct NodoEmpresasRegistradas *ptrAux=listaEmpresasRegistradas;ptrAux!=nullptr;ptrAux=ptrAux->siguiente) {
        for (struct NodoEmpresasRegistradas*ptrAux2=ptrAux->siguiente;ptrAux2!=nullptr;ptrAux2=ptrAux2->siguiente) {
            if (strcmp(ptrAux->datoEmpresasRegistradas.distrito,ptrAux2->datoEmpresasRegistradas.distrito)>0) {
                cambiarStruct(ptrAux->datoEmpresasRegistradas,ptrAux2->datoEmpresasRegistradas);
            }
        }
    }
}
void cambiarStruct(struct EmpresasRegistradas &datoI,struct EmpresasRegistradas &datoJ) {
    struct EmpresasRegistradas aux=datoI;
    datoI=datoJ;
    datoJ=aux;
}