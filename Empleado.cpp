#include "ABfinalProgramacionAplicada.h"
#include "Persona.cpp" 


class Empleado : public Persona {
	string disponibilidad;
	Empleado(int id, string nombre, string apellido, string dni, int tlf, string disponibilidad) : Persona(id, nombre, apellido, dni, tlf) {
		this->disponibilidad = disponibilidad;
	}
};