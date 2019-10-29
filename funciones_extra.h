#pragma once

#include<vector>
#include<string>
#include<map>

std::vector<std::string> separar_string_coma(std::string string_inicial);

void print_vector(std::vector<std::string> a);

bool verificar_estado_valido(std::string estado, std::vector<std::string> Q);

bool is_on_string_vector (std::vector<std::string> v,std::string s);

bool palabra_valida (std::vector<std::string>Sigma,std::string word);

int obtener_posicion_estado(std::string estado, std::vector<std::string> Q);

void print_estados_posibles(std::vector<std::string> Q);

void verificar(std::string s,int& n);

void limpiar();

bool is_on_vector(std::vector<int> V,int q);

bool is_on_map(std::map<std::string,std::string> M,std::string qx,std::string qy,std::string w);
