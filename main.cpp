#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <thread>
#include <chrono>
#include "cabeceras/equipos/AllInOne.h"
#include "cabeceras/listas/ListaEquipo.h"
#include "cabeceras/excepciones/ErrorDecimal.h"
#include "cabeceras/excepciones/ErrorNegativo.h"
#include "cabeceras/excepciones/ErrorCast.h"
#include "cabeceras/excepciones/ErrorRango.h"
#include "cabeceras/equipos/Laptop.h"
#include "cabeceras/equipos/ComputadoraEscritorio.h"
#include "cabeceras/excepciones/ErrorArchivo.h"
#include "cabeceras/equipos/Osciloscopio.h"
#include "cabeceras/equipos/Microscopio.h"
#include "cabeceras/archivos/LectorEquipos.h"
#include "cabeceras/archivos/LectorIncidencias.h"
#include "cabeceras/excepciones/ErrorArchivoLectura.h"
#include "cabeceras/excepciones/ErrorPuntero.h"
#include "cabeceras/mantenimientos/Mantenimiento.h"
#include "cabeceras/mantenimientos/MantenimientoBase.h"
#include "cabeceras/mantenimientos/MantenimientoCambio.h"
#include "cabeceras/mantenimientos/MantenimientoSoftware.h"
using namespace std;

void sorteoIncidencias(ListaEquipo*,int,
    ListaIncidencia*);
Mantenimiento* crearMantenimiento(int tipo);
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
    int reparacion() {
        cout << "- REPARACION DE EQUIPOS -" << endl<<endl
        << "   1. Reparacion manual"<<endl
        << "   2. Reparacion automatica"<<endl<<endl;
        return pedirDato(1,2);
    }
    int finalizar() {
        cout << "- MOSTRAR INFORMACION FINAL -" << endl << endl
        << "   1. Mostrar equipos"          << endl
        << "   2. Mostrar incidencias"       << endl
        << "   3. Mostrar equipo especifico" << endl
        << "   4. Estado global al finalizar"<< endl
        << "   5. Mostrar registros"         << endl
        << "   0. Salir"                     << endl << endl;
        return pedirDato(0, 5);
    }
};

