#pragma once
#include<vector>
#include"automata_obj.h"

void pedir_estados(std::vector<std::string> &Q);

void pedir_alfabeto(std::vector<std::string> &Sigma);

void pedir_tabla_transicion(std::vector<std::string> Q, std::vector<std::string> Sigma,std::vector<Estado> &Automat); // https://stackoverflow.com/a/34182883

void pedir_tabla_transicion_afnd(std::vector<std::string> Q, std::vector<std::string> Sigma,std::vector<Estado> &Automat);

int pedir_estado_inicial(std::vector<std::string> Q,std::vector<Estado> &automat);

void pedir_estados_finales(std::vector<std::string> Q, std::vector<int> &estados_finales);

void mostrar_tabla_transicion (std::vector<std::string> Sigma,std::vector<std::string> Q,std::vector<Estado>automat);

std::vector<Estado> simplificar (std::vector<Estado> automat,int qinicial,std::vector<int> qfinales,std::vector<std::string>Q,std::vector<std::string>S);
