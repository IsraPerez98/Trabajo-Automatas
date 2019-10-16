#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>

#include "funciones_extra.h"
#include "ingreso_automatas.h"

using namespace std;

int main()
{
    vector<string> Q; //estados
    vector<string> Sigma; //alfabeto

    pedir_estados(Q);
    pedir_alfabeto(Sigma);

    printf("Estados:\n");
    print_vector(Q);
    printf("Alfabeto:\n");
    print_vector(Sigma);

    string tabla_transicion[Q.size()][Sigma.size()]; // estados x alfabeto

    for(int i=0; i<Sigma.size(); i++) // no podemos usar una funcion con un arreglo bidimensional sin conocer sus dimensiones
    {
        string tabla_transicion_una_letra[Q.size()]; // vector que contiene solo una entrada para cada estado, por ejemplo 0 o 1
        pedir_tabla_transicion(tabla_transicion_una_letra, Q, Sigma, i);
        for(int j=0; j<Q.size(); j++)
        {
            tabla_transicion[j][i] = tabla_transicion_una_letra[j];
        }
    }

    //print tabla_transicion
    for(int i=0; i<Q.size(); i++)
    {
        for(int j=0; j<Sigma.size(); j++)
        {
            cout << "transicion estado " << Q[i] << " con entrada " << Sigma[j] << " = " << tabla_transicion[i][j] << endl;
        }
    }

    int estado_inicial; // indice del vector Q, con el estado inicial
    estado_inicial = pedir_estado_inicial(Q);

    cout << "Estado inicial: " << Q[estado_inicial] << endl;

    vector<int> estados_finales; // indices del vector Q para los estados finales
    pedir_estados_finales(Q, estados_finales);

    //print estados finales
    cout << "estados finales: " << endl;
    for(int i=0;i<estados_finales.size();i++)
    {
        cout << Q[estados_finales[i]] << "  ";
    }
    cout << endl;

    system("PAUSE");
    return 0;
}