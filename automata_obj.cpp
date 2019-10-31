#include<string>
#include<map>
#include<iostream>
#include "automata_obj.h"
#include "funciones_extra.h"
using namespace std;

Estado::Estado(string nombre, bool afd, bool inicial, bool final)
{
    this->nombre = nombre;
    this->afd = afd;
}

void Estado::print_transiciones() // https://stackoverflow.com/a/14070977
{
    for (auto it = this->transiciones.cbegin(); it != this->transiciones.cend(); ++it)
    {
        cout << "entrada: " << it -> first << " transicion " << it->second->nombre << endl;
    }

    if(!this->afd)
    {
        cout << "con entrada epsilon: ";
        for(int i=0; i< this->transiciones_epsilon.size(); i++ )
        {
            cout << this->transiciones_epsilon[i]->nombre << "  ";
        }
        cout << endl;
    }
}

void Estado::generar_transiciones(vector<string> Q, vector<string> Sigma, vector<vector<string>> tabla_transicion, vector<Estado> &estados_obj)
{
    if (this->transiciones_hechas) return;
    this->transiciones_hechas = true; // marcamos este estado como listo para que no se generen ciclos
    cout << this->nombre << " generando transiciones..." << endl;
    int posicion_estado = obtener_posicion_estado(this->nombre, Q);

    for(int i=0; i< Sigma.size(); i++ ) // la letra de entrada
    {
        cout << "Sigma: " << Sigma[i] << endl;
        string estado_transicion = tabla_transicion[posicion_estado][i]; // el string del estado que debemos enlazar
        int posicion_estado_sig = obtener_posicion_estado(estado_transicion, Q);
        this->transiciones[Sigma[i]] = &estados_obj[posicion_estado_sig];
        cout << "transicion: " << this->transiciones[Sigma[i]]->nombre << endl;
    }
}

void Estado::genererar_transiciones_epsilon(vector<string> Q, vector<vector<string>> transiciones_epsilon, vector<Estado> &estados_obj)
{
    //posicion de este estado
    int posicion_estado = obtener_posicion_estado(this->nombre, Q);
    //transiciones con epsilon de este estado
    vector<string> transiciones = transiciones_epsilon[posicion_estado];
    for(int i=0;i<transiciones.size();i++) // por cada transicion
    {
        string estado_transicion = transiciones[i]; // el nombre
        int posicion_estado_transicion = obtener_posicion_estado(estado_transicion, Q); // la posicion de la transicion en el vector
        this->transiciones_epsilon.push_back(&estados_obj[posicion_estado_transicion]); // enlazamos
    }
}

bool Estado::palabra_pertenece(string palabra)
{
    if(palabra == "") return this->final; // si no tenemos nada mas que revisar, comprobamos si terminamos en estado final

    string letra_incial(1,palabra[0]); // palabra[0] es char asi que debemos convertir
    cout << letra_incial << "  ";
    string palabra_sig = "";
    for(int i=1;i<palabra.length();i++)
    {
        palabra_sig = palabra_sig + palabra[i];
    }

    //revisamos si existe un siguiente movimiento
    if(this->transiciones.find(letra_incial) == this->transiciones.end() ) return false;

    //saltamos al siguiente estado
    cout << this->transiciones[letra_incial]->nombre << endl;
    return this->transiciones[letra_incial]->palabra_pertenece(palabra_sig);
}