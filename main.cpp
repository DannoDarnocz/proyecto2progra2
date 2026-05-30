#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <thread>
#include <chrono>
using namespace std;


void esperarEnter(bool = true);
int pedirDato(int,int,bool=true);
void limpiarBufer();
void recargarArchivo(string);

struct Menu
{
    int principal(int equipos, int incidencias)
    {
        cout << "- SISTEMA INTELIGENTE DE MANTENIMIENTO -"<<endl<<endl
        << "Equipos cargados en el sistema: " << equipos <<endl
        << "Incidencias cargadas en el sistema: " << incidencias <<endl	<<endl
        << "   1. Cargar datos desde archivos"<<endl
        << "   2. Agregar equipos manualmente"<<endl
        << "   3. Agregar incidencias manualmente"<<endl
        << "   4. Ver lista de equipos"<<endl
        << "   5. Ver lista de incidencias"<<endl
        << "   6. Ejecutar simulacion"<<endl<<endl;
        return pedirDato(1,6);
    }
};

int main()
{
}

void esperarEnter(bool msg) {
    if (msg) {
        cout << "Presione ENTER para continuar... ";
    }
    cin.ignore(100000, '\n');
}


int pedirDato(int min, int max, bool mostrarTexto) {
    int opcion;
    if (mostrarTexto) {
        cout << "Ingrese la opcion deseada: ";
    }

    // Repetir hasta que ingrese una opcion valida
    while (true) {
        cin >> opcion;
        // verificar que sea valido
        if (cin.fail()) {
            limpiarBufer();
            cout << "Entrada invalida. Por favor ingrese un numero: ";
            continue;
        }
        if (opcion < min || opcion > max) {
            cout << "Opcion fuera de rango. Ingrese un numero entre " << min << " y " << max << ": ";
            continue;
        }
        limpiarBufer();
        return opcion;
    }
}

void limpiarBufer() {
    cin.clear();
    // "numeric_limits" se usa para indicar la mayor cantidad posible de caracteres a ignorar en el bufer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void recargarArchivo(string ruta) {
    ofstream f(ruta,ios::trunc);
    if (!f) { throw ErrorArchivoLectura("Recarga de archivo fallida"); }
    f.close();
}

