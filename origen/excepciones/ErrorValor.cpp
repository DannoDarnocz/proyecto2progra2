//
// Created by Daniel on 15/04/2026.
//

#include "../../cabeceras/excepciones/ErrorValor.h"

ErrorValor::ErrorValor() : msg("") {}

ErrorValor::ErrorValor(string mensaje) : msg(mensaje) {}

const char* ErrorValor::what() const noexcept
{
    static string resultado;
    resultado = "El valor ingresado es invalido." + (msg.empty() ? string() : " (" + msg + ")");
    return resultado.c_str();
}

string ErrorValor::obtenerMensaje() const {
    return msg;
}