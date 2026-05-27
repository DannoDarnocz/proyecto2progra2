//
// Created by axel on 9/4/2026.
//

#ifndef PROYECTO_1_NODOINCIDENCIA_H
#define PROYECTO_1_NODOINCIDENCIA_H
#include "../Incidencia.h"

class Incidencia;

class NodoIncidencia {
private:
    Incidencia* miIncidencia;
public:
    NodoIncidencia* sig;
    NodoIncidencia();
    Incidencia* getIncidencia() const;
    void setIncidencia(Incidencia* O);
    NodoIncidencia* getSig() const;
};


#endif //PROYECTO_1_NODOINCIDENCIA_H