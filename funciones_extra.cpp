#include<vector>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include "funciones_extra.h"

using namespace std;

vector<string> separar_string_coma(string string_inicial)
{
    vector<string> vector_final;
    string str; //contiene un solo valor
    for(unsigned int i=0; i<string_inicial.length(); i++) // separamos los estados y los guardamos en el vector_final
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

bool is_on_string_vector (vector<string> v,string s)
{
    for(int i=0;i<v.size();i++)
    {
        if((v[i].compare(s))==0)
            return true;
    }
    return false;
}

bool palabra_valida (vector<string>Sigma,string word)
{
    string str;
    for(int i=0;i<word.length();i++)
    {
        str.push_back(word[i]);
        if(is_on_string_vector(Sigma,str)==false)
            return false;
        str.clear();
    }
    return true;
}

void print_vector(vector<string> a)
{
    cout << "{";
    for(int i=0; i<a.size();i++)
    {
        if(i+1 == a.size())
            cout << a[i] << "}";
        else
            cout << a[i] <<", ";
    }
    cout<<endl<<endl;
}

bool verificar_estado_valido(string estado, vector<string> Q)
{
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

void print_estados_posibles(vector<string> Q)
{
    cout << "Valores posibles: ";
    for(int j=0;j<Q.size();j++)
    {
        cout << Q[j] << "  ";
    }
    cout << endl;
}

void verificar(string s,int& n)
{
    do{
        cout << s;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cin >> n;
    }while (cin.fail());
}

void limpiar()
{
    cin.clear();
    fflush(stdin);
}

bool is_on_vector(vector<int> V,int q )
{
    for(int i=0;i<V.size();i++)
    {
        if(V[i] == q)
            return true;
    }
    return false;
}

bool is_on_map(map<string, string> M,string qx,string qy,string w)
{
    map<string,string>::iterator itr;
    itr = M.find(w);
}
