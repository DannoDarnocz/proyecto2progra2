//
// Created by Daniel on 15/04/2026.
//
//
#include "../../cabeceras/excepciones/ErrorRango.h"

ErrorRango::ErrorRango() : ErrorValor("") {}

ErrorRango::ErrorRango(string mensaje) : ErrorValor(mensaje) {}

const char* ErrorRango::what() const noexcept
{
    static string resultado;
    resultado = "El valor esta fuera del rango permitido." + (msg.empty() ? string() : " (" + msg + ")");
    return resultado.c_str();
}