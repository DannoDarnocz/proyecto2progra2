//
// Created by Daniel on 17/04/2026.
//

#ifndef PROYECTO_1_ERRORPUNTERO_H
#define PROYECTO_1_ERRORPUNTERO_H

#include <exception>
#include <string>
using namespace std;

class ErrorPuntero : public exception
{
    protected:
    string msg;
    public:
    ErrorPuntero();
    ErrorPuntero(string mensaje);
    const char* what() const noexcept override;
    string obtenerMensaje() const;
};


#endif //PROYECTO_1_ERRORPUNTERO_H

