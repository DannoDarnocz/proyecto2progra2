//
// Created by axel on 9/4/2026.
//

#ifndef PROYECTO_1_NODOEQUIPO_H
#define PROYECTO_1_NODOEQUIPO_H
#include "../equipos/Equipo.h"

class NodoEquipo {
private:
    Equipo* miEquipo;
public:
    NodoEquipo* sig;
    NodoEquipo();
    ~NodoEquipo();
    Equipo* getEquipo() const;
    void setEquipo(Equipo* O);
    NodoEquipo* getSig() const;
};


#endif //PROYECTO_1_NODOEQUIPO_H