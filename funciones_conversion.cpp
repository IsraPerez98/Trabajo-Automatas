#include<iostream>
#include<vector>
#include<algorithm>

#include "funciones_extra.h"
#include "automata_obj.h"

using namespace std;

void print_tabla_transicion_afnd(vector<vector<vector<Estado*>>> tabla_transicion_afnd, vector<string> Q, vector<string> Sigma)
{
    cout << "tabla transicion afnd" << endl;
    for(int i=0; i< Q.size(); i++)
    {
        for(int j=0;j<Sigma.size();j++)
        {
            cout << Q[i] << " con entrada " << Sigma[j] << " transiciones:  ";
            vector<Estado*> transiciones = tabla_transicion_afnd[i][j];
            for(int k=0;k<transiciones.size();k++)
            {
                cout << transiciones[k]->nombre << "  ";
            }
            cout << endl;
        }
    }
}

//obtiene los estados pseudo iniciales del automata
void obtener_estados_pseudo(int posicion,vector<string> Q,vector<Estado> estados_obj,vector<Estado*> &pseudo_iniciales) // la posicion del estado en el vector estados_obj, estados_obj, y el vector donde se almacenan los estados pseudo
{
    for(int i=0;i<estados_obj[posicion].transiciones_epsilon.size();i++)
    {
        //las transiciones con epsilon del estado incial
        Estado *est_transicion = estados_obj[posicion].transiciones_epsilon[i];
        //solo si no hemos agregado antes este estado lo consideramos
        if(find(pseudo_iniciales.begin(), pseudo_iniciales.end(), est_transicion) == pseudo_iniciales.end()) // https://stackoverflow.com/a/3450906
        {
            pseudo_iniciales.push_back(est_transicion); //lo agregamos al vector
            int pos_siguiente = obtener_posicion_estado(est_transicion->nombre,Q);
            obtener_estados_pseudo(pos_siguiente,Q,estados_obj, pseudo_iniciales); // buscamos mas vectores pseudo, de forma recursiva
        }
    }
}

int combinar_estados(vector<Estado*> estados_anteriores, bool inicial , vector<string> &nueva_Q, vector<Estado> &nuevos_estados_obj)
// pasamos los 2 o mas estados anteriores, un bool si es inicial o no , un vector donde se almacena una nueva Q (estados como string), y los nuevos estados resultantes se almacenan en nuevos_estados_obj
{
    //esto es para no considerar el mismo estado 2 veces
    vector<string> estados_ya_considerados;
    // el nuevo nombre del estado es la combinacion de los estados anteriores
    // tambien hay que ver si el nuevo estado es final
    bool final = false;
    for(int i=0;i<estados_anteriores.size();i++)
    {
        string nombre_estado = estados_anteriores[i]->nombre;
        if(find(estados_ya_considerados.begin(), estados_ya_considerados.end(), nombre_estado) == estados_ya_considerados.end())
        {
            //nuevo_estado_str = nuevo_estado_str + nombre_estado;
            if (estados_anteriores[i]->final) final = true;
            estados_ya_considerados.push_back(nombre_estado);
        }
    }
    //ordenamos los estados alfabeticamente
    sort(estados_ya_considerados.begin(), estados_ya_considerados.end(), comparacion_string); // funcion en funciones_extra

    string nuevo_estado_str = "";
    for(int i=0;i<estados_ya_considerados.size();i++)
    {
        nuevo_estado_str = nuevo_estado_str + estados_ya_considerados[i];
    }

    if(nuevo_estado_str == "") nuevo_estado_str = "Sumidero";


    for(int i=0; i<nueva_Q.size(); i++)
    {
        if (nueva_Q[i] == nuevo_estado_str)
        {
            cout << "estado " << nuevo_estado_str << " ya ha sido creado" << endl;
            return i;
            //return &nuevos_estados_obj[i];
        }
    }

    cout << "creando nuevo estado " << nuevo_estado_str << endl;
    nueva_Q.push_back(nuevo_estado_str);

    Estado nuevo_estado_obj(nuevo_estado_str,true, inicial, final);
    nuevos_estados_obj.push_back(nuevo_estado_obj);

    return nuevos_estados_obj.size() - 1;
    //return &(nuevos_estados_obj.back()); // retornamos el puntero del ultimo objeto insertado
}


void generar_nuevos_estados_afd(vector<string> Sigma, int pos_estado_anterior, vector<Estado*> estados_a_combinar, vector<vector<vector<Estado*>>> tabla_transicion_afnd, vector<string> Q, vector<string> &nueva_Q, vector<vector<string>> &tabla_transicion, vector<Estado> &nuevos_estados_obj )
{
    Estado *estado_anterior = &(nuevos_estados_obj[pos_estado_anterior]);
    cout << "generando nuevos estados para " << estado_anterior->nombre << endl;
    if(estado_anterior->nombre == "Sumidero")
    {
        cout << "Sumidero se enlaza a si mismo" << endl;
        for(int i=0;i<Sigma.size(); i++)
        {
            //estado_anterior->transiciones[Sigma[i]] = estado_anterior;
            tabla_transicion[pos_estado_anterior][i] = estado_anterior->nombre;
        }
    }

    for(int i=0;i<Sigma.size();i++)
    {
        cout << " con entrada " << Sigma[i] << endl;

        //comprobamos si esta transicion ya ha sido considerada
        if((tabla_transicion.size() > pos_estado_anterior) && (tabla_transicion[pos_estado_anterior][i] != "" ) )
        {
            cout << " el estado ya ha sido enlazado a " << tabla_transicion[pos_estado_anterior][i] << endl;
            continue;
        }

        //jutamos todas las salidas de los estados combinados
        vector<Estado*> estados_salidas;
        for(int j=0;j<estados_a_combinar.size();j++)
        {
            vector<Estado*> estados_salidas_local;
            int posicion_estado = obtener_posicion_estado(*estados_a_combinar[j],Q);

            estados_salidas_local = tabla_transicion_afnd[posicion_estado][i];

            estados_salidas.insert(estados_salidas.begin(), estados_salidas_local.begin(), estados_salidas_local.end());

        }

        // combinamos todos los estados de salida en uno solo
        int estado_salida_posicion = combinar_estados(estados_salidas, false, nueva_Q, nuevos_estados_obj);
        Estado* est_transicion = &nuevos_estados_obj[estado_salida_posicion];
        
        cout << "redimensionando nueva_Q" << endl;
        tabla_transicion.resize(nueva_Q.size(),vector<string>(Sigma.size()));
        cout << "enlazando a " << est_transicion->nombre;
        tabla_transicion[pos_estado_anterior][i] = est_transicion->nombre;

        cout << " enlazado a " << est_transicion->nombre << endl;
        cout << "estados creados: " << endl;
        print_vector(nueva_Q);

        generar_nuevos_estados_afd(Sigma, estado_salida_posicion, estados_salidas, tabla_transicion_afnd, Q, nueva_Q, tabla_transicion,nuevos_estados_obj);
    }
}
