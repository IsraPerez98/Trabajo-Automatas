#pragma once

#include<vector>
#include<string>

std::vector<std::string> separar_string_coma(std::string string_inicial);

void print_vector(std::vector<std::string> a);

bool verificar_estado_valido(std::string estado, std::vector<std::string> Q);

int obtener_posicion_estado(std::string estado, std::vector<std::string> Q);

void print_estados_posibles(std::vector<std::string> Q);


