//
// Created by axel on 9/4/2026.
//

#include "../../cabeceras/equipos/AllInOne.h"

AllInOne::AllInOne(bool esPrototipo) : Equipo(0,0,esPrototipo) { if (!esPrototipo) { generarId();} }
AllInOne::AllInOne(double crit, double tiempo) : Equipo(crit, tiempo) { generarId(); }

string AllInOne::getTipo() const { return "All-In-One"; }

string AllInOne::getPrefix() const { return "AIO"; }
void AllInOne::leerDatos(stringstream &ss) {
    string idDescartar; //El archivo tiene una ID del equipo de ejemplo, pero si ya existe dicha ID previamente se le debe asignar una nueva
    //Por lo que, se descarta la ID del archivo que su única utilidad es otorgar el tipo de Equipo que es
    getline(ss,idDescartar,',');
    ss >> criticidad; ss.ignore();
    ss >> diaMantenimiento; ss.ignore();
}

Equipo *AllInOne::crear() {
    return new AllInOne();
}
