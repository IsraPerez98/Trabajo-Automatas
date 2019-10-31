#include<vector>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<algorithm>


using namespace std;

vector<string> separar_string_coma(string string_inicial)
{
    vector<string> vector_final;
    string str; //contiene un solo valor
    for(int i=0; i<string_inicial.length(); i++) // separamos los estados y los guardamos en el vector_final
    {
        if(string_inicial[i] == ',') // si hay una coma debemos cortar la linea y guardar el valor de str
        {
            if(str != "")
            {
                vector_final.push_back(str);
                str = "";
            }
        }
        else if(string_inicial[i] != ' ') // ignoramos los espacios
        {
            str = str + string_inicial[i];
        }
    }
    if(str != "") vector_final.push_back(str); // el resto
    return vector_final;
}

void print_vector(vector<string> a)
{
    for(int i=0; i<a.size();i++)
    {
        cout << a[i] << endl;
    }
}

bool verificar_estado_valido(string estado, vector<string> Q, bool considerar_guion)
{
    if(considerar_guion && estado == "-") return true; 
    for(int i=0;i<Q.size();i++)
    {
        if(Q[i] == estado) return true;
    }
    cout << "Estado "<< estado << " no pertenece al automata " << endl;
    return false;
}

int obtener_posicion_estado(string estado, vector<string> Q)
{
    for(int i=0; i<Q.size(); i++ )
    {
        if(Q[i] == estado) return i;
    }
    cout << "Estado " << estado  << " no pertenece al automata." << endl;
    return -1;
}

void print_estados_posibles(vector<string> Q, bool incluir_guion)
{
    cout << "Valores posibles: ";
    for(int j=0;j<Q.size();j++)
    {
        cout << Q[j] << "  ";
    }
    if(incluir_guion) cout << "-  ";
    cout << endl;
}


bool estado_es_final(string estado, vector<string> Q, vector<int> estados_finales)
{
    for(int i=0; i< estados_finales.size();i++)
    {
        if(Q[estados_finales[i]] == estado) return true;
    }
    return false;
}