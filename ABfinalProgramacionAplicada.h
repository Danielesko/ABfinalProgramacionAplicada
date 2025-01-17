// ABfinalProgramacionAplicada.h: archivo de inclusión para archivos de inclusión estándar del sistema,
// o archivos de inclusión específicos de un proyecto.

#pragma once

#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "Persona.h"
#include "Cliente.h"
#include "Empleado.h"
#include "Funciones.h"
#include "Cita.h"

// TODO: Haga referencia aquí a los encabezados adicionales que el programa requiere.
void crearCliente();
void escribirClienteArchivo(json cliente);
void menuPacientes();
void menuEmpleados();
void menuQuejas();
void menuCitas();
string jsonToString(json clientesJson);