//
// Created by axela on 9/4/2026.
//

#ifndef PROYECTO_1_ERRORARCHIVO_H
#define PROYECTO_1_ERRORARCHIVO_H

#include <exception>
#include <string>

using namespace std;

class FileException : public exception {
    protected:
    string msg;
    public:
    FileException(string specificMsg = "");
    const char* what() const noexcept override;
    string obtenerMensaje() const;
};


#endif //PROYECTO_1_ERRORARCHIVO_H