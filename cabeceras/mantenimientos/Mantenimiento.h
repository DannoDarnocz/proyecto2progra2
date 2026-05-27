//
// Created by axela on 9/4/2026.
//

#ifndef PROYECTO_1_MANTENIMIENTO_H
#define PROYECTO_1_MANTENIMIENTO_H
#include "../equipos/Equipo.h"


class Mantenimiento {
public:
    virtual string descripcion() const = 0;
    virtual ~Mantenimiento() = default;
    virtual void arreglar(Equipo* e, int dia) = 0;
};


#endif //PROYECTO_1_MANTENIMIENTO_H