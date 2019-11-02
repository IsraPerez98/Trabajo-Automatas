#pragma once

#include<vector>
#include<string>
#include "automata_obj.h"

void print_tabla_transicion_afnd(std::vector<std::vector<std::vector<Estado*>>>, std::vector<string> Q, std::vector<string> Sigma);

void obtener_estados_pseudo(int posicion,std::vector<std::string> Q,std::vector<Estado> estados_obj,std::vector<Estado*> &pseudo_iniciales); // la posicion del estado en el vector estados_obj, estados_obj, y el vector donde se almacenan los estados pseudo

int combinar_estados(std::vector<Estado*> estados_anteriores, bool inicial, std::vector<std::string> &nueva_Q, std::vector<Estado> &nuevos_estados_obj);

void generar_nuevos_estados_afd(std::vector<std::string> Sigma, int posicion_estado, std::vector<Estado*> estados_a_combinar, std::vector<std::vector<std::vector<Estado*>>> tabla_transicion_afnd, std::vector<std::string> Q, std::vector<std::string> &nueva_Q, std::vector<std::vector<std::string>> &tabla_transicion, std::vector<Estado> &nuevos_estados_obj );