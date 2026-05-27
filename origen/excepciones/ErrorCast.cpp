//
// Created by axela on 9/4/2026.
//

#include "../../cabeceras/excepciones/ErrorCast.h"

ErrorCast::ErrorCast() : msg("") {}

ErrorCast::ErrorCast(string mensaje) : msg(mensaje) {}

const char* ErrorCast::what() const noexcept
{
    static string resultado;
    resultado = "El casteo no se pudo hacer de forma correcta." + (msg.empty() ? string() : " (" + msg + ")");
    return resultado.c_str();
}

string ErrorCast::obtenerMensaje() const {
    return msg;
}

