//
// Created by axel on 9/4/2026.
//

#ifndef PROYECTO_1_ALLINONE_H
#define PROYECTO_1_ALLINONE_H
#include "Equipo.h"


class AllInOne : public Equipo {
public:
    AllInOne(bool esPrototipo = false);
    AllInOne(double crit, double tiempo);
    string getTipo() const;
    string getPrefix() const override;
    void leerDatos(stringstream &ss) override;
    Equipo* crear() override;
};


#endif //PROYECTO_1_ALLINONE_H