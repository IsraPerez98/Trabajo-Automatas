#include<string>
#include "automata_obj.h"

using namespace std;

Estado::Estado(string nombre,bool inicial)
{
    this->nombre = nombre;
    this->inicial = false;
}
