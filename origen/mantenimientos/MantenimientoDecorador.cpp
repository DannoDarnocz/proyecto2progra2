//
// Created by axela on 9/4/2026.
//

#include "../../cabeceras/mantenimientos/MantenimientoDecorador.h"

MantenimientoDecorador::MantenimientoDecorador(Mantenimiento *m) {
    this->mant=m;
}

MantenimientoDecorador::~MantenimientoDecorador() {
    if (mant) delete mant;
}
