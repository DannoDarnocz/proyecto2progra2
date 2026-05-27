//
// Created by Daniel on 15/04/2026.
//

#include "../../cabeceras/mantenimientos/MantenimientoSoftware.h"

#include "../../cabeceras/equipos/Osciloscopio.h"
#include "../../cabeceras/equipos/Microscopio.h"
#include "../../cabeceras/mantenimientos/MantenimientoDecorador.h"
#include "../../cabeceras/excepciones/ErrorCast.h"


string MantenimientoSoftware::descripcion() const
{
   return mant->descripcion() + " + Mantenimiento de software";
};
void MantenimientoSoftware::arreglar(Equipo *e, int dia)
{
   if (dynamic_cast <Osciloscopio*>(e)|| dynamic_cast<Microscopio*>(e))
      throw ErrorCast("El mantenimiento de software no es compatible con osciloscopios ni microscopios");
   mant->arreglar(e, dia);
   e->setCriticidad(e->getCriticidad()-20); // puede quedar negativo sin problema
};