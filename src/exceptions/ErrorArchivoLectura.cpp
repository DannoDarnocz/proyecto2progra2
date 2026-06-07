//
// Created by axela on 9/4/2026.
//

#include "../../headers/exceptions/ErrorArchivoLectura.h"

// Store the complete message in the msg member variable during construction
// to avoid memory leaks from temporary string objects in what()
ErrorArchivoLectura::ErrorArchivoLectura() {
    msg = "An error occurred while reading the file.";
}

ErrorArchivoLectura::ErrorArchivoLectura(string mensaje) {
    msg = "An error occurred while reading the file." + (mensaje.empty() ? string() : " (" + mensaje + ")");
}

const char* ErrorArchivoLectura::what() const noexcept
{
    return msg.c_str();
}