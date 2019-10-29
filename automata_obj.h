#pragma once

#include<map>

using namespace std;


class Estado
{
    public:
        string nombre;
        bool inicial;
        void agregar_transicion(string nombre, Estado estado);
        Estado(string nombre,bool inicial);
        map<string, string> transiciones;
};
