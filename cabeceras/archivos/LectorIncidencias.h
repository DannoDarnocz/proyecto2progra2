//
// Created by Daniel on 17/04/2026.
//

#ifndef PROYECTO_1_LECTORINCIDENCIAS_H
#define PROYECTO_1_LECTORINCIDENCIAS_H

#include <fstream>
#include "../listas/ListaIncidencia.h"
using namespace std;

class LectorIncidencias
{
public:
    ListaIncidencia* leerArchivo(string, ListaIncidencia*) const;
};


#endif //PROYECTO_1_LECTORINCIDENCIAS_H