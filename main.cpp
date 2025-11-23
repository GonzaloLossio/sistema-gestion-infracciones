#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "Bibliotecas/Fecha.h"
#include "Bibliotecas/TablaDeInfracciones.h"
#include "Bibliotecas/InfraccionCometida.h"
#include "Bibliotecas/EmpresasRegistradas.h"

#include "Bibliotecas/NodoTablaDeInfracciones.h"
#include "Bibliotecas/NodoEmpresasRegistradas.h"

#include "Bibliotecas/FuncionesAuxiliares.h"
int main() {
    struct NodoTablaDeInfracciones *listaTablaDeInfracciones;
    struct NodoEmpresasRegistradas *listaEmpresasRegistradas;

    leerTablaDeInfracciones(listaTablaDeInfracciones);
    leerEmpresasRegistradas(listaEmpresasRegistradas);
    leerPlacasRegistradas(listaEmpresasRegistradas);
    leerInfraccionesCometidas(listaEmpresasRegistradas,listaTablaDeInfracciones);
    ordenarEmpresasRegistradasAscPorDistrito(listaEmpresasRegistradas);

    return 0;
}