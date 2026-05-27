//
// Created by axel on 9/4/2026.
//

#include "../../cabeceras/equipos/Laptop.h"

Laptop::Laptop(bool esPrototipo) : Equipo(0,0,esPrototipo) { if (!esPrototipo) { generarId();} }
Laptop::Laptop(double crit, double tiempo) : Equipo(crit, tiempo) { generarId(); }

string Laptop::getTipo() const { return "Laptop"; }

string Laptop::getPrefix() const { return "LAP"; }
void Laptop::leerDatos(stringstream &ss) {
    string idDescartar; //El archivo tiene una ID del equipo de ejemplo, pero si ya existe dicha ID previamente se le debe asignar una nueva
    //Por lo que, se descarta la ID del archivo que su única utilidad es otorgar el tipo de Equipo que es
    getline(ss,idDescartar,',');
    ss >> criticidad; ss.ignore();
    ss >> diaMantenimiento; ss.ignore();
}

Equipo *Laptop::crear() {
    return new Laptop();
}
