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


bool tabla_comparativa::comprobar_si_son_distinguibles( vector<vector<bool>> &tabla_compatibilidad, vector<string> Sigma)
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

                tabla_comparativa tc(salida_1, salida_2);
                tabla_comparativa tc2(salida_2, salida_1);
                tc.comprobar_si_son_distinguibles(tabla_compatibilidad,Sigma);
                tc2.distinguibles = tc.distinguibles;
                tc2.han_sido_comparados = true;
                if(tc.distinguibles)
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