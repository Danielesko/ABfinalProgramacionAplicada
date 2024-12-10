#include "ABfinalProgramacionAplicada.h"
#include "Persona.h"
void escribirClienteArchivo(json cliente) {
	ofstream outputFile("clientes.json");
	if (outputFile.is_open()) {
		outputFile << cliente.dump(4);
		outputFile.close();
		cout << "Cliente guardado correctamente." << endl;
	}
	else {
		cout << "No se pudo abrir el archivo para guardar." << endl;
	}
}
void crearCliente() {
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
	escribirClienteArchivo(cliente.to_json());
}

class Cliente :public Persona {
	string fechaNac;
	string localidad;
public:
	Cliente() : Persona(0, "", "", "", 0), fechaNac(""), localidad("") {
	}

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
};
