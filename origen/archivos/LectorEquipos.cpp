//
// Created by Daniel on 17/04/2026.
//

#include "../../cabeceras/archivos/LectorEquipos.h"

#include "../../cabeceras/equipos/AllInOne.h"
#include "../../cabeceras/equipos/ComputadoraEscritorio.h"
#include "../../cabeceras/equipos/Laptop.h"
#include "../../cabeceras/equipos/Microscopio.h"
#include "../../cabeceras/equipos/Osciloscopio.h"
#include "../../cabeceras/excepciones/ErrorArchivoLectura.h"

//Para mantener OCP y evitar If-Else, se definen las posibles derivadas para obtener el tipo al leer archivo
Equipo* prototipos[] = { //Funciona similar a un enum, pero al necesitar en especifico el prefijo, se obtiene al llamar el prototipo
    new Microscopio(true),
    new ComputadoraEscritorio(true),
    new Osciloscopio(true),
    new AllInOne(true),
    new Laptop(true)
};
int numPrototipos = sizeof(prototipos) / sizeof(prototipos[0]); //Tamaño en bytes del array / tamaño de 1 en especifico en bytes

ListaEquipo * LectorEquipos::leerArchivo(string nombreArchivo, ListaEquipo* le) const {
    ifstream f(nombreArchivo);
    if (!f) {
        throw ErrorArchivoLectura(nombreArchivo);
    }
    if (!le) { le = new ListaEquipo(); }
    ListaEquipo* lista = le; //Guarda lista que ya existia, sino existe es una lista nueva
    string linea;
    while (getline(f,linea)) {
        //Formato: id,crit,tiempo;
        stringstream ss(linea);
        stringstream x(linea);
        string tipo;
        getline(ss,tipo,'-');
        for (int i=0;i<numPrototipos;i++) {
            if (prototipos[i]->getPrefix() == tipo) {
                Equipo* equipo = prototipos[i]->crear(); //Se crea a si mismo, pero del tipo especifico
                equipo->leerDatos(x); //Se guardan los datos del archivo directamente en el objeto
                lista->insertarFinal(equipo); //Y se inserta el equipo con los datos del archivo en la lista
                break;
            }
        }
        //Se respeta OCP debido a que solo se debe ingresar un nuevo prototipo de Equipo y funcionara igual
        //Se guarda automaticamente los datos de los archivos en una lista de equipos siempre y cuando el archivo
        //Respete el formato.
    }
    f.close();
    return lista;
}

