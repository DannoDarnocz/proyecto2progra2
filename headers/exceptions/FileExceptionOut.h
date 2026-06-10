//
// Created by axela on 9/4/2026.
//

#ifndef PROYECTO_1_ERRORARCHIVOESCRITURA_H
#define PROYECTO_1_ERRORARCHIVOESCRITURA_H

#include "FileException.h"

class FileExceptionOut : public FileException {
public:
    FileExceptionOut(string specificMsg = "");
    const char* what() const noexcept override;
};


#endif //PROYECTO_1_ERRORARCHIVOESCRITURA_H