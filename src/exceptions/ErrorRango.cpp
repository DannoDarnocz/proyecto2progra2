//
// Created by Daniel on 15/04/2026.
//
//
#include "../../headers/exceptions/ErrorRango.h"

// Store the complete message in the msg member variable during construction
// to avoid memory leaks from temporary string objects in what()
ErrorRango::ErrorRango() : ErrorValor("The value is out of the allowed range.") {
}

ErrorRango::ErrorRango(string mensaje) : ErrorValor(    msg = "The value is out of the allowed range." + (mensaje.empty() ? string() : " (" + mensaje + ")")) {
}

const char* ErrorRango::what() const noexcept
{
    return msg.c_str();
}