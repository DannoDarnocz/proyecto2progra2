//
// Created by axela on 9/4/2026.
//

#ifndef PROYECTO_1_ERRORCAST_H
#define PROYECTO_1_ERRORCAST_H

#include <exception>
#include <string>

using namespace std;

class ErrorCast : public exception {
    protected:
    string msg;
    public:
    ErrorCast();
    ErrorCast(string mensaje);
    const char* what() const noexcept override;
    string obtenerMensaje() const;
};


#endif //PROYECTO_1_ERRORCAST_H