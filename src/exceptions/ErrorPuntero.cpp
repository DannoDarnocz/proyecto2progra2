//
// Created by Daniel on 17/04/2026.
//

#include "../../headers/exceptions/ErrorPuntero.h"

// Store the complete message in the msg member variable during construction
// to avoid memory leaks from temporary string objects in what()
ErrorPuntero::ErrorPuntero() : msg("The pointer that was attempted to be accessed is null.") {}

ErrorPuntero::ErrorPuntero(string mensaje) : msg("The pointer that was attempted to be accessed is null." + (mensaje.empty() ? string() : " (" + mensaje + ")")) {}

const char* ErrorPuntero::what() const noexcept
{
    return msg.c_str();
}

string ErrorPuntero::obtenerMensaje() const {
    return msg;
}

