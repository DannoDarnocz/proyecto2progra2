//
// Created by axel on 9/4/2026.
//

#ifndef PROYECTO_1_LAPTOP_H
#define PROYECTO_1_LAPTOP_H
#include "Equipo.h"


class Laptop : public Equipo {
public:
    Laptop(bool esPrototipo = false);
    Laptop(double crit, double tiempo);
    string getTipo() const;
    string getPrefix() const override;
    void leerDatos(stringstream &ss) override;
    Equipo* crear() override;
};


#endif //PROYECTO_1_LAPTOP_H