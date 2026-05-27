//
// Created by axel on 9/4/2026.
//

#ifndef PROYECTO_1_COMPUTADORAESCRITORIO_H
#define PROYECTO_1_COMPUTADORAESCRITORIO_H
#include "Equipo.h"


class ComputadoraEscritorio : public Equipo {
public:
    ComputadoraEscritorio(bool esPrototipo = false);
    ComputadoraEscritorio(double crit, double tiempo);
    string getTipo() const;
    string getPrefix() const override;
    void leerDatos(stringstream &ss) override;
    Equipo* crear() override;
};


#endif //PROYECTO_1_COMPUTADORAESCRITORIO_H