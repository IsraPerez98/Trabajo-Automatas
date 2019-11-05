#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<limits>

#include "funciones_extra.h"

using namespace std;

bool preguntar_afd_o_afnd()
{
    cout << "El automata a ingresar es AFD? S/N" << endl;
    char respuesta;
    cin >> respuesta;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //https://stackoverflow.com/a/23745035
    if(respuesta == 's' || respuesta == 'S')
    {
        cout << "Automata AFD" << endl;
        return true;
    }
    cout << "Automata AFND" << endl;
    return false;
}

void pedir_estados(vector<string> &Q)
{
    cout << "Ingrese los estados separados por una coma." << endl;
    cout << "Q: ";

    string estados_str;
    getline(cin, estados_str);

    Q = separar_string_coma(estados_str);
}

void pedir_alfabeto(vector<string> &Sigma)
{
    cout << "Ingrese el alfabeto utilizado por el automata (separado por una coma)." << endl;
    cout << "Sigma: ";
    string alfabeto;
    getline(cin,alfabeto);
    Sigma = separar_string_coma(alfabeto);
}

void pedir_tabla_transicion(vector<vector<string>> &tabla, vector<string> Q, vector<string> Sigma , bool afd) // https://stackoverflow.com/a/34182883
{
    for(int i=0;i<Q.size();i++) 
    {
        //cout << "i: " << i << endl;
        for(int j=0;j<Sigma.size();j++)
        {
            while(1)
            {
                cout << "Ingrese la transicion de " << Q[i] << " con entrada " << Sigma[j] << endl;
                print_estados_posibles(Q, !afd); // consideramos el "-" como valido si es afnd
                string estado_transicion;
                getline(cin, estado_transicion);
                cin.clear(); //??
                bool transicion_correcta = verificar_estado_valido(estado_transicion, Q, !afd); // consideramos el "-" como valido si es afnd
                if(transicion_correcta)
                {
                    //cout << "fijando valor " << estado_transicion << endl;
                    tabla[i][j] = estado_transicion;
                    break;
                }
            }
        }
    }
}

void pedir_transiciones_epsilon(vector<vector<string>> &tabla, vector<string> Q)
{
    for(int i=0;i<Q.size();i++)
    {
        bool finalizado = false;
        while(!finalizado)
        {
            cout << "Ingrese las transiciones con epsilon de " << Q[i] << " separadas por una coma" << endl;
            print_estados_posibles(Q, true);
            cout << "Estados: ";
            string transicion_epsilon_str;
            getline(cin, transicion_epsilon_str);
            vector<string> estados_separados = separar_string_coma(transicion_epsilon_str);
            finalizado = true;
            for(int i=0;i<estados_separados.size();i++)
            {
                if(!verificar_estado_valido(estados_separados[i], Q, true))
                {
                    cout << "Estado " << estados_separados[i] << " no es valido.";
                    finalizado = false;
                    break;
                }
            }
            if(!finalizado) continue;
            tabla[i] = estados_separados;
        }
    }
}

int pedir_estado_inicial(vector<string> Q)
{
    while(1)
    {
        cout << "Ingrese el estado inicial." << endl;
        print_estados_posibles(Q, false);
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
        print_estados_posibles(Q, false);
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