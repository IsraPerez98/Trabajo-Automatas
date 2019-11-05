#pragma once

#include<vector>

#include "automata_obj.h"
#include "tabla_comparativa_obj.h"

void crear_matriz_compatibilidad(std::vector<std::vector<bool>> &compatibilidad, std::vector<tabla_comparativa> &tablas_comparativas, std::vector<Estado> &estados_obj);

void generar_vector_nd(std::vector<tabla_comparativa> tablas_comparativas, std::vector<std::vector<Estado*>> &estados_nd);

void eliminar_estados_nd(std::vector<std::vector<Estado*>> &estados_nd, std::vector<Estado> &estados_obj, std::vector<std::string> &Q, std::vector<std::string> Sigma,  std::vector<std::vector<std::string>> &tabla_transicion, int *estado_inicial, std::vector<int> &estados_finales);