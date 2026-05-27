//
// Created by Daniel on 15/04/2026.
//

#ifndef PROYECTO_1_ERRORVALOR_H
#define PROYECTO_1_ERRORVALOR_H

#include <exception>
#include <string>
using namespace std;

class ErrorValor : public exception
{
    protected:
    string msg;
    public:
    ErrorValor();
    ErrorValor(string mensaje);
    const char* what() const noexcept override;
    string obtenerMensaje() const;
};


#endif //PROYECTO_1_ERRORVALOR_H