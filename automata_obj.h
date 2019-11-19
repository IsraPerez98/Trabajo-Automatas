#pragma once

#include<map>
#include<vector>

using namespace std;


class Estado
{
    public:
        Estado(string nombre, bool afd, bool inicial, bool final);
        Estado();

        void generar_transiciones(vector<string> Q, vector<string> Sigma, vector<vector<string> > tabla_transicion, vector<Estado> &estados_obj);
        void genererar_transiciones_epsilon(vector<string> Q, vector<vector<string> > transiciones_epsilon, vector<Estado> &estados_obj);

        void print_transiciones();
        void print();

        void transiciones_afnd(vector<Estado*> &transiciones_posibles, string letra, vector<Estado*> &estados_revisados);
        Estado* obtener_transicion_afd(string letra);
        bool palabra_pertenece(string palabra);

        string nombre;
        bool inicial = false;
        bool final = false;
        bool afd = false;
        map<string, Estado*> transiciones; // mapa entrada:estado
        vector<Estado*> transiciones_epsilon;
        bool transiciones_hechas = false;
};
