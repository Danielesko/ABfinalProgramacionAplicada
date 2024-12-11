#include "ABfinalProgramacionAplicada.h"
#include "Persona.h"

void escribirClienteArchivo(json cliente) {
	ofstream archivo("clientes.json", ios::app);
	ifstream archivoLeer("clientes.json");
	json clientesExistentes;
	if (archivoLeer.is_open()) {
		archivoLeer >> clientesExistentes;
		clientesExistentes = json::array();
		archivoLeer.close();
	}
	else {
		clientesExistentes = json::array();
	}
	clientesExistentes.push_back(cliente);
	if (archivo.is_open()) {
		archivo << cliente.dump(4);
		archivo.close();
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
	string tlf;
	string fechaNac;
	string localidad;
    cout << "Ingrese el id del cliente: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese el nombre del cliente: ";
    getline(cin, nombre);
    cout << "Ingrese el apellido del cliente: ";
    getline(cin, apellido);
    cout << "Ingrese el dni del cliente: ";
    getline(cin, dni);
    cout << "Ingrese el telefono del cliente: ";
    getline(cin, tlf);
    cout << "Ingrese la fecha de nacimiento del cliente: ";
    getline(cin, fechaNac);
    cout << "Ingrese la localidad del cliente: ";
    getline(cin, localidad);
	Cliente cliente = Cliente(id, nombre, apellido, dni, tlf, fechaNac, localidad);
	escribirClienteArchivo(cliente.to_json());
}
void mostrarPacientes() {
	ifstream archivo;
	json datos;
	archivo.open("clientes.json");
	if (archivo.is_open()) {
		archivo >> datos;
		if (datos.size() == 0) {
			cout << "No hay pacientes registrados." << endl;
		}
		else if (datos.is_array()) {
			for (int i = 0; i < datos.size(); i++) {
				cout << datos.dump(4) << endl;
			}
		}
		else {
			cout << datos.dump(4) << endl;
		}
	}else {
		cout << "No se pudo abrir el archivo para leer." << endl;
	}
}