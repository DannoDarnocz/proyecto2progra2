//
// Created by Daniel on 17/04/2026.
//

#include "../../cabeceras/archivos/LectorIncidencias.h"
#include "../../cabeceras/excepciones/ErrorArchivoLectura.h"

ListaIncidencia* LectorIncidencias::leerArchivo(string nombreArchivo, ListaIncidencia* li) const
{
    ifstream f(nombreArchivo);

    if (!f)
    {
        throw ErrorArchivoLectura(nombreArchivo);
    }

    if (!li) { li = new ListaIncidencia(); }
    ListaIncidencia* lista = li;

    int severidad;
    while (f >> severidad)
    {
        //nullptr porque aun no se asigna a ninguna, y dia 0 porque es cuando empieza la simulacion
        Incidencia* incidencia = new Incidencia(nullptr,severidad,0);
        lista->insertarFinal(incidencia);
    }
    f.close();
    return lista;
}
