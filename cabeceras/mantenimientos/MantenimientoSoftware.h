//
// Created by Daniel on 15/04/2026.
//

#ifndef PROYECTO_1_MANTENIMIENTOSOFTWARE_H
#define PROYECTO_1_MANTENIMIENTOSOFTWARE_H
#include "MantenimientoDecorador.h"

// actualizacion de software, limpieza de disco duro, etc
class MantenimientoSoftware : public MantenimientoDecorador
{
public:
    MantenimientoSoftware(Mantenimiento *m):MantenimientoDecorador(m) {}
    string descripcion() const override;
    void arreglar(Equipo *e, int dia) override;
};


#endif //PROYECTO_1_MANTENIMIENTOSOFTWARE_H