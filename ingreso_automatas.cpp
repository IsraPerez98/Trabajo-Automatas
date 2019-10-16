#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include "funciones_extra.h"

using namespace std;

void pedir_estados(vector<string> &Q)
{
    printf("Ingrese los estados separados por una coma.\n");
    cout << "Q: ";

    string estados_str;
    getline(cin, estados_str);

    Q = separar_string_coma(estados_str);
}

void pedir_alfabeto(vector<string> &Sigma)
{
    printf("Ingrese el alfabeto utilizado por el automata (separado por una coma).\n");
    string alfabeto;
    getline(cin,alfabeto);
    Sigma = separar_string_coma(alfabeto);
}

void pedir_tabla_transicion(string tabla_transicion[], vector<string> Q, vector<string> Sigma, int entrada)
{
    for(int i=0;i<Q.size();i++)
    {
        bool transicion_correcta = false;
        while(!transicion_correcta)
        {
            cout << "Ingrese el valor de transicion de " << Q[i] << " con entrada " << Sigma[entrada] << endl;
            print_estados_posibles(Q);
            cout << "Estado: ";
            string estado_transicion;
            getline(cin, estado_transicion);
            transicion_correcta = verificar_estado_valido(estado_transicion, Q);
            if(transicion_correcta) tabla_transicion[i] = estado_transicion;
        }
    }
}

int pedir_estado_inicial(vector<string> Q)
{
    while(1)
    {
        cout << "Ingrese el estado incial." << endl;
        print_estados_posibles(Q);
        cout << endl << "Estado: ";
        string estado;
        getline(cin, estado);
        int posicion = obtener_posicion_estado(estado, Q);
        if(posicion != -1) return posicion;
    }
}

void pedir_estados_finales(vector<string> Q, vector<int> &estados_finales)
{
    bool finalizado = false;
    while(!finalizado)
    {
        cout << "Ingrese los estados finales, separados por una coma." << endl;
        print_estados_posibles(Q);
        cout << "Estados: ";
        string estados_finales_str;
        getline(cin,estados_finales_str);
        vector<string> estados_separados = separar_string_coma(estados_finales_str);
        finalizado = true;
        for(int i=0;i<estados_separados.size();i++)
        {
            int posicion = obtener_posicion_estado(estados_separados[i], Q);
            if(posicion == -1)
            {
                finalizado = false;
                break;
            }
            else
            {
                estados_finales.push_back(posicion);
            }
        }
    }
}