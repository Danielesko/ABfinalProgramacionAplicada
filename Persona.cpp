#include <string>
using namespace std;
class Persona {
	int id;
	string nombre;
	string apellido;
	string dni;

public:
	Persona(int id, string nombre, string apellido, string dni) {
		this->id = id;
		this->nombre = nombre;
		this->apellido = apellido;
		this->dni = dni;
	}
	Persona() {
		this->id = 0;
		this->nombre = "";
		this->apellido = "";
		this->dni = "";
	}
	int getId() {
		return id;
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