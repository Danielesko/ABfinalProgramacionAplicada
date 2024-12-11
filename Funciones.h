#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "Cliente.h"
using json = nlohmann::json;
using namespace std;

void menuPacientes();
void menuEmpleados();
void menuQuejas();
void menuCitas();

string jsonToString(json clientesJson);

void crearCliente();
string leerCadenaNoVacia(const string &mensaje);
#endif 
