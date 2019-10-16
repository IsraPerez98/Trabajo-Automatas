#include<string>
#include "automata_obj.h"
using namespace std;

Estado::Estado(string nombre)
{
    this->nombre = nombre;
}

void Estado::agregar_transicion(string nombre, Estado *estado)
{
    this->transiciones[nombre] = estado;
}