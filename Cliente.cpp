#include "ABfinalProgramacionAplicada.h"
#include "Persona.cpp" 
class Cliente :public Persona {
	string fechaNac;
	string localidad;
	Cliente(int id, string nombre, string apellido, string dni, int tlf, string fechaNac, string localidad) : Persona(id, nombre, apellido, dni, tlf) {
		this->fechaNac = fechaNac;
		this->localidad = localidad;
	}
};