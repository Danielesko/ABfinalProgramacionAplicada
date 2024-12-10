#pragma once
#pragma once

#include "ABfinalProgramacionAplicada.h"   

class Persona {
public:
	int id;
	string nombre;
	string apellido;
	string dni;
	int tlf;
	Persona(int id, string nombre, string apellido, string dni, int tlf);
	Persona();
	int getId();
	int getTlf();
	string getNombre();
	string getApellido();
	string getDni();
};
