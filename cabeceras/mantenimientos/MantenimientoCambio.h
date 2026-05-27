//
// Created by Daniel on 15/04/2026.
//

#ifndef PROYECTO_1_MANTENIMIENTOCAMBIO_H
#define PROYECTO_1_MANTENIMIENTOCAMBIO_H
#include "MantenimientoDecorador.h"
// cambio de componentes
class MantenimientoCambio : public MantenimientoDecorador
{
public:
    MantenimientoCambio(Mantenimiento *m):MantenimientoDecorador(m) {}
    string descripcion() const override;
    void arreglar(Equipo *e, int dia) override;
};


#endif //PROYECTO_1_MANTENIMIENTOCAMBIO_H