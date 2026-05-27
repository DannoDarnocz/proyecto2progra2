//
// Created by axela on 9/4/2026.
//

#include "../../cabeceras/excepciones/ErrorArchivoLectura.h"

ErrorArchivoLectura::ErrorArchivoLectura() : ErrorArchivo("") {}

ErrorArchivoLectura::ErrorArchivoLectura(string mensaje) : ErrorArchivo(mensaje) {}

const char* ErrorArchivoLectura::what() const noexcept
{
    static string resultado;
    resultado = "Ha ocurrido un error durante la lectura del archivo." + (msg.empty() ? string() : " (" + msg + ")");
    return resultado.c_str();
}