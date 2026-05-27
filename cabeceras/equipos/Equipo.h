//
// Created by Daniel on 08/04/2026.
//

#ifndef PROYECTO_1_EQUIPO_H
#define PROYECTO_1_EQUIPO_H
#include <iostream>
#include <string>
#include <sstream>
#include "../listas/ListaIncidencia.h"
#include "../Incidencia.h"
using namespace std;

class ListaIncidencia;
class Incidencia;

class Equipo {
protected:
    static int contador; //cuenta cuantos equipos se han creado
    string id;
    int diaMantenimiento; // dia en el cual se le hizo el ultimo mantenimiento
    float criticidad;
    ListaIncidencia* incidencias;
public:
    Equipo(double crit, int diaMant, bool esProto = false);
    virtual ~Equipo() = default;
    //Gets
    string getId() const;
    int getDiaMant() const;
    float getCriticidad() const;
    virtual string getPrefix() const = 0; //Prefijo que se le agrega a las ID
    Incidencia* obtenerIncidencia(int pos) const;
    ListaIncidencia* obtenerListaIncidencia() const;
    void eliminarIncidencias();
    //Sets
    void setCriticidad(float criticidad);
    void setDiaMantenimiento(int diaMantenimiento);
    //Generales
    void generarId(); //Genera nueva ID según el tipo de Equipo de las derivadas
    int tiempoInactivo(int diaActual) const; //Devuelve cantidad de tiempo sin mantenimiento
    int cantidadIncidencias() const; //Devuelve cantidad de incidencias existentes
    double calcPrioridad(int) const;    //Calcula su nivel de prioridad
    void aplicarDegradacion(int dia); //Aplica degradacion al equipo en un dia especifico
    virtual string getTipo() const = 0; //Devuelve tipo de las hijas
    virtual string toString(int) const; //Devuelve todos los atributos + la prioridad
    virtual void leerDatos(stringstream& ss) = 0; //Lee datos enviados desde el archivo para copiar
    virtual Equipo* crear() = 0; //Se crea a si misma
    static int getContador();

};


#endif //PROYECTO_1_EQUIPO_H

