#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<iterator>

#include "funciones_extra.h"
#include "ingreso_automatas.h"

using namespace std;

void pedir_estados(vector<string> &Q)
{
    cout << "Ingrese los estados separados por una coma.\n";
    cout << "Q: ";

    string estados_str;
    getline(cin, estados_str);

    Q = separar_string_coma(estados_str);
}

void pedir_alfabeto(vector<string> &Sigma)
{
    cout << "Ingrese el alfabeto utilizado por el automata (separado por una coma).\n";
    string alfabeto;
    getline(cin,alfabeto);
    Sigma = separar_string_coma(alfabeto);
}

void pedir_tabla_transicion(vector<string> Q, vector<string> Sigma, vector<Estado> &Automat) // https://stackoverflow.com/a/34182883
{
    for(unsigned int n=0;n<Q.size();n++)
        Automat.push_back(Estado(Q[n],false));

    for(unsigned int i=0;i<Q.size();i++)
    {
        cout << "i: " << i << endl;
        for(unsigned int j=0;j<Sigma.size();j++)
        {
            while(1)
            {
                cout << "Ingrese la transicion de " << Q[i] << " con entrada " << Sigma[j] << endl;
                print_estados_posibles(Q);
                string estado_transicion;
                getline(cin, estado_transicion);

                bool transicion_correcta = verificar_estado_valido(estado_transicion, Q);
                if(transicion_correcta)
                {
                    cout << "fijando valor " << estado_transicion << endl;
                    Automat[i].transiciones.insert(pair<string,string> (Sigma[j],estado_transicion));
                    break;
                }

            }
        }
    }
}

void pedir_tabla_transicion_afnd(vector<string> Q, vector<string> Sigma, vector<Estado> &Automat)
{
    for(unsigned int n=0;n<Q.size();n++)
        Automat.push_back(Estado(Q[n],false));

    for(unsigned int i=0;i<Q.size();i++)
    {
        cout << "i: " << i << endl;
        for(unsigned int j=0;j<Sigma.size();j++)
        {
            while(1)
            {
                cout << "Ingrese la transicion de " << Q[i] << " con entrada " << Sigma[j] << endl;
                cout<< "(0 para continuar)" << endl;
                print_estados_posibles(Q);

                string estado_transicion;
                getline(cin, estado_transicion);

                if(estado_transicion=="0")
                {
                    Automat[i].transiciones.insert(pair<string,string> (Sigma[j],"-"));
                    break;
                }
                else
                {

                    bool transicion_correcta = verificar_estado_valido(estado_transicion, Q);
                    if(transicion_correcta)
                    {
                        cout << "fijando valor " << estado_transicion << endl;
                        Automat[i].transiciones.insert(pair<string,string> (Sigma[j],estado_transicion));
                        break;
                    }
                }

            }
        }
    }

}

int pedir_estado_inicial(vector<string> Q,vector<Estado>& Automat)
{
    while(1)
    {
        cout << "Ingrese el estado incial." << endl;
        print_estados_posibles(Q);
        cout << endl << "Estado: ";
        string estado;
        getline(cin, estado);
        int posicion = obtener_posicion_estado(estado, Q);
        if(posicion != -1)
            return posicion;
    }
}

void pedir_estados_finales(vector<string> Q, vector<int> &estados_finales)
{
    bool finalizado = false;
    while(!finalizado)
    {
        cout << "Ingrese los estados finales, separados por una coma." << endl;
        print_estados_posibles(Q);
        cout << "Estados: ";
        string estados_finales_str;
        getline(cin,estados_finales_str);
        vector<string> estados_separados = separar_string_coma(estados_finales_str);
        finalizado = true;
        for(int i=0;i<estados_separados.size();i++)
        {
            int posicion = obtener_posicion_estado(estados_separados[i], Q);
            if(posicion == -1)
            {
                finalizado = false;
                break;
            }
            else
            {
                estados_finales.push_back(posicion);
            }
        }
    }
}

