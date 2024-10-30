#include "ABfinalProgramacionAplicada.h"
class Persona {
	int id;
	string nombre;
	string apellido;
	string dni;
	int tlf;

public:
	Persona(int id, string nombre, string apellido, string dni, int tlf) {
		this->id = id;
		this->nombre = nombre;
		this->apellido = apellido;
		this->dni = dni;
		this->tlf = tlf;
	}
	Persona() {
		this->id = 0;
		this->nombre = "";
		this->apellido = "";
		this->dni = "";
		this->tlf = 0;
	}
	int getId() {
		return id;
	}
	int getTlf() {
		return tlf;
	}
	string getNombre() {
		return nombre;
	}
	string getApellido() {
		return apellido;
	}
	string getDni() {
		return dni;
	}
	void setId(int id) {
		this->id = id;
	}
	void setTlf(int tlf) {
		this->tlf = tlf;
	}
	void setNombre(string nombre) {
		this->nombre = nombre;
	}
	void setApellido(string apellido) {
		this->apellido = apellido;
	}
	void setDni(string dni) {
		this->dni = dni;
	}

};