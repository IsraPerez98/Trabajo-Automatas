#pragma once

#include<map>

using namespace std;


class Estado
{
    public:
        string nombre;
        void agregar_transicion(string nombre, Estado *estado);
        Estado(string nombre);
    private:
        map<string, Estado*> transiciones;
};