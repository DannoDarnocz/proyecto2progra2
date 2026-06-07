//
// Created by axela on 9/4/2026.
//

#include "../../headers/exceptions/ErrorDecimal.h"

// Store the complete message in the msg member variable during construction
// to avoid memory leaks from temporary string objects in what()
ErrorDecimal::ErrorDecimal() : ErrorValor("The value cannot be decimal.") {
}

ErrorDecimal::ErrorDecimal(string mensaje) : ErrorValor("The value cannot be decimal." + (mensaje.empty() ? string() : " (" + mensaje + ")")){};

const char* ErrorDecimal::what() const noexcept
{
    return msg.c_str();
}
