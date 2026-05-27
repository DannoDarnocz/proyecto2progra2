//
// Created by Daniel on 10/04/2026.
//

#ifndef PROYECTO_1_MICROSCOPIO_H
#define PROYECTO_1_MICROSCOPIO_H

#include "Equipo.h"

class Microscopio : public Equipo
{
public:
    Microscopio(bool esPrototipo = false);
    Microscopio(double crit, double tiempo);
    string getTipo() const;
    string getPrefix() const override;
    void leerDatos(stringstream &ss) override;
    Equipo* crear() override;
};


#endif //PROYECTO_1_MICROSCOPIO_H