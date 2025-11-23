cmake_minimum_required(VERSION 4.0)
project(Estructuras_Laboratorio09_2025_1_)

set(CMAKE_CXX_STANDARD 20)

add_executable(Estructuras_Laboratorio09_2025_1_ main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Fecha.h
        Bibliotecas/TablaDeInfracciones.h
        Bibliotecas/InfraccionCometida.h
        Bibliotecas/EmpresasRegistradas.h
        Bibliotecas/NodoTablaDeInfracciones.h
        Bibliotecas/NodoEmpresasRegistradas.h
)
