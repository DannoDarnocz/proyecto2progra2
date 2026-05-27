//
// Created by axela on 9/4/2026.
//

#include "../cabeceras/Incidencia.h"

#include <iomanip>

#include "../cabeceras/excepciones/ErrorRango.h"

int Incidencia::contador = 0;

Incidencia::Incidencia(Equipo* e, int severidad, int dia):equipo(e),dia(dia)
{
    if (severidad>2 || severidad<0) throw ErrorRango("La severidad debe de estar entre 0 y 2");
    this->severidad = severidad;
    id = to_string(contador);
    contador++;
};

int Incidencia::getSeveridad() const { return severidad; }

void Incidencia::setEquipo(Equipo *e) { this->equipo = e; }

string Incidencia::getSeveridadString() const
{
    switch (severidad)
    {
        case 0:
            return "Baja";
        case 1:
            return "Media";
        case 2:
            return "Alta";
        default:
            throw ErrorRango("La severidad de la incidencia no esta entre 0 y 2");
    }
}

string Incidencia::toString() const {
    stringstream s;

    s << "ID: " << left << setw(2) << id << " | Severidad: " << setw(5) << getSeveridadString() << " | Dia: " << setw(2) << dia<< " | Equipo: " ;

    if (equipo) {
        s << equipo->getId();
    }
    else{
        s << "No asignado";
    }
    return s.str();
}

