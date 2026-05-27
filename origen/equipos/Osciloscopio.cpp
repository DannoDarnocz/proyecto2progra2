//
// Created by Daniel on 10/04/2026.
//

#include "../../cabeceras/equipos/Osciloscopio.h"

Osciloscopio::Osciloscopio(bool esPrototipo) : Equipo(0,0,esPrototipo) { if (!esPrototipo) { generarId();} }
Osciloscopio::Osciloscopio(double crit, double tiempo) : Equipo(crit, tiempo) { generarId(); }

string Osciloscopio::getTipo() const { return "Osciloscopio";}

string Osciloscopio::getPrefix() const { return "OSC"; }
void Osciloscopio::leerDatos(stringstream &ss) {
    string idDescartar; //El archivo tiene una ID del equipo de ejemplo, pero si ya existe dicha ID previamente se le debe asignar una nueva
    //Por lo que, se descarta la ID del archivo que su única utilidad es otorgar el tipo de Equipo que es
    getline(ss,idDescartar,',');
    ss >> criticidad; ss.ignore();
    ss >> diaMantenimiento; ss.ignore();
}

Equipo *Osciloscopio::crear() {
    return new Osciloscopio();
}
