//
// Created by axela on 9/4/2026.
//

#include "../../cabeceras/mantenimientos/MantenimientoBase.h"

string MantenimientoBase::descripcion() const {
    return "Mantenimiento basico";
}
void MantenimientoBase::arreglar(Equipo* e, int dia) {
    e->eliminarIncidencias();
    e->setCriticidad(e->getCriticidad() * 0.2);
    e->setDiaMantenimiento(dia);
}
