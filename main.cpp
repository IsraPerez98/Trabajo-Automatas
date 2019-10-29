#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>


#include "funciones_extra.h"
#include "ingreso_automatas.h"
#include "automata_obj.h"

using namespace std;

int main()
{
    string estado = "NO INGRESADO";
    string word;
    int opcion;
    int auto_opcion;

    int estado_inicial; // indice del vector Q, con el estado inicial
    vector<int> estados_finales; // indices del vector Q para los estados finales

    vector<string> Q; //estados
    vector<string> Sigma; //alfabeto

    pedir_estados(Q);
    pedir_alfabeto(Sigma);

    vector<Estado> Automata; //Vector de objetos estado
    vector<Estado> anfdtoafd; //Para guardar conversión de automata

    while(opcion!=7){
        system("cls");
        cout << "Dise" <<char(164)<<"ador de aut"<<char(162)<<"matas\t\t\tESTADO: "<<estado<<endl<<endl;
        cout << "1- Ingresar transiciones\n2- Convertir AFND a AFD\n3- Verificar si la palabra es reconocible por el automata\n4- Obtener AFD equivalente\n5- Simplificar AFD\n6- Mostrar tabla de transici"<<char(162)<<"n\n7- Salir\n\n";
        cout << "Ingrese una opci" <<char(162)<<"n: " ;
        cin >> opcion;

        if (cin.fail()){
            system ("cls");
            cout << "ERROR: Ingrese un n"<<char(163)<<"mero...\n";
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            system("pause");
        }
        else{
            switch(opcion){
            case 1:
            {
                if(estado=="NO INGRESADO")
                {
                    system("cls");

                    limpiar(); //limpia el buffer de cin

                    cout<<"Estados:\n";
                    print_vector(Q);
                    cout<<"Alfabeto:\n";
                    print_vector(Sigma);

                    cout << "Que desea ingresar?:\n1)AFD\n2)ANFD\n\n>>";
                    cin>>auto_opcion;
                    if(cin.fail())
                        verificar("ERROR, INGRESE 1 o 2\n",auto_opcion);

                    if(auto_opcion==1)
                    {
                        pedir_tabla_transicion(Q, Sigma,Automata);


                        for(unsigned int i=0; i<Q.size(); i++)
                        {
                            for(unsigned int j=0; j<Sigma.size(); j++)
                            {
                                cout << "transicion estado " << Q[i] << " con entrada " << Sigma[j] << " = " << Automata[i].transiciones.at(Sigma[j]) << endl;
                            }
                        }



                        estado_inicial = pedir_estado_inicial(Q,Automata);
                        Automata[estado_inicial].inicial = true;

                        cout << "Estado inicial: " << Q[estado_inicial] << endl;
                        pedir_estados_finales(Q, estados_finales);

                        //print estados finales
                        cout << "estados finales: " << endl;
                        for(unsigned int i=0;i<estados_finales.size();i++)
                        {
                            cout << Q[estados_finales[i]] << "  ";
                        }
                        cout << endl;
                        cout << "AFD Ingresado con " <<char(130)<< "xito!" <<endl;
                        estado = "AFD INGRESADO";
                        system("PAUSE");
                        system("cls");
                    }
                    if(auto_opcion==2)
                    {
                        while(1)
                        {
                            int palabras;
                            cout<<"Desea agregar una palabra de largo n al alfabeto?\n1)Si\n2)No\n>>";
                            cin>>palabras;
                            if(cin.fail())
                                verificar("ERROR: Ingrese 1 o 2",palabras);
                            else
                            {
                                if (palabras==1)
                                {

                                    limpiar();

                                    cout<<"Alfabeto disponible para formar la palabra: ";
                                    for(unsigned int i=0;i<Sigma.size();i++)
                                        cout<<Sigma[i]<<"   ";
                                    cout<<"Palabra: ";
                                    limpiar();
                                    getline(cin,word);
                                    if(palabra_valida(Sigma,word))
                                    {
                                        Sigma.push_back(word);
                                        Sigma.push_back("e");
                                        break;
                                    }
                                    else
                                    {
                                        word.clear();
                                        cout << "Ingrese una palabra valida..." << endl;
                                    }

                                }
                                if (palabras == 2)
                                {
                                    Sigma.push_back("e");
                                    break;
                                }
                            }
                        }

                        pedir_tabla_transicion_afnd(Q,Sigma,Automata);

                        for(unsigned int i=0; i<Q.size(); i++)
                        {
                            for(unsigned int j=0; j<Sigma.size(); j++)
                            {
                                cout << "transicion estado " << Q[i] << " con entrada " << Sigma[j] << " = " << Automata[i].transiciones.at(Sigma[j]) << endl;
                            }
                        }


                        estado_inicial = pedir_estado_inicial(Q,Automata);
                        Automata[estado_inicial].inicial = true;

                        cout << "Estado inicial: " << Q[estado_inicial] << endl;
                        pedir_estados_finales(Q, estados_finales);

                        //print estados finales
                        cout << "estados finales: " << endl;
                        for(unsigned int i=0;i<estados_finales.size();i++)
                        {
                            cout << Q[estados_finales[i]] << "  ";
                        }
                        cout << endl;
                        cout << "ANFD Ingresado con " <<char(130)<< "xito!" <<endl;
                        estado = "ANFD INGRESADO";
                        system("PAUSE");
                        system("cls");
                    }
                    else
                    {
                        cout<<"ERROR: Ingrese una opci"<<char(162)<<"n v"<<char(160)<<"lida..."<<endl;
                        system("pause");
                        system("cls");
                    }
                    break;
                }
            }

            case 2:
                system("cls");
                cout << "En construccion..." <<endl;
                system("pause");
                system("cls");
                break;
            case 3 :
                system("cls");
                cout << "En construccion..." <<endl;
                system("pause");
                system("cls");
                break;
            case 4 :
                system("cls");
                cout << "En construccion..." <<endl;
                system("pause");
                system("cls");
                break;
            case 5:
             {
                 vector<Estado>automat_simp = simplificar(Automata,estado_inicial,estados_finales,Q,Sigma);
                 //mostrar_tabla_transicion(tabla_simp,Sigma,Q);
                 break;
             }
            case 6:
                mostrar_tabla_transicion(Sigma,Q,Automata);
                cout<<endl;
                system("pause");
                system("cls");
                break;
            case 7:
                break;
            default:
                cout << "ERROR: Ingrese una opci"<<char(162)<<"n v"<<char(160)<<"lida...\n\n";
                system("pause");
            }
        }
     }




    return 0;
}
