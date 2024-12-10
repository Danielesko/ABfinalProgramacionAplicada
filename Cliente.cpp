#include "Persona.h" 
#include "ABfinalProgramacionAplicada.h"

class Cliente :public Persona {
	string fechaNac;
	string localidad;
public:
	Cliente(int id, string nombre, string apellido, string dni, int tlf, string fechaNac, string localidad)
		: Persona(id, nombre, apellido, dni, tlf), fechaNac(fechaNac), localidad(localidad) {
	}

	json to_json() const {
		return json{
			{"id", getId()},
			{"nombre", getNombre()},
			{"apellido", getApellido()},
			{"dni", getDni()},
			{"telefono", getTlf()},
			{"fechaNac", fechaNac},
			{"localidad", localidad}
		};
	}
	bool crearCliente() {
		int id;
		string nombre;
		string apellido;
		string dni;
		int tlf;
		string fechaNac;
		string localidad;
		cout << "Ingrese el id del cliente" << endl;
		cin >> id;
		cout << "Ingrese el nombre del cliente" << endl;
		cin >> nombre;
		cout << "Ingrese el apellido del cliente" << endl;
		cin >> apellido;
		cout << "Ingrese el dni del cliente" << endl;
		cin >> dni;
		cout << "Ingrese el telefono del cliente" << endl;
		cin >> tlf;
		cout << "Ingrese la fecha de nacimiento del cliente" << endl;
		cin >> fechaNac;
		cout << "Ingrese la localidad del cliente" << endl;
		cin >> localidad;
		Cliente cliente = Cliente(id, nombre, apellido, dni, tlf, fechaNac, localidad);
		abrirArchivo("clientes.json");

		json jsonC = cliente.to_json();

		return true;
	}

};