int main()
{
    srand(time(NULL)); // generar nueva semilla
    cout << "\n";
    ListaEquipo* equipos = new ListaEquipo();
    ListaIncidencia* incidencias = new ListaIncidencia();
    try
    {
        recargarArchivo("../registrosNuevo.txt"); //Recarga un archivo para vaciarlo
    }
    catch (ErrorArchivo& e)
    {
        cout << e.what() << endl;
    }
    // Menu principal
    bool repetir = true;
    int dato;
    bool cargado = false;
    Menu menu;

    while (repetir)
    {
        dato = menu.principal(equipos->getTam(),incidencias->getTam());
        switch (dato)
        {
        case 1:
            if (!cargado) {
                LectorEquipos lectorEquipos;
                LectorIncidencias lectorIncidencias;

                try{
                    equipos = lectorEquipos.leerArchivo("../equipos.txt", equipos);
                    incidencias = lectorIncidencias.leerArchivo("../incidencias.txt",incidencias);
                    cout << "Se han cargado los datos con exito." << endl;
                    cargado = true;
                }
                catch (ErrorArchivoLectura& e)
                {
                    cout << e.what() << endl;
                }
            } else { cout << "Los datos ya han sido cargados" << endl; }
            break;
        case 2:
            // agregar nuevo equipo a mano
            while (true)
            {
                cout << "- AGREGAR NUEVO EQUIPO -"<<endl<<endl
                << "Tipos de equipo: " << endl
                << "   1. Laptop"<<endl
                << "   2. Computadora de escritorio"<<endl
                << "   3. Computadora All-In-One"<<endl
                << "   4. Microscopio"<<endl
                << "   5. Osciloscopio"<<endl
                << "   0. Salir"<<endl<<endl;
                dato = pedirDato(0,5);

                if (dato==0) break;

                try {
                    switch (dato)
                    {
                    case 1:
                        equipos->insertarFinal(new Laptop);
                        break;
                    case 2:
                        equipos->insertarFinal(new ComputadoraEscritorio);
                        break;
                    case 3:
                        equipos->insertarFinal(new AllInOne);
                        break;
                    case 4:
                        equipos->insertarFinal(new Microscopio);
                        break;
                    case 5:
                        equipos->insertarFinal(new Osciloscopio);
                        break;
                    }
                    cout<< "Equipo agregado exitosamente."<<endl;
                }
                catch (ErrorValor& e) {
                    cout << e.what()  << endl;
                }
                catch (ErrorPuntero& e) {
                    cout << e.what()  << endl;
                }
            }
            break;
        case 3: // agregar incidencia
            while (true){
                try
                {
                    string severidad;
                    int s;

                    cout << "Se va a crear una incidencia con ID " << incidencias->getTam()<< endl
                    << "Ingrese la severidad de la incidencia (0- salir, 1- baja, 2- media, 3- alta): ";
                    dato = pedirDato(0,3,false);
                    if (dato==0) break;

                    s=dato-1; // uno menor a lo que se le muestra el usuario
                    Incidencia* nuevaIncidencia = new Incidencia(nullptr,s,0);
                    incidencias->insertarFinal(nuevaIncidencia);
                    cout << "Se ha creado la incidencia con exito. " << endl << endl;
                } catch (ErrorValor& e)
                {
                    cout << e.what() << endl;
                }
                catch (ErrorPuntero& e) {
                    cout << e.what()  << endl;
                }
            }
            break;
        case 4: // lista equipos
            cout << equipos->toString(0)<<endl;
            break;
        case 5: // lista incidentes
            cout << incidencias->toString()<<endl;
            break;
        case 6: // ejecutar simulacion
            if (equipos->getTam()<3) {
                cout << "Se requiere un minimo de 3 computadoras."<<endl;
            }
            else
            {
                repetir=false;
                continue;
            }
            break;
        }
        esperarEnter();
    }

    cout << "\n\n";
    // Sorteo inicial de 300 incidencias
    int dia=0;
    sorteoIncidencias(equipos,300,incidencias);
    cout << "\n";
    equipos->ordenarPrioridad(dia);
    cout << equipos->toString(dia);
    //cout << "\n\n";
    //cout << incidencias->toString(); //Visualizar equipos asignados a incidencias correctamente
    cout << "\n\n";
    cout << "Equipos han sido ordenados y las incidencias han sido sorteadas.\nPresione ENTER para proceder con la simulacion.";
    esperarEnter(false);

    //Contador de equipos atendidos
    int contador=0;

    // lista para almacenar 3 equipos a los que se les hará mantenimiento
    Equipo** equiposMant = new Equipo*[3];
    for (int i=0;i<3;i++)
        equiposMant[i] = nullptr; // para que no queden viendo a basura

    // simulacion
    for (dia=1;dia<=30;dia++)
    {

        // array pr

        stringstream resultado;
        cout << " --- DIA " << dia << " ---" <<endl<<endl
        << "Equipos con mayor prioridad"<<endl;

        //Mostrar equipos a reparar
        for (int i=0;i<equipos->getTam()&&i<3;i++)
        {
            Equipo* actual = nullptr;
            NodoEquipo* nodoActual = equipos->buscarPorPos(i);
            if (nodoActual) {
                actual = nodoActual->getEquipo();
                cout << actual->toString(dia) << endl;
                equiposMant[i] = actual; //Guarda los 3 primeros de la lista global
            }
        }
        cout << "\n\n"<<"Presione ENTER para proceder con el mantenimiento.";

        esperarEnter(false);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        //Reparacion
        dato = menu.reparacion();
        switch (dato) {
            case 1: {
                int cont=0;
                while (cont < 3) {
                    cout << endl <<"- REPARA EQUIPO " << (cont+1) << "-"<<endl
                    <<equiposMant[cont]->toString(dia)<<endl<<endl
                    << "Tipos de Mantenimiento: " << endl
                    << "   1. Basico"<<endl
                    << "   2. Basico + Cambio Componentes"<<endl
                    << "   3. Basico + Software"<<endl
                    << "   4. Basico + Cambio Componentes + Software"<<endl<<endl;
                    dato = pedirDato(1,4);
                    try {
                        //Valida Equipo
                        Equipo* eqMant = equiposMant[cont];
                        if (!eqMant) { throw ErrorPuntero();}
                        //Crea Mantenimiento requerido por el usuario
                        Mantenimiento* m = crearMantenimiento(dato);
                        cout << "Tipo de Mantenimiento: " << m->descripcion() << endl;
                        m->arreglar(eqMant, dia);
                        delete m; //Libera memoria
                        cont++;
                        cout << "Equipo reparado correctamente"<<endl;
                        // esto es el equivalente de sleep que sirve para todos los OS
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    } catch (ErrorValor& e) {
                        cout << e.what() << endl;
                    } catch (ErrorPuntero& e) {
                        cout << e.what() << endl;
                    } catch (ErrorCast& e) {
                        cout << e.what() << endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                }
                break;
            }
            case 2: {
                for (int i=0;i<3;i++) {
                    int tipo;
                    try {
                        //Valida Equipo
                        Equipo* eqMant = equiposMant[i];
                        if (!eqMant) { throw ErrorPuntero();}
                        if (eqMant->getTipo()=="Osciloscopio" || eqMant->getTipo()=="Microscopio") {
                            tipo = (rand() % 2) + 1; // solo basico o cambio de componentes
                        } else {
                            tipo = (rand() % 4) + 1; // cualquiera de los 4 tipos
                        }
                        //Crea Mantenimiento requerido por el usuario
                        Mantenimiento* m = crearMantenimiento(tipo);
                        cout << "Tipo de Mantenimiento: " << m->descripcion() << endl;
                        m->arreglar(eqMant, dia);
                        delete m; //Libera memoria
                        cout << "Equipo reparado correctamente"<<endl;
                        cout << "\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    } catch (ErrorValor& e) {
                        cout << e.what() << endl;
                    } catch (ErrorPuntero& e) {
                        cout << e.what() << endl;
                    }
                }
                break;
            }
        }
        esperarEnter();

        // Reporte final

        try
        {
            resultado << "---- REPORTE DEL DIA " << dia << " ----"<< endl<< endl
            << "Equipos atendidos: 3" << endl<< endl
            << "Resultados:" << endl;

            // equipos mantenidos
            for (int i=0;i<3;i++)
            {
                if (!equiposMant[i]) throw ErrorPuntero("Equipo en mantenimiento es nulo");
                resultado<<equiposMant[i]->toString(dia)<<endl;
            }

            resultado <<endl<< "Equipos pendientes de atencion (prioridad mayor a 0): " << equipos->equiposPendientes(dia) << endl
            << "Riesgo global del laboratorio (promedio de prioridades): " << equipos->promedioPrioridad(dia) << endl << endl;
            cout << resultado.str();
            ofstream f("../registros.txt",ios::app); //El registro se guarda encima de un registro viejo
            ofstream g("../registrosNuevo.txt",ios::app); //Registro que guarda solo la de 1 iteración

            if (!f || !g)
            {
                throw ErrorArchivo();
            }

            string dato;
            Equipo* encontrado;
            while (true)
            {
                cout<< endl<<"Ingrese el ID de un equipo para mostrar su estado actual (ENTER para seguir simulacion): ";
                getline(cin,dato);
                if (dato=="") break;
                encontrado=equipos->buscarPorId(dato);
                if (!encontrado)
                {
                    cout <<"No se encontro un equipo con el ID ingresado.";
                }
                else
                {
                    cout << encontrado->toString(dia) << endl;
                }

            }

            f << resultado.str();
            g << resultado.str();


            f.close();
            g.close();
        }
        catch (ErrorArchivo& e)
        {
            cout << e.what() << endl;
        }
        catch (ErrorPuntero& e)
        {
            cout << e.what() << endl;
        }

        // finalizar dia degradando y ordenando
        equipos->degradarTodos(dia);
        equipos->ordenarPrioridad(dia);
        //cout << equipos->toString(dia); //Puede usarse para revisar que se haya hecho los mantenimientos y degradacion
        contador = contador + 3;
    }

    repetir = true;
    while (repetir)
    {
        dato = menu.finalizar();
        switch (dato)
        {
            case 1: // Mostrar equipos
                cout << equipos->toString(30);
                break;
            case 2: // Mostrar incidencias
                cout << incidencias->toString();
                break;
            case 3: {
                // Mostrar equipo especifico
                string dato;
                Equipo* encontrado;
                while (true) {
                    cout<< endl<<"Ingrese el ID de un equipo para mostrar su estado actual (ENTER para continuar): ";
                    getline(cin,dato);
                    if (dato=="") break;
                    encontrado=equipos->buscarPorId(dato);
                    if (!encontrado) { cout <<"No se encontro un equipo con el ID ingresado."; }
                    else { cout << encontrado->toString(dia) << endl; }
                }
                break;
            }
            case 4: // Estado global al finalizar
                cout << "- ESTADO GLOBAL -" << endl;
                cout << "Equipos atendidos: "<< contador << endl << "Resultados:" << endl;
                cout << "Equipos pendientes de atencion (prioridad mayor a 0): " << equipos->equiposPendientes(dia) << endl
                << "Riesgo global del laboratorio (promedio de prioridades): " << equipos->promedioPrioridad(dia) << endl << endl;
                break;
            case 5:
                try {
                    ifstream archivo("../registrosNuevo.txt");
                    if (!archivo.is_open()) throw ErrorArchivoLectura("No se pudo abrir el archivo");
                    string linea;
                    while (getline(archivo, linea)) {
                        cout << linea << endl;
                    }
                    archivo.close();
                }
                catch (ErrorArchivoLectura& e) {
                    cout << e.what() << endl;
                }
                break;
            case 0: // Salir
                repetir = false;
                continue;
        }
        if (dato!=3) { esperarEnter();}
    }

    cout  << "La simulacion ha finalizado." << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    delete equipos;
    // no se borran incidencias porque cada equipo borraba la suya al aplicar mantenimiento
    delete[] equiposMant;
}

//Función para registrar las incidencias cargadas por primera vez en los equipos de forma automática
void sorteoIncidencias(ListaEquipo* l, int cantidad, ListaIncidencia* inci) {
    try {
        if (cantidad<=0) { throw ErrorNegativo(); }
        NodoEquipo* ne = l->getPrimero();
        NodoIncidencia* ni = inci->getPrimero();
        for (int i=0;i<cantidad;i++) {
            if (!ne) { break;} //Nodo Equipos
            if (!ni) { break;} //Nodo Incidencias
            Equipo* E = ne->getEquipo();
            if (!E) { ne = ne->sig; continue;}
            if (E->getCriticidad() <= 100 && E->getCriticidad() > 80) {
                for (int j=0;j<9;j++) {
                    if (!ni) { break;}
                    E->obtenerListaIncidencia()->insertarFinal(ni->getIncidencia());
                    ni->getIncidencia()->setEquipo(E);
                    ni = ni->getSig();
                }
            } else if (E->getCriticidad() <= 80 && E->getCriticidad() > 55) {
                for (int j=0;j<7;j++) {
                    if (!ni) { break;}
                    E->obtenerListaIncidencia()->insertarFinal(ni->getIncidencia());
                    ni->getIncidencia()->setEquipo(E);
                    ni = ni->getSig();
                }
            } else if (E->getCriticidad() <= 55 && E->getCriticidad() > 30) {
                for (int j=0;j<5;j++) {
                    if (!ni) { break;}
                    E->obtenerListaIncidencia()->insertarFinal(ni->getIncidencia());
                    ni->getIncidencia()->setEquipo(E);
                    ni = ni->getSig();
                }
            } else if (E->getCriticidad() <= 30 && E->getCriticidad() > 0) {
                for (int j=0;j<3;j++) {
                    if (!ni) { break;}
                    E->obtenerListaIncidencia()->insertarFinal(ni->getIncidencia());
                    ni->getIncidencia()->setEquipo(E);
                    ni = ni->getSig();
                }
            }
            ne = ne->sig;
        }
        cout << "Se han sorteado "  << cantidad << " incidencias correctamente." << endl;
    }
    catch (ErrorNegativo& e) {
        cout << e.what() << endl;
    }
    catch (exception& e) {
        cout << "Ocurrio un error inesperado al sortear las incidencias." << endl;
    }
}

//Funcion que retorna el tipo de mantenimiento
Mantenimiento* crearMantenimiento(int tipo) {
    switch (tipo) {
        case 1: return new MantenimientoBase();
        case 2: return new MantenimientoCambio(new MantenimientoBase());
        case 3: return new MantenimientoSoftware(new MantenimientoBase());
        case 4: return new MantenimientoCambio(new MantenimientoSoftware(new MantenimientoBase()));
        default: throw ErrorValor("Tipo invalido");
    }
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

