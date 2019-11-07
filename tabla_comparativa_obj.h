#pragma once

#include<vector>

#include "automata_obj.h"

using namespace std;

class tabla_comparativa
{
    public:
        tabla_comparativa(Estado* estado_1,Estado* estado_2);

        // los 2 estados
        Estado* estado_1;
        Estado* estado_2;
        // si son distinguibles
        bool distinguibles;
        // si ya han sido comparados
        bool han_sido_comparados;

        bool comprobar_si_son_distinguibles(vector<vector<bool>> &tabla_compatibilidad, vector<string> Sigma,vector<tabla_comparativa> &tablas_comparativas);
};