void mostrar_tabla_transicion (vector<string> Sigma,vector<string> Q,vector<Estado>automat)
{

    for(unsigned int n=0;n<Sigma.size();n++)
    {
        if(n==0)
            cout<<"\t";
        cout << Sigma[n] << "\t";
    }

    for(unsigned int i=0;i<automat.size();i++)
    {
        cout<<endl;
        for(int j=0;j<Sigma.size();j++)
        {
            if(j==0)
                cout << Q[i] << "\t";
            cout << automat[i].transiciones.at(Sigma[j]) << "\t";
        }
    }

}

vector<Estado> simplificar(vector<Estado> automat,int qinicial,vector<int>qfinales,vector<string>Q,vector<string>S)
{
    vector<Estado> simp;
    vector<string> comp; //Para mostrar la compatibilidad entre estados
    vector<int> posp; //Posiciones de los estados pendientes
    map<string,string> pendiente; //Guarda el par de estados a verificar
    map<string,string> nocomp; //Estados no compatibles


    simp = automat;

    for(unsigned int i=1;i<Q.size();i++)
    {
        for(int j=0;j<i;j++)
        {
            if(is_on_vector(qfinales,j))
            {
                if(is_on_vector(qfinales,i)==false)
                {
                    comp.push_back("X");
                    nocomp.insert(pair<string,string>(Q[i],Q[j]));
                }
                else
                {
                    comp.push_back(".");
                    posp.push_back((comp.size()-1));
                    pendiente.insert(pair<string,string> (Q[i],Q[j]));
                }

            }
            else
            {
                if(is_on_vector(qfinales,i))
                {
                     comp.push_back("X");
                     nocomp.insert(pair<string,string>(Q[i],Q[j]));
                }
                else
                {
                    comp.push_back(".");
                    posp.push_back((comp.size()-1));
                    pendiente.insert(pair<string,string> (Q[i],Q[j]));
                }
            }
        }
    }
    int cont=0;
    limpiar();
    for(unsigned int i=1;i<Q.size();i++)
    {
        for(unsigned int j=0;j<i;j++)
        {
            if(j==0)
                cout << Q[i]<<"\t";
            cout<<comp[cont]<<"\t";
            cont++;
        }
        cout<<endl;
    }
    for(unsigned int n=1;n<Q.size();n++)
    {
        if(n==1)
            cout << "\t";
        cout << Q[n-1] << "\t";
    }
    cout<<endl<<endl;
    system("pause");

    if(pendiente.empty()==false)
    {
        cont = 0;
        map<string,string>::iterator itr;
        for (itr=pendiente.begin(); itr!=pendiente.end(); ++itr)
        {
            int posqx = obtener_posicion_estado(itr->first,Q);
            int posqy = obtener_posicion_estado(itr->second,Q);

            for(unsigned int i=0;i<S.size();i++)
            {
                if((automat[posqx].transiciones.at(S[i]) == automat[posqy].transiciones.at(S[i]))&&(i+1==S.size()))
                    comp[posp.at(cont)] = "ND";
                else if((automat[posqx].transiciones.at(S[i]) != automat[posqy].transiciones.at(S[i])))
                {
                    comp[posp.at(cont)] = "X";
                    break;
                }
            }
            cont++;
        }
        cont=0;

        for(unsigned int i=1;i<Q.size();i++)
        {
            for(unsigned int j=0;j<i;j++)
            {
                if(j==0)
                    cout << Q[i]<<"\t";
                cout<<comp[cont]<<"\t";
                cont++;
            }
            cout<<endl;
        }
        for(unsigned int n=1;n<Q.size();n++)
        {
            if(n==1)
                cout << "\t";
            cout << Q[n-1] << "\t";
        }
        cout<<endl<<endl;
        system("pause");

        }

        return simp;
}




