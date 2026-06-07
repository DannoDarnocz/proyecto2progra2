//
// Created by axela on 9/4/2026.
//

#include "../../headers/exceptions/ErrorCast.h"

// Store the complete message in the msg member variable during construction
// to avoid memory leaks from temporary string objects in what()
ErrorCast::ErrorCast() : msg("The cast could not be performed correctly.") {}

ErrorCast::ErrorCast(string mensaje) : msg("The cast could not be performed correctly." + (mensaje.empty() ? string() : " (" + mensaje + ")")) {}

const char* ErrorCast::what() const noexcept
{
    return msg.c_str();
}

string ErrorCast::obtenerMensaje() const {
    return msg;
}


