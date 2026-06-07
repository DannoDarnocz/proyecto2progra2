//
// Created by axela on 9/4/2026.
//

#include "../../headers/exceptions/ErrorNegativo.h"

// Store the complete message in the msg member variable during construction
// to avoid memory leaks from temporary string objects in what()
ErrorNegativo::ErrorNegativo() : ErrorValor("The value must be positive.") {
    msg = "The value must be positive.";
}

ErrorNegativo::ErrorNegativo(string mensaje) : ErrorValor("") {
    msg = "The value must be positive." + (mensaje.empty() ? string() : " (" + mensaje + ")");
}

const char* ErrorNegativo::what() const noexcept
{
    return msg.c_str();
}