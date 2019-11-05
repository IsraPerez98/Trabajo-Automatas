#include<string>
#include<map>
#include<iostream>
#include<algorithm>

#include "funciones_extra.h"
using namespace std;

Estado::Estado(string nombre, bool afd, bool inicial, bool final)
{
    this->nombre = nombre;
    this->afd = afd;
    this->inicial = inicial;
    this->final = final;
}

void Estado::print_transiciones() // https://stackoverflow.com/a/14070977
{
    for (auto it = this->transiciones.cbegin(); it != this->transiciones.cend(); ++it)
    {
        cout << " entrada: " << it -> first << " transicion " << it->second->nombre << endl;
    }

    if(!this->afd)
    {
        cout << " con epsilon: ";
        if(transiciones_epsilon.size() == 0) cout << " no tiene transiciones";
        for(int i=0; i< this->transiciones_epsilon.size(); i++ )
        {
            cout << this->transiciones_epsilon[i]->nombre << "  ";
        }
        cout << endl;
    }
}

void Estado::print()
{
    cout << "Estado: " << this->nombre << " :  " << endl;

    if(this->afd) cout << "AFD" << endl;
    else cout << "AFND" << endl;

    if(this->inicial) cout << "[estado inicial]" << endl;
    if(this->final) cout << "[estado final]" << endl;

    print_transiciones();
    
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
        if(estado_transicion != "-")
        {
            int posicion_estado_sig = obtener_posicion_estado(estado_transicion, Q);
            this->transiciones[Sigma[i]] = &estados_obj[posicion_estado_sig];
            cout << "transicion: " << this->transiciones[Sigma[i]]->nombre << endl;
        }
        else cout << " no tiene transicion" << endl;
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
        if(estado_transicion != "-") // no consideramos los -
        {
            int posicion_estado_transicion = obtener_posicion_estado(estado_transicion, Q); // la posicion de la transicion en el vector
            this->transiciones_epsilon.push_back(&estados_obj[posicion_estado_transicion]); // enlazamos
        }
    }
}

void Estado::transiciones_afnd(vector<Estado*> &transiciones_posibles, string letra, vector<Estado*> &estados_revisados) // transiciones posibles como afnd, considerando los epsilon
// transiciones_posibles a las que podemos llegar, la letra a revisar, y los estados que ya han sido revisados para evitar ciclos infinitos
// esta funcion ta media fea y puede que no funcione perfectamente :C
{
    //cout << " comprobando transiciones normales... " << endl;
    if(this->transiciones.find(letra) != this->transiciones.end() ) // transiciones normales
    {
        Estado* estado_siguiente = this->transiciones[letra];
        
        cout << "  transicion de " << this->nombre << " con " << letra << " " << this->transiciones[letra]->nombre << endl;
        // continuamos de forma recursiva sin considerar la letra
        estado_siguiente->transiciones_afnd(transiciones_posibles,"", estados_revisados);
    }

    // los epsilon
    //cout << " comprobando transiciones epsilon" << endl;
    for(int i=0;i<this->transiciones_epsilon.size();i++)
    {
        Estado* estado_siguiente = this->transiciones_epsilon[i];
        cout << "  transicion " << this->nombre << " con epsilon " << estado_siguiente->nombre << endl;
        //los estados epsilon no se consideran como "caminos"
        //continuamos de forma recursiva considerando la misma letra
        // solo si no lo hemos considerado antes
        if(find(estados_revisados.begin(), estados_revisados.end(), estado_siguiente) == estados_revisados.end()) // https://stackoverflow.com/a/3450906
        {
            estado_siguiente->transiciones_afnd(transiciones_posibles, letra, estados_revisados);
        }
    }

    // si "aterrizamos" en este estado, debemos incluirlo
    if(letra == "" && find(transiciones_posibles.begin(), transiciones_posibles.end(), this) == transiciones_posibles.end()) // https://stackoverflow.com/a/3450906
    {

        transiciones_posibles.push_back(this);
    }
}

Estado* Estado::obtener_transicion_afd(string letra) // retorna la transicion hacia donde se debe mover con esa letra, NULL en otro caso
{
    if(this->transiciones.find(letra) != this->transiciones.end() )
    {
        return this->transiciones[letra];
    }
    return NULL;
}

bool Estado::palabra_pertenece(string palabra)
{
    if(this->afd)
    {
        if(palabra == "") return this->final; // si no tenemos nada mas que revisar, comprobamos si terminamos en estado final

        string letra_incial(1,palabra[0]); // palabra[0] es char asi que debemos convertir
        cout << letra_incial << "  ";
        string palabra_sig = "";
        for(int i=1;i<palabra.length();i++)
        {
            palabra_sig = palabra_sig + palabra[i];
        }

        Estado* est_siguiente = obtener_transicion_afd(letra_incial);
        if(est_siguiente != NULL)
        {
            cout << "siguiente estado " << est_siguiente->nombre;
            return est_siguiente->palabra_pertenece(palabra_sig);
        }
        return false;
    }
    else // transiciones afnd
    {
        //TODO
        return false;
    }
}

