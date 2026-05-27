//
// Created by axela on 9/4/2026.
//

#ifndef PROYECTO_1_MANTENIMIENTODECORADOR_H
#define PROYECTO_1_MANTENIMIENTODECORADOR_H
#include "Mantenimiento.h"


class MantenimientoDecorador : public Mantenimiento {
protected:
    Mantenimiento* mant;
public:
    MantenimientoDecorador(Mantenimiento* m);
    virtual ~MantenimientoDecorador();
};


#endif //PROYECTO_1_MANTENIMIENTODECORADOR_H