//
// Created by axela on 9/4/2026.
//

#include "../../headers/exceptions/ErrorArchivoEscritura.h"

// TODO: fix shitty ass parent invocations that claude gave me wtf

// Store the complete message in the msg member variable during construction
// to avoid memory leaks from temporary string objects in what()
ErrorArchivoEscritura::ErrorArchivoEscritura() : ErrorArchivo("An error occurred while writing to the file.") {
    msg = "An error occurred while writing to the file.";
}

ErrorArchivoEscritura::ErrorArchivoEscritura(string mensaje) : ErrorArchivo("") {
    msg = "An error occurred while writing to the file." + (mensaje.empty() ? string() : " (" + mensaje + ")");
}

const char* ErrorArchivoEscritura::what() const noexcept
{
    return msg.c_str();
}

