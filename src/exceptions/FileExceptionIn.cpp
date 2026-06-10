//
// Created by axela on 9/4/2026.
//

#include "../../headers/exceptions/FileExceptionIn.h"

// Store the complete message in the msg member variable during construction
// to avoid memory leaks from temporary string objects in what()

FileExceptionIn::FileExceptionIn(string specificMsg) {
    msg = "An error occurred while reading the file." + (specificMsg.empty() ? "" : " (" + specificMsg + ")");
}

const char* FileExceptionIn::what() const noexcept
{
    return msg.c_str();
}