//
// Created by Daniel on 10/04/2026.
//

#ifndef PROYECTO_1_OSCILOSCOPIO_H
#define PROYECTO_1_OSCILOSCOPIO_H
#include "Equipo.h"

class Osciloscopio : public Equipo
{
public:
    Osciloscopio(bool esPrototipo = false);
    Osciloscopio(double crit, double tiempo);
    string getTipo() const;
    string getPrefix() const override;
    void leerDatos(stringstream &ss) override;
    Equipo* crear() override;
};


#endif //PROYECTO_1_OSCILOSCOPIO_H