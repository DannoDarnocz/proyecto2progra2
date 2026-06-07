//
// Created by Daniel on 15/04/2026.
//

#include "../../headers/exceptions/ErrorValor.h"

// Store the complete message in the msg member variable during construction
// to avoid memory leaks from temporary string objects in what()
ErrorValor::ErrorValor() : msg("The entered value is invalid.") {}

ErrorValor::ErrorValor(string mensaje) : msg("The entered value is invalid." + (mensaje.empty() ? string() : " (" + mensaje + ")")) {}

const char* ErrorValor::what() const noexcept
{
    return msg.c_str();
}

string ErrorValor::obtenerMensaje() const {
    return msg;
}