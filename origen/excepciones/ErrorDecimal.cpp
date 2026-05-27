//
// Created by axela on 9/4/2026.
//

#include "../../cabeceras/excepciones/ErrorDecimal.h"

ErrorDecimal::ErrorDecimal() : ErrorValor("") {}

ErrorDecimal::ErrorDecimal(string mensaje) : ErrorValor(mensaje) {}

const char* ErrorDecimal::what() const noexcept
{
    static string resultado;
    resultado = "El valor no puede ser decimal." + (msg.empty() ? string() : " (" + msg + ")");
    return resultado.c_str();
}
