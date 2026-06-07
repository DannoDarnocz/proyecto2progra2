//
// Created by axela on 9/4/2026.
//

#ifndef PROYECTO_1_ERRORNEGATIVO_H
#define PROYECTO_1_ERRORNEGATIVO_H

#include "ErrorValor.h"

using namespace std;

class ErrorNegativo : public ErrorValor  {
    public:
    ErrorNegativo();
    ErrorNegativo(string mensaje);
    const char* what() const noexcept override;
};


#endif //PROYECTO_1_ERRORNEGATIVO_H