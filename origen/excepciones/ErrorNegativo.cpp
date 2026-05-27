//
// Created by axela on 9/4/2026.
//

#include "../../cabeceras/excepciones/ErrorNegativo.h"

ErrorNegativo::ErrorNegativo() : ErrorValor("") {}

ErrorNegativo::ErrorNegativo(string mensaje) : ErrorValor(mensaje) {}

const char* ErrorNegativo::what() const noexcept
{
    static string resultado;
    resultado = "El valor debe de ser positivo." + (msg.empty() ? string() : " (" + msg + ")");
    return resultado.c_str();
}