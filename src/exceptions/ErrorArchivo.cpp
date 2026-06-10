//
// Created by axela on 9/4/2026.
//

#include "../../headers/exceptions/ErrorArchivo.h"

// Store the complete message in the msg member variable during construction
// to avoid memory leaks from temporary string objects in what()
ErrorArchivo::ErrorArchivo(string specificMsg) : msg("An error occurred while manipulating the file." + (specificMsg.empty() ? "" : " (" +specificMsg + ")")) {}

const char* ErrorArchivo::what() const noexcept
{
    return msg.c_str();
}

string ErrorArchivo::obtenerMensaje() const {
    return msg;
}
