//
// Created by axela on 9/4/2026.
//

#include "../../cabeceras/listas/ListaIncidencia.h"
#include "../../cabeceras/excepciones/ErrorPuntero.h"

ListaIncidencia::ListaIncidencia() : primero(nullptr), actual(nullptr), tam(0) {}

ListaIncidencia::~ListaIncidencia() {
    while (primero) {
        NodoIncidencia* temp = primero;
        primero = primero->sig;
        delete temp->getIncidencia();
        delete temp;
        actual = primero;
    }
}

NodoIncidencia* ListaIncidencia::getPrimero() const { return primero; }
int ListaIncidencia::getTam() const { return tam; }

// Inserciones
void ListaIncidencia::insertarInicio(Equipo* e, int severidad, int dia) {
    NodoIncidencia* nuevo = new NodoIncidencia();
    nuevo->sig = primero;
    primero = nuevo;
    Incidencia* i = new Incidencia(e, severidad, dia);
    nuevo->setIncidencia(i);
    ++tam;
}

void ListaIncidencia::insertarInicio(Incidencia* i) {
    if (!i) throw ErrorPuntero("Incidencia a insertar en lista es nullptr");
    NodoIncidencia* nuevo = new NodoIncidencia();
    nuevo->sig = primero;
    primero = nuevo;
    nuevo->setIncidencia(i);
    ++tam;
}

void ListaIncidencia::insertarFinal(Incidencia* i) {
    if (!i) throw ErrorPuntero("Incidencia a insertar en lista es nullptr");
    NodoIncidencia* nuevo = new NodoIncidencia();
    nuevo->setIncidencia(i);

    if (!primero) {
        primero = nuevo;
    } else {
        actual = primero;
        while (actual->getSig()) {
            actual = actual->getSig();
        }
        actual->sig = nuevo;
    }
    ++tam;
}

bool ListaIncidencia::eliminarTodos() {
    while (primero) {
        NodoIncidencia* temp = primero;
        primero = primero->sig;
        delete temp->getIncidencia();
        delete temp;
        actual = primero;
    }
    return true;
}

NodoIncidencia* ListaIncidencia::buscarPorPos(int pos) {
    if (pos < 0 || pos >= tam) { return nullptr; }
    actual = primero;
    for (int i = 0; i < pos; i++) { actual = actual->sig; }
    return actual;
}

// Eliminaciones
bool ListaIncidencia::eliminarInicio() {
    if (!primero) return false;
    NodoIncidencia* temp = primero;
    primero = primero->sig;
    delete temp->getIncidencia();
    delete temp;
    --tam;
    return true;
}

bool ListaIncidencia::eliminarFinal() {
    if (!primero) return false;
    if (tam == 1) {
        return eliminarInicio();
    }

    NodoIncidencia* previo = buscarPorPos(tam - 2);
    NodoIncidencia* ultimo = previo->sig;
    previo->sig = nullptr;
    delete ultimo->getIncidencia();
    delete ultimo;
    --tam;
    return true;
}

bool ListaIncidencia::eliminarPos(int pos) {
    if (!primero) return false;
    if (pos < 0 || pos >= tam) return false;

    if (pos == 0) { return eliminarInicio(); }
    if (pos == (tam-1)) { return eliminarFinal(); }

    actual = primero;
    for (int i = 0; i < pos-1; i++) { actual = actual->sig; }
    NodoIncidencia* temp = actual->sig;
    actual->sig = temp->sig;
    delete temp->getIncidencia();
    delete temp;
    --tam;
    return true; // Encontrado
}

// toString
string ListaIncidencia::toString(){
    if (tam==0) return "No hay incidencias registradas";
    stringstream s;
    actual = primero;
    while (actual) {
        s << actual->getIncidencia()->toString() << endl;
        actual = actual->sig;
    }
    return s.str();
}
