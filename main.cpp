#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<algorithm>

#include "funciones_extra.h"
#include "ingreso_automatas.h"
#include "automata_obj.h"

using namespace std;

bool ingresado = false;
bool afd; // grafo es afd o afnd

vector<string> Q; //estados
vector<string> Sigma; //alfabeto

vector<vector<string>> tabla_transicion(Q.size(),vector<string>(Sigma.size())); //vector de vectores estados x alfabeto como matriz

vector<vector<string>> transiciones_epsilon(Q.size(), vector<string>(0)); //vector de vectores con las transiciones del epsilon
//este puede tomar varios valores simultaneos
//mismo tramaño que Q

int estado_inicial; // indice del vector Q, con el estado inicial
vector<int> estados_finales; // indices del vector Q para los estados finales

vector<Estado> estados_obj; // contiene los estados como objeto, mismo tamaño que Q


void ingresar_automata()
{
    afd = preguntar_afd_o_afnd();

    pedir_estados(Q);
    pedir_alfabeto(Sigma);

    cout << "Estados:" << endl;
    print_vector(Q);
    cout << "Alfabeto:" << endl;
    print_vector(Sigma);

    //necesitamos rehacer estos vectores con nuevos tamaños
    vector<vector<string>> tabla_transicion(Q.size(),vector<string>(Sigma.size())); //vector de vectores estados x alfabeto como matriz
    vector<vector<string>> transiciones_epsilon(Q.size(), vector<string>(0)); //vector de vectores con las transiciones del epsilon
    //este puede tomar varios valores simultaneos
    //mismo tramaño que Q

    pedir_tabla_transicion(tabla_transicion, Q, Sigma, afd);
    
    if(!afd)
    {

        pedir_transiciones_epsilon(transiciones_epsilon,Q);
    }

    //print de la tabla de transicion
    for(int i=0; i<Q.size(); i++)
    {
        for(int j=0; j<Sigma.size(); j++)
        {
            cout << "transicion estado " << Q[i] << " con entrada " << Sigma[j] << " = " << tabla_transicion[i][j] << endl;
        }
    }

    //print de los epsilon si es afnd
    if(!afd)
    {
        for(int i=0; i<Q.size(); i++)
        {
            cout << "transiciones epsilon de " << Q[i] << " :" << endl;
            for(int j=0; j < transiciones_epsilon[i].size();j++)
            {
                cout << transiciones_epsilon[i][j] << "   ";
            }
            cout << endl;
        }
    }
    
    estado_inicial = pedir_estado_inicial(Q);

    cout << "Estado inicial: " << Q[estado_inicial] << endl;

    pedir_estados_finales(Q, estados_finales);

    //print estados finales
    cout << "estados finales: " << endl;
    for(int i=0;i<estados_finales.size();i++)
    {
        cout << Q[estados_finales[i]] << "  ";
    }
    cout << endl;

    //generamos estados como objeto para cada Q
    for(int i=0;i<Q.size();i++)
    {
        Estado estado_obj(Q[i], afd, false, false);
        estados_obj.push_back(estado_obj);
    }
    
    // fijamos estado inicial
    estados_obj[estado_inicial].incial = true;
    //fijamos estados finales
    for(int i=0;i<estados_finales.size();i++)
    {
        estados_obj[estados_finales[i]].final = true;
    }

    //generamos las transiciones de cada objeto
    for(int i=0;i<estados_obj.size();i++)
    {
        estados_obj[i].generar_transiciones(Q,Sigma,tabla_transicion,estados_obj);
    }

    //si es afnd tambien generamos las transiciones epsilon
    if(!afd)
    {
        for(int i=0;i<estados_obj.size();i++)
        {
            estados_obj[i].genererar_transiciones_epsilon(Q,transiciones_epsilon,estados_obj);
        }    
    }

    //print de todas las transiciones de los objetos
    for(int i=0;i<estados_obj.size();i++)
    {
        estados_obj[i].print_transiciones();
    }
    ingresado = true;
}

void comprobar_palabra()
{
    cout << "Ingrese una palabra" << endl;
    string palabra;
    cin.ignore();
    getline(cin,palabra);
    bool pertenece = estados_obj[estado_inicial].palabra_pertenece(palabra);
    if(pertenece) cout << "la palabra " << palabra << " pertenece al automata" << endl;
    else cout << "la palabra no pertenece al automata" << endl;
    cin.ignore();
    cin.get();
}

bool verificar_si_ha_ingresado(bool pause) // verificamos si se ha ingresado un afd o un afnd
{
    if(!ingresado)
    {
        cout << "AUN NO SE INGRESA UN AFD o AFND" << endl;
        if(pause)
        {
            cin.ignore();
            cin.get();
        }
        return false;
    }
    return true;
}

void convertir_a_afd()
{
    if(afd)
    {
        cout << "El automata ya es AFD" << endl;
    }


}

int main()
{
    int opcion = -1;
    while(opcion != 5)
    {
        cout << "AFD y AFND" << endl;
        verificar_si_ha_ingresado(false);
        cout << "1- Ingresar un AFD o AFND" << endl;
        cout << "2- Ingresar una palabra y comprobar si pertenece" << endl;

        cin >> opcion;
        switch(opcion)
        {
            case 1:
                ingresar_automata();
                break;
            case 2:
                if(verificar_si_ha_ingresado(true))  comprobar_palabra();
                break;
            case 3:
                if(verificar_si_ha_ingresado(true)) convertir_a_afd();
                break;
        }
    }
    //system("PAUSE");
    cin.ignore();
    cin.get();
    return 0;
}