//
// Created by Daniel on 15/04/2026.
//

#include "../../cabeceras/mantenimientos/MantenimientoCambio.h"

string MantenimientoCambio::descripcion() const
{
    return mant->descripcion() + " + Cambio de componentes";
};
void MantenimientoCambio::arreglar(Equipo *e, int dia)
{
    mant->arreglar(e, dia);
    e->setCriticidad(e->getCriticidad()-50); // puede quedar negativo sin problema
};