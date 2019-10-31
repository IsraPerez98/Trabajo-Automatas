#pragma once

#include<map>
#include<vector>

using namespace std;


class Estado
{
    public:
        Estado(string nombre, bool afd, bool inicial, bool final);

        void generar_transiciones(vector<string> Q, vector<string> Sigma, vector<vector<string>> tabla_transicion, vector<Estado> &estados_obj);
        void genererar_transiciones_epsilon(vector<string> Q, vector<vector<string>> transiciones_epsilon, vector<Estado> &estados_obj);
        void print_transiciones();

        void transiciones_afnd(vector<Estado*> &transiciones_posibles, string letra, vector<Estado*> &estados_revisados);
        bool palabra_pertenece(string palabra);
        string nombre;
        bool incial = false;
        bool final = false;
        bool afd = false;
        map<string, Estado*> transiciones; // mapa entrada:estado
        vector<Estado*> transiciones_epsilon;
    private:
        bool transiciones_hechas = false;
};