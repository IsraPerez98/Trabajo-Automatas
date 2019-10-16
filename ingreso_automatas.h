#pragma once
#include<vector>

void pedir_estados(std::vector<std::string> &Q);

void pedir_alfabeto(std::vector<std::string> &Sigma);

void pedir_tabla_transicion(std::vector<std::vector<std::string>> &tabla, std::vector<std::string> Q, std::vector<std::string> Sigma); // https://stackoverflow.com/a/34182883

int pedir_estado_inicial(std::vector<std::string> Q);

void pedir_estados_finales(std::vector<std::string> Q, std::vector<int> &estados_finales);

