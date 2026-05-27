//
// Created by axel on 9/4/2026.
//

#include "../../cabeceras/listas/ListaEquipo.h"
#include "../../cabeceras/excepciones/ErrorValor.h"
#include "../../cabeceras/excepciones/ErrorPuntero.h"
#include <vector>
#include <algorithm>
NodoEquipo* ListaEquipo::buscarPorPos(int pos) {
	if (pos < 0 || pos >= tam) { return nullptr; }
	actual = primero;
	for (int i = 0; i < pos; i++) { actual = actual->sig; }
	return actual;
}


int ListaEquipo::obtenerPos(string id) {
    if (!primero) return -1;
    actual = primero;
    int pos = -1;
    while (actual) {
        ++pos;
        if (actual->getEquipo() && actual->getEquipo()->getId() == id) {
            return pos;
        }
        actual = actual->sig;
    }
    return -1;
}

ListaEquipo::ListaEquipo() : primero(nullptr), actual(nullptr), tam(0) {}

ListaEquipo::~ListaEquipo() {
	while (primero) {
		NodoEquipo* temp = primero;
		primero = primero->sig;
		delete temp;
		actual = primero;
	}
}

NodoEquipo* ListaEquipo::getPrimero() const { return primero; }
int ListaEquipo::getTam() const { return tam; }

// Inserciones
void ListaEquipo::insertarInicio(Equipo* c) {
    NodoEquipo* nuevo = new NodoEquipo();
    nuevo->sig = primero;
    primero = nuevo;
    nuevo->setEquipo(c);
    ++tam;
}

void ListaEquipo::insertarFinal(Equipo* c) {
    NodoEquipo* nuevo = new NodoEquipo();
    if (!primero) {
        primero = nuevo;
    }
    else {
        actual = primero;
        while (actual->sig) actual = actual->sig;
        actual->sig = nuevo;

    }
    nuevo->setEquipo(c);
    ++tam;
}

bool ListaEquipo::insertarPos(int pos, Equipo* c) {
    if (pos < 0 || pos > tam) return false;

    if (pos == 0) {
        insertarInicio(c);
        return true;
    }
    if (pos == (tam)) {
        insertarFinal(c);
        return true;
    }
    NodoEquipo* previo = buscarPorPos(pos - 1);
    if (!previo) return false;

    NodoEquipo* nuevo = new NodoEquipo();
    nuevo->sig = previo->sig;
    previo->sig = nuevo;
    nuevo->setEquipo(c);
    ++tam;
    return true;
}

// Eliminaciones
bool ListaEquipo::eliminarInicio() {
    if (!primero) return false;
    NodoEquipo* temp = primero;
    primero = primero->sig;
    delete temp->getEquipo();
    delete temp;
    --tam;
    return true;
}

bool ListaEquipo::eliminarFinal() {
    if (!primero) return false;
    if (tam == 1) {
        return eliminarInicio();
    }

    NodoEquipo* previo = buscarPorPos(tam - 2);
    NodoEquipo* ultimo = previo->sig;
    previo->sig = nullptr;
    delete ultimo->getEquipo();
    delete ultimo;
    --tam;
    return true;
}

bool ListaEquipo::eliminarPos(int pos) {
    if (!primero) return false;
    if (pos < 0 || pos >= tam) return false;

    if (pos == 0) { return eliminarInicio(); }
    if (pos == (tam-1)) { return eliminarFinal(); }

    actual = primero;
    for (int i = 0; i < pos-1; i++) { actual = actual->sig; }
    NodoEquipo* temp = actual->sig;
    actual->sig = temp->sig;
    delete temp->getEquipo();
    delete temp;
    --tam;
    return true; // Encontrado
}
// Busquedas (version vieja sin busqueda binaria)
/*
NodoEquipo* ListaEquipo::buscarPorId(string id) {
    if (!primero) { return nullptr; }

    //Busca la prioridad double especifica
    actual = primero;
    while (actual) {
        if (actual->getEquipo() && actual->getEquipo()->getId() == id) {
            return actual;
        }
        actual = actual->sig;
    }
    return nullptr;
}*/


//Ordenamientos
NodoEquipo *ListaEquipo::dividir(NodoEquipo* cabeza) {
    NodoEquipo* rapido = cabeza;
    NodoEquipo* lento = cabeza;

    while (rapido != nullptr && rapido->sig != nullptr) {
        rapido = rapido->sig->sig;
        if (rapido != nullptr) {
            lento = lento->sig;
        }
    }

    NodoEquipo* temporal = lento->getSig();
    lento->sig = nullptr;
    return temporal;
}

NodoEquipo *ListaEquipo::merge(NodoEquipo *primero, NodoEquipo *segundo, int dia) {
    if (primero == nullptr) { return segundo;}
    if (segundo == nullptr) { return primero;}

    Equipo* a = primero->getEquipo();
    Equipo* b = segundo->getEquipo();
    if (!a || !b) { return nullptr; }
    double aPrio = a->calcPrioridad(dia);
    double bPrio = b->calcPrioridad(dia);
    if (aPrio > bPrio) {
        primero->sig = merge(primero->getSig(),segundo,dia);
        return primero;
    } else if (aPrio < bPrio) {
        segundo->sig = merge(primero,segundo->getSig(),dia);
        return segundo;
    }
    else {
        // se prioriza el mas viejo si son iguales
        if (a->getDiaMant() <= b->getDiaMant()) {
            primero->sig = merge(primero->getSig(),segundo,dia);
            return primero;
        }
        else {
            segundo->sig = merge(primero,segundo->getSig(),dia);
            return segundo;
        }
    }
}

NodoEquipo *ListaEquipo::mergeSort(NodoEquipo *cabeza, int dia) {
    if (!cabeza || !cabeza->sig) { return cabeza;}
    NodoEquipo* mitad = dividir(cabeza);
    cabeza = mergeSort(cabeza,dia);
    mitad = mergeSort(mitad,dia);
    return merge(cabeza,mitad,dia);
}

void ListaEquipo::ordenarPrioridad(int dia) {
    actual = primero;
    if (tam==0 || tam==1) return;
    primero = mergeSort(primero,dia);
}

// degradacion
void ListaEquipo::degradarTodos(int dia)
{
    actual = primero;
    // recorrer todos los nodos degradnado
    while (actual)
    {
        actual->getEquipo()->aplicarDegradacion(dia);
        actual = actual->getSig();
    }
}

// toString
string ListaEquipo::toString(int dia) {
    if (tam==0) return "No hay equipos registrados";
    stringstream s;
    actual = primero;
    while (actual) {
        s << actual->getEquipo()->toString(dia) << endl;
        actual = actual->sig;
    }
    return s.str();
}

double ListaEquipo::promedioPrioridad(int diaActual) {
    // recorrer todos y obtener promedio de prioridad
    if (tam == 0) { return 0.0; }
    double suma = 0.0;
    actual = primero;
    while (actual) {
        Equipo* e = actual->getEquipo();
        if (e) {
            suma += e->calcPrioridad(diaActual);
        }
        actual = actual->getSig();
    }
    return suma / tam;
}

int ListaEquipo::equiposPendientes(int dia) {
    if (tam == 0) { return 0;}
    int contador = 0;
    actual = primero;
    while (actual) {
        Equipo* e = actual->getEquipo();
        if (e && e->calcPrioridad(dia) > 0) {
            contador++;
        }
        actual = actual->getSig();
    }
    return contador;
}

// Extrae el número después del guión
int ListaEquipo::extraerNumero(string id) {
    size_t pos = id.find('-'); // encontrar posicion del guion
    string idParte = (pos != string::npos) ? id.substr(pos+1) : id; //Asignar Id sin guion si la tiene, sino mantiene id
    size_t inicioNum = idParte.find_first_of("0123456789"); //Busca el primer numero de la id
    if (inicioNum == string::npos) { return -1; } //Sino la encuentra, retorna -1

    //
    try
    {
        // retornar como entero sin la primera parte del id, si no es un numero o es muy grande, se captura la excepcion y se retorna -1
        int numero = stoi(idParte.substr(inicioNum));
        return numero;
    }
    catch (out_of_range& e)
    {
        return -1;
    }
}

Equipo* ListaEquipo::buscarPorId(string idBuscada) {
    vector<Equipo*> vec;
    actual = primero;
    while (actual != nullptr) {
        if (!actual->getEquipo()) throw ErrorPuntero("NodoEquipo sin Equipo asignado");
        vec.push_back(actual->getEquipo());
        actual = actual->getSig();
    }

    // ordenar vector
    sort(vec.begin(), vec.end(), [this](Equipo* a, Equipo* b) {
        return extraerNumero(a->getId()) < extraerNumero(b->getId());
    });
    // esto es una funcion anonima con lambda capturando "this" para llamar a extraerNumero

    int izq = 0, der = (int)vec.size() - 1;
    int numBuscado = extraerNumero(idBuscada);

    while (izq <= der) {
        int mid = izq + (der - izq) / 2;
        int midNum = extraerNumero(vec[mid]->getId());

        if (midNum == numBuscado)       return vec[mid];
        else if (midNum < numBuscado)   izq = mid + 1;
        else                            der = mid - 1;
    }
    return nullptr;
}
