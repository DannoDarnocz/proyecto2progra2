//
// Created by axela on 9/4/2026.
//

#ifndef PROYECTO_1_INCIDENCIA_H
#define PROYECTO_1_INCIDENCIA_H

#include "equipos/Equipo.h"
#include <sstream>
using namespace std;
class Equipo;

class Incidencia {
private:
    static int contador;
    string id;
    Equipo* equipo; //Equipo que presenta esta incidencia
    int severidad; //1-Baja, 2-Media, 3-Alta
    int dia; //Dia en el que se presento la incidencia
public:
    Incidencia(Equipo* e, int severidad, int dia);
    int getSeveridad() const;
    void setEquipo(Equipo* e);
    string getSeveridadString() const;
    string toString() const;
};


#endif //PROYECTO_1_INCIDENCIA_H