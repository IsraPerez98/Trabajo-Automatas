#include<iostream>
#include<vector>

#include "funciones_extra.h"
#include "automata_obj.h"
#include "tabla_comparativa_obj.h"

using namespace std;

tabla_comparativa::tabla_comparativa(Estado* estado_1, Estado* estado_2)
{
    this->estado_1 = estado_1;
    this->estado_2 = estado_2;
    this->distinguibles = false;
    this->han_sido_comparados = false;
}

tabla_comparativa tc(Estado* e1, Estado* e2, vector<tabla_comparativa> &tablas_comparativas) //devuelve una nueva tabla comparativa o la que ya existe anteriormente
{
    for(int i=0;i<tablas_comparativas.size();i++) // comprobamos si ya existe
    {
        if( (tablas_comparativas[i].estado_1 == e1 && tablas_comparativas[i].estado_2 == e2) || (tablas_comparativas[i].estado_1 == e2 && tablas_comparativas[i].estado_2 == e1) )
        {
            return tablas_comparativas[i];
        }
    }
    //eoc creamos una nueva tabla y la retornamos
    return tabla_comparativa(e1,e2);
}


bool tabla_comparativa::comprobar_si_son_distinguibles( vector<vector<bool>> &tabla_compatibilidad, vector<string> Sigma, vector<tabla_comparativa> &tablas_comparativas)
{
    cout << "comparando si " << estado_1->nombre << " y " << estado_2->nombre << " son distinguibles" << endl;
    if(this->han_sido_comparados)
    {
        cout << " ya han sido comparados " << this->distinguibles << endl;
        return this->distinguibles;
    }
    else
    {
        if(estado_1 == estado_2) // si los estados son iguales no son distinguibles
        {
            cout << " son iguales " << false << endl;
            this->han_sido_comparados = true;
            this->distinguibles = false;
            return false;
        }
        else // no son iguales
        {
            bool dist = false;
            // comprobamos sus salidas por cada letra
            for(int i=0;i<Sigma.size();i++)
            {
                Estado* salida_1 = this->estado_1->obtener_transicion_afd(Sigma[i]);
                Estado* salida_2 = this->estado_2->obtener_transicion_afd(Sigma[i]);

                cout << " comprobando salida de " << estado_1->nombre << " con " << Sigma[i] << " :  " << salida_1->nombre << endl;
                cout << " comprobando salida de " << estado_2->nombre << " con " << Sigma[i] << " :  " << salida_2->nombre << endl;
                //esto tenia un error que creaba nuevas tablas y no usaba las anteriores
                //tabla_comparativa tc(salida_1, salida_2); 
                //tabla_comparativa tc2(salida_2, salida_1);
                tabla_comparativa tabla1 = tc(salida_1,salida_2,tablas_comparativas);
                tabla_comparativa tabla2 = tc(salida_2, salida_1, tablas_comparativas);
                tabla1.comprobar_si_son_distinguibles(tabla_compatibilidad,Sigma, tablas_comparativas);
                tabla2.distinguibles = tabla1.distinguibles;
                tabla2.han_sido_comparados = true;
                if(tabla1.distinguibles)
                {
                    dist = true;
                    break;
                }
            }
            this->distinguibles = dist;
            this->han_sido_comparados = true;
            cout << this->estado_1->nombre << " con " << this->estado_2->nombre << " dist: " << dist << endl; 
            return dist;
        }
        
    }
}