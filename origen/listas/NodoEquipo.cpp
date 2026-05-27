//
// Created by axel on 9/4/2026.
//

#include "../../cabeceras/listas/NodoEquipo.h"

NodoEquipo::NodoEquipo() : miEquipo(nullptr), sig(nullptr) {}
NodoEquipo::~NodoEquipo(){delete miEquipo;}
Equipo* NodoEquipo::getEquipo() const { return miEquipo; }
void NodoEquipo::setEquipo(Equipo* O) { miEquipo = O; }
NodoEquipo* NodoEquipo::getSig() const { return sig; }