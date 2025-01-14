#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "Cliente.h"
#include <regex>

using json = nlohmann::json;
using namespace std;

void menuPacientes();
void menuEmpleados();
void menuQuejas();
void menuCitas();

string jsonToString(json clientesJson);

void crearCliente();
string leerCadenaNoVacia(const string &mensaje);
int leerOpcion();
string leerDni(const string& mensaje);
string leerFechaNac(const string& mensaje);
#endif 
