//
// Created by axela on 9/4/2026.
//

#ifndef PROYECTO_1_ERRORARCHIVOLECTURA_H
#define PROYECTO_1_ERRORARCHIVOLECTURA_H
#include "ErrorArchivo.h"


class ErrorArchivoLectura : public ErrorArchivo {
public:
    ErrorArchivoLectura();
    ErrorArchivoLectura(string mensaje);
    const char* what() const noexcept override;
};


#endif //PROYECTO_1_ERRORARCHIVOLECTURA_H