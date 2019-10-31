#pragma once

#include<vector>
#include<string>
#include "automata_obj.h"

std::vector<std::string> separar_string_coma(std::string string_inicial);

void print_vector(std::vector<std::string> a);

bool verificar_estado_valido(std::string estado, std::vector<std::string> Q, bool considerar_guion);

int obtener_posicion_estado(std::string estado, std::vector<std::string> Q);

void print_estados_posibles(std::vector<std::string> Q, bool incluir_guion);

bool estado_es_final(std::string estado, std::vector<std::string> Q, std::vector<int> estados_finales);

void print_tabla_transicion_afnd(std::vector<std::vector<std::vector<Estado*>>>, std::vector<string> Q, std::vector<string> Sigma);