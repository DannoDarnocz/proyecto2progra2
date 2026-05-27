//
// Created by Daniel on 17/04/2026.
//

#ifndef PROYECTO_1_LECTORARCHIVO_H
#define PROYECTO_1_LECTORARCHIVO_H
#include <fstream>
#include <sstream>
#include "../listas/ListaEquipo.h"
using namespace std;

class LectorEquipos {
public:
    ListaEquipo* leerArchivo(string, ListaEquipo*) const;
};


#endif //PROYECTO_1_LECTORARCHIVO_H
