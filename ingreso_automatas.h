#pragma once
#include<vector>

bool preguntar_afd_o_afnd();

void pedir_estados(std::vector<std::string> &Q);

void pedir_alfabeto(std::vector<std::string> &Sigma);

void pedir_tabla_transicion(std::vector<std::vector<std::string>> &tabla, std::vector<std::string> Q, std::vector<std::string> Sigma, bool afd); // https://stackoverflow.com/a/34182883

void pedir_transiciones_epsilon(std::vector<std::vector<std::string>> &transiciones_epsilon, std::vector<std::string> Q);

int pedir_estado_inicial(std::vector<std::string> Q);

void pedir_estados_finales(std::vector<std::string> Q, std::vector<int> &estados_finales);

