//
// Created by Daniel on 10/04/2026.
//

#include "../../cabeceras/equipos/Microscopio.h"

Microscopio::Microscopio(bool esPrototipo) : Equipo(0,0,esPrototipo) { if (!esPrototipo) { generarId();} }
Microscopio::Microscopio(double crit, double tiempo) : Equipo(crit, tiempo) { generarId(); }

string Microscopio::getTipo() const { return "Microscopio"; }

string Microscopio::getPrefix() const { return "MIC"; }
void Microscopio::leerDatos(stringstream &ss) {
    string idDescartar; //El archivo tiene una ID del equipo de ejemplo, pero si ya existe dicha ID previamente se le debe asignar una nueva
    //Por lo que, se descarta la ID del archivo que su única utilidad es otorgar el tipo de Equipo que es
    getline(ss,idDescartar,',');
    ss >> criticidad; ss.ignore();
    ss >> diaMantenimiento; ss.ignore();
}

Equipo* Microscopio::crear() { return new Microscopio(); }