//
// Created by axel on 9/4/2026.
//

#include "../../cabeceras/listas/NodoIncidencia.h"

NodoIncidencia::NodoIncidencia() : miIncidencia(nullptr), sig(nullptr) {}
Incidencia* NodoIncidencia::getIncidencia() const { return miIncidencia; }
void NodoIncidencia::setIncidencia(Incidencia* O) { miIncidencia = O; }
NodoIncidencia* NodoIncidencia::getSig() const { return sig; }