#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<algorithm>
#include<limits>

#include "funciones_extra.h"
#include "ingreso_automatas.h"
#include "automata_obj.h"
#include "funciones_conversion.h"
#include "funciones_simplificacion.h"
#include "tabla_comparativa_obj.h"

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

void pause() // analogo al system pause
{
    cout << "Presione Enter para continuar" << endl;
    cin.clear();
    cin.get();
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void ingresar_automata()
{
    //como vamos a ingresar uno nuevo, reiniciamos todos los valores
    Q.clear();
    Sigma.clear();
    estados_obj.clear();
    tabla_transicion.clear();
    transiciones_epsilon.clear();
    afd = preguntar_afd_o_afnd();

    pedir_estados(Q);
    pedir_alfabeto(Sigma);

    cout << "Estados:" << endl;
    print_vector(Q);
    cout << "Alfabeto:" << endl;
    print_vector(Sigma);

    //necesitamos redimensionar estos vectores
    tabla_transicion.resize(Q.size(),vector<string>(Sigma.size()));
    transiciones_epsilon.resize(Q.size(), vector<string>(0));
    //vector<vector<string>> tabla_transicion(Q.size(),vector<string>(Sigma.size())); //vector de vectores estados x alfabeto como matriz
    //vector<vector<string>> transiciones_epsilon(Q.size(), vector<string>(0)); //vector de vectores con las transiciones del epsilon

    pedir_tabla_transicion(tabla_transicion, Q, Sigma, afd);
    
    if(!afd)
    {

        pedir_transiciones_epsilon(transiciones_epsilon,Q);
    }

    //print de la tabla de transicion
    //print_tabla_transicion(tabla_transicion,Q,Sigma);

    //print de los epsilon si es afnd
    /*
    if(!afd)
    {
        print_tabla_epsilon(transiciones_epsilon,Q,Sigma);
    }
    */
    
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
    estados_obj[estado_inicial].inicial = true;
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

    //print de todos los estados
    for(int i=0;i<estados_obj.size();i++)
    {
        estados_obj[i].print();
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
    else cout << "la palabra NO pertenece al automata" << endl;
}

bool verificar_si_ha_ingresado() // verificamos si se ha ingresado un afd o un afnd
{
    if(!ingresado)
    {
        cout << "AUN NO SE INGRESA UN AFD o AFND" << endl;
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

    cout << "verificando el estado inicial + pseudo-iniciales" << endl;
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
    tabla_transicion.clear();
    tabla_transicion.resize(nueva_Q.size(),vector<string>(Sigma.size()));
    //vector<vector<string>> tabla_transicion(nueva_Q.size(),vector<string>(Sigma.size()));
    //nuevo estado inicial = combinacion de todos los pseudo iniciales
    int estado_inicial = combinar_estados(pseudo_iniciales, true, nueva_Q, nuevos_estados_obj);
    cout << "nuevo estado inicial creado " << nuevos_estados_obj[estado_inicial].nombre << endl;

    generar_nuevos_estados_afd(Sigma,estado_inicial, pseudo_iniciales, tabla_transicion_afnd, Q, nueva_Q, tabla_transicion, nuevos_estados_obj);

    Q = nueva_Q;
    transiciones_epsilon.clear();
    //vector<vector<string>> transiciones_epsilon(Q.size(), vector<string>(0)); // borramos todas las transiciones con epsilon
    print_tabla_transicion(tabla_transicion,Q,Sigma);

    //generamos las nuevas transiciones
    for (int i=0; i<nuevos_estados_obj.size();i++)
    {
        nuevos_estados_obj[i].generar_transiciones(Q,Sigma,tabla_transicion,nuevos_estados_obj);
    }
    estados_obj = nuevos_estados_obj;
    afd = true;

    //marcamos los nuevos estados finales
    estados_finales.clear();
    for(int i=0;i<estados_obj.size();i++)
    {
        if(estados_obj[i].final) estados_finales.push_back(i);
    }

    //imprimimos los nuevos estados
    for(int i=0;i<estados_obj.size();i++)
    {
        estados_obj[i].print();
    }
}

void simplificar_afd()
{
    if(!afd)
    {
        cout << "Para simplificar el automata debe ser AFD" << endl;
        return;
    }

    //generamos tabla de los estados
    vector<vector<bool>> compatibilidad(Q.size(), vector<bool>(Q.size()));
    vector<tabla_comparativa> tablas_comparativas; // tabla
    //revisamos compatibilidad
    crear_matriz_compatibilidad(compatibilidad,tablas_comparativas,estados_obj);

    print_matriz_compatibilidad(compatibilidad);
    
    cout << "comparando estados compatibles" << endl;
    // por cada tabla comparativa, se hace la comparacion
    for(int i=0;i<tablas_comparativas.size();i++)
    {
        //cout << "compat " << tablas_comparativas[i].estado_1->nombre << "  " << tablas_comparativas[i].estado_2->nombre << endl;
        if(!tablas_comparativas[i].han_sido_comparados) // solo si no han sido comparadas
        tablas_comparativas[i].comprobar_si_son_distinguibles(compatibilidad,Sigma, tablas_comparativas);
    }

    //este vector tendra los pares de estados no distinguibles SIN REPETIR
    vector<vector<Estado*>> estados_nd;
    // comprobamos los que no sean distinguibles
    generar_vector_nd(tablas_comparativas, estados_nd);

    //eliminamos el primero de cada par
    eliminar_estados_nd(estados_nd, estados_obj, Q, Sigma, tabla_transicion, &estado_inicial, estados_finales);

    //imprimimos el resultado
    for(int i=0;i<estados_obj.size();i++)
    {
        estados_obj[i].print();
    }

}

int main()
{
    int opcion = -1;
    while(opcion != 5)
    {
        cout << "AFD y AFND" << endl;
        verificar_si_ha_ingresado();
        cout << "1- Ingresar un AFD o AFND" << endl;
        cout << "2- Ingresar una palabra y comprobar si pertenece" << endl;
        cout << "3- Transformar AFND a AFD" << endl;
        cout << "4- Simplificar AFD" << endl;
        cin >> opcion;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(opcion)
        {
            case 1:
                ingresar_automata();
                pause();
                break;
            case 2:
                if(verificar_si_ha_ingresado())  comprobar_palabra();
                pause();
                break;
            case 3:
                if(verificar_si_ha_ingresado()) convertir_a_afd();
                pause();
                break;
            case 4:
                if(verificar_si_ha_ingresado()) simplificar_afd();
                pause();
                break;
        }
    }
    //system("PAUSE");
    return 0;
}