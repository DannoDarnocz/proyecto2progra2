//
// Created by axela on 9/4/2026.
//

#include "../../headers/exceptions/FileExceptionOut.h"


// Store the complete message in the msg member variable during construction
// to avoid memory leaks from temporary string objects in what()

FileExceptionOut::FileExceptionOut(string specificMsg) : FileException("") {
    msg = "An error occurred while writing to the file." + (specificMsg.empty() ? "": " (" + specificMsg + ")");
}

const char* FileExceptionOut::what() const noexcept
{
    return msg.c_str();
}

