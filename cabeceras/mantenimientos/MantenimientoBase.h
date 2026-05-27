//
// Created by axela on 9/4/2026.
//

#ifndef PROYECTO_1_MANTENIMIENTOBASE_H
#define PROYECTO_1_MANTENIMIENTOBASE_H
#include "Mantenimiento.h"


class MantenimientoBase : public Mantenimiento {
public:
    string descripcion() const override;
    void arreglar(Equipo *e, int dia) override;
};


#endif //PROYECTO_1_MANTENIMIENTOBASE_H