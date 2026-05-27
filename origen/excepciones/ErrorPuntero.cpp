//
// Created by Daniel on 17/04/2026.
//

#include "../../cabeceras/excepciones/ErrorPuntero.h"

ErrorPuntero::ErrorPuntero() : msg("") {}

ErrorPuntero::ErrorPuntero(string mensaje) : msg(mensaje) {}

const char* ErrorPuntero::what() const noexcept
{
    static string resultado;
    resultado = "El puntero al cual se ha intentado acceder es nulo" + (msg.empty() ? string() : " (" + msg + ")");
    return resultado.c_str();
}

string ErrorPuntero::obtenerMensaje() const {
    return msg;
}

