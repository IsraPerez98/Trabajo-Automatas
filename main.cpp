#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<algorithm>
#include <limits>

#include "funciones_extra.h"
#include "ingreso_automatas.h"
#include "automata_obj.h"
#include "funciones_conversion.h"

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
    print_tabla_transicion(tabla_transicion,Q,Sigma);

    //print de los epsilon si es afnd
    if(!afd)
    {
        for(int i=0; i<Q.size(); i++)
        {
            cout << "transiciones epsilon de " << Q[i] << " : ";
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
        return;
    }

    cout << "verificando el estado incial + pseudo-iniciales" << endl;
    vector<Estado*> pseudo_iniciales;
    pseudo_iniciales.push_back(&estados_obj[estado_inicial]);
    obtener_estados_pseudo(estado_inicial, Q, estados_obj, pseudo_iniciales);

    cout << "haciendo una tabla de transicion" << endl;
    // Q x Sigma x estados_transicion 
    vector<vector<vector<Estado*>>> tabla_transicion_afnd(Q.size(), vector<vector<Estado*>>(Sigma.size()) );

    for(int i=0;i<Q.size();i++)
    {
        Estado *estado = &estados_obj[i];
        for(int j=0;j<Sigma.size();j++)
        {
            cout << "comprobando transiciones de " << estado->nombre << " con letra " << Sigma[j] << endl;
            vector<Estado*> transiciones_posibles;
            vector<Estado*> estados_revisados; // este es solo para que funciene transiciones_afnd() , no tiene otro uso
            estado->transiciones_afnd(transiciones_posibles, Sigma[j], estados_revisados);
            tabla_transicion_afnd[i][j] = transiciones_posibles;
        }
    }

    //print tabla_transicion 
    print_tabla_transicion_afnd(tabla_transicion_afnd, Q, Sigma);

    vector<string> nueva_Q;
    vector<Estado> nuevos_estados_obj;
    vector<vector<string>> tabla_transicion(nueva_Q.size(),vector<string>(Sigma.size()));
    //nuevo estado incial = combinacion de todos los pseudo iniciales
    int estado_inicial = combinar_estados(pseudo_iniciales, true, nueva_Q, nuevos_estados_obj);
    cout << "nuevo estado inicial creado " << nuevos_estados_obj[estado_inicial].nombre << endl;

    generar_nuevos_estados_afd(Sigma,estado_inicial, pseudo_iniciales, tabla_transicion_afnd, Q, nueva_Q, tabla_transicion, nuevos_estados_obj);

    Q = nueva_Q;
    vector<vector<string>> transiciones_epsilon(Q.size(), vector<string>(0)); // borramos todas las transiciones con epsilon
    print_tabla_transicion(tabla_transicion,Q,Sigma);

    //generamos las nuevas transiciones
    for (int i=0; i<nuevos_estados_obj.size();i++)
    {
        nuevos_estados_obj[i].generar_transiciones(Q,Sigma,tabla_transicion,nuevos_estados_obj);
    }
    estados_obj = nuevos_estados_obj;
    afd = true;

    cin.ignore();
    cin.get();
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
        cout << "3- Transformar AFND a AFD" << endl;
        cin >> opcion;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    return 0;
}