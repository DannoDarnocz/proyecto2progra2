//
// Created by axela on 9/4/2026.
//

#include "../../cabeceras/excepciones/ErrorArchivoEscritura.h"

ErrorArchivoEscritura::ErrorArchivoEscritura() : ErrorArchivo("") {}

ErrorArchivoEscritura::ErrorArchivoEscritura(string mensaje) : ErrorArchivo(mensaje) {}

const char* ErrorArchivoEscritura::what() const noexcept
{
    static string resultado;
    resultado = "Ha ocurrido un error durante la escritura del archivo." + (msg.empty() ? string() : " (" + msg + ")");
    return resultado.c_str();
}

