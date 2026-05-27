//
// Created by axela on 9/4/2026.
//

#include "../../cabeceras/excepciones/ErrorArchivo.h"

ErrorArchivo::ErrorArchivo() : msg("") {}

ErrorArchivo::ErrorArchivo(string mensaje) : msg(mensaje) {}

const char* ErrorArchivo::what() const noexcept
{
    static string resultado;
    resultado = "Ha ocurrido un error durante la manipulacion del archivo." + (msg.empty() ? string() : " (" + msg + ")");
    return resultado.c_str();
}

string ErrorArchivo::obtenerMensaje() const {
    return msg;
}
