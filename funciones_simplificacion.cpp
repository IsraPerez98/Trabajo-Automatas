#include<iostream>
#include<vector>
#include<algorithm>

#include "funciones_extra.h"
#include "automata_obj.h"
#include "tabla_comparativa_obj.h"
using namespace std;


void crear_matriz_compatibilidad(vector<vector<bool>> &compatibilidad, vector<tabla_comparativa> &tablas_comparativas, vector<Estado> &estados_obj)
{
    for(int i=1;i<estados_obj.size();i++)
    {
        for(int j=0;j<i;j++) // con esto solo marcamos "la mitad" de la matriz
        {
            cout << "comprobando compatibilidad " << estados_obj[i].nombre << " con " << estados_obj[j].nombre << endl;
            bool compatible = (estados_obj[i].final == estados_obj[j].final);
            compatibilidad[i][j] == compatible;
            // creamos la tabla comparativa para el par de estados
            tabla_comparativa tabla(&estados_obj[i], &estados_obj[j]);
            tabla_comparativa tabla2(&estados_obj[j], &estados_obj[i]);
            if(!compatible)
            {
                tabla.distinguibles = true;
                tabla2.distinguibles = true;
                tabla.han_sido_comparados = true;
                tabla2.han_sido_comparados = true;
            }
            tablas_comparativas.push_back(tabla);
            tablas_comparativas.push_back(tabla2);
            cout << " " << compatible << endl;
        }
    }
}

void generar_vector_nd(vector<tabla_comparativa> tablas_comparativas, vector<vector<Estado*>> &estados_nd)
{
    for(int i=0;i<tablas_comparativas.size();i++)
    {
        if(!tablas_comparativas[i].distinguibles)
        {
            Estado *e1 = tablas_comparativas[i].estado_1;
            Estado *e2 = tablas_comparativas[i].estado_2;
            // si no han sido considerados ya
            bool ya_considerados = false;
            for(int j=0;j<estados_nd.size();j++)
            {
                //si ya existen en el vector estados_nd
                if((estados_nd[j][0] == e1 && estados_nd[j][1] == e2) || (estados_nd[j][0] == e2 && estados_nd[j][1] == e1 ) )
                {
                    ya_considerados = true;
                    break; // terminamos de buscar
                }
            }
            if(!ya_considerados)
            {
                cout << "considerando par ND " << e1->nombre << " con " << e2->nombre << endl;
                estados_nd.push_back({e1,e2});
            }
        }
    }
}

void eliminar_estados_nd(vector<vector<Estado*>> &estados_nd, vector<Estado> &estados_obj, vector<string> &Q, vector<string> Sigma,  vector<vector<string>> &tabla_transicion, int *estado_inicial, vector<int> &estados_finales)
{
    string estado_inicial_str = Q[*estado_inicial]; // almacenamos el nombre del inicial por si hay que moverlo de posicion
    //almacenamos los nombres de los finales
    vector<string> estados_finales_str(estados_finales.size());
    for(int i=0;i<estados_finales.size();i++)
    {
        estados_finales_str[i] = Q[estados_finales[i]];
    }
    for(int i=0;i<estados_nd.size();i++) // cada par de estados
    {
        Estado *eliminado = estados_nd[i][0];
        Estado *eq = estados_nd[i][1];
        cout << "eliminando " << eliminado->nombre << " que es ND con " << eq->nombre << endl;

        //por cada estado que apunte al que se va a eliminar
        for(int j=0;j<Q.size();j++)
        {
            for(int k=0;k<Sigma.size();k++) // como es AFD, estamos seguro que la transicion existe, no hay que comprobar nada
            {

                if(tabla_transicion[j][k] == eliminado->nombre)
                {
                    cout << "redireccionando " << estados_obj[j].nombre << " con entrada " << Sigma[k] << " hacia " << eq->nombre << endl;
                    tabla_transicion[j][k] = eq->nombre;
                }
            }
        }
        //eliminamos el estado
        cout << "eliminando estado " << eliminado->nombre << " del AFD" << endl;
        int pos_eliminar = obtener_posicion_estado(eliminado->nombre, Q);
        
        Q.erase(Q.begin() + pos_eliminar); //https://stackoverflow.com/a/875109
        tabla_transicion.erase(tabla_transicion.begin() + pos_eliminar);
        //estados_obj.erase(estados_obj.begin() + pos_eliminar); 
    }


    // generamos un nuevo vector de estados    
    cout << "generando nuevo vector de estados " << endl;
    estados_obj.clear();
    for(int i=0;i<Q.size();i++)
    {
        bool final = (find(estados_finales_str.begin(), estados_finales_str.end(), Q[i]) != estados_finales_str.end());
        Estado estado_obj(Q[i], true, false, final); // nombre, afd, inicial, final
        estados_obj.push_back(estado_obj);
    }
    for(int i=0;i<Q.size();i++) // generamos las nuevas transiciones
    {
        estados_obj[i].generar_transiciones(Q,Sigma,tabla_transicion,estados_obj);
    }
    //la posicion del nuevo estado inicial
    *estado_inicial = obtener_posicion_estado(estado_inicial_str, Q);
    estados_obj[*estado_inicial].inicial = true;
    
}