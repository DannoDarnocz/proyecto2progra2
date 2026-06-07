//
// Created by Daniel on 15/04/2026.
//

#ifndef PROYECTO_1_ERRORRANGO_H
#define PROYECTO_1_ERRORRANGO_H


#include "ErrorValor.h"

using namespace std;

class ErrorRango : public ErrorValor {
public:
    ErrorRango();
    ErrorRango(string mensaje);
    const char* what() const noexcept override;
};

#endif //PROYECTO_1_ERRORRANGO_H