#pragma once

#include<map>
#include<vector>

using namespace std;


class Estado
{
    public:
        string nombre;
        void genererar_transiciones_epsilon(vector<string> Q, vector<vector<string>> transiciones_epsilon, vector<Estado> &estados_obj);
        void generar_transiciones(vector<string> Q, vector<string> Sigma, vector<vector<string>> tabla_transicion, vector<Estado> &estados_obj);
        void print_transiciones();
        Estado(string nombre, bool afd, bool inicial, bool final);
        bool palabra_pertenece(string palabra);
        bool incial = false;
        bool final = false;
        bool afd = false;
    private:
        map<string, Estado*> transiciones; // mapa entrada:estado
        vector<Estado*> transiciones_epsilon;
        bool transiciones_hechas = false;
};