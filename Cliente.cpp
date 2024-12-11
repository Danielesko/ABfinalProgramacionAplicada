#include "ABfinalProgramacionAplicada.h"
#include "Persona.h"
#include "Funciones.h"
void escribirClienteArchivo(json cliente) {
	json clientesExistentes;
	ifstream archivoLeer("clientes.json");

	if (archivoLeer.is_open() && archivoLeer.peek() != ifstream::traits_type::eof()) {
		archivoLeer >> clientesExistentes;
		if (!clientesExistentes.is_array()) {
			cout << "El archivo no contiene un array válido. Se sobrescribirá con un array nuevo." << endl;
			clientesExistentes = json::array();
		}
		archivoLeer.close();
	}else {
		clientesExistentes = json::array(); 
	}
	clientesExistentes.push_back(cliente);

	ofstream archivoEscribir("clientes.json", ios::trunc); 
	if (archivoEscribir.is_open()) {
		archivoEscribir << clientesExistentes.dump(4); 
		archivoEscribir.close();
		cout << "Cliente guardado correctamente." << endl;
	}
	else {
		cout << "No se pudo abrir el archivo para guardar." << endl;
	}
}

void crearCliente() {
	int id;
    cout << "Ingrese el id del cliente: ";
    while (!(cin >> id)) {
        cout << "ID inválido. Ingrese un número entero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string nombre = leerCadenaNoVacia("Ingrese el nombre del cliente: ");
	string apellido = leerCadenaNoVacia("Ingrese el apellido del cliente: ");
	string dni = leerCadenaNoVacia("Ingrese el DNI del cliente: ");
	string tlf = leerCadenaNoVacia("Ingrese el teléfono del cliente: ");
	string fechaNac = leerCadenaNoVacia("Ingrese la fecha de nacimiento del cliente: ");
	string localidad = leerCadenaNoVacia("Ingrese la localidad del cliente: ");
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
			cout << datos.dump(4) << endl;
		}
	}else {
		cout << "No se pudo abrir el archivo para leer." << endl;
	}
}
void buscarPaciente(string nombre) {
	ifstream archivo;
	archivo.open("clientes.json");
	int contador = 0;
	if (archivo.is_open()) {
		json pacientes;
		archivo >> pacientes;
		for (int i = 0; i < pacientes.size(); i++) {
			if (pacientes[i].contains("nombre") && pacientes[i]["nombre"] == nombre) {
				cout << pacientes[i].dump(4) << endl;
				contador++;
			}
		}
		if (contador == 0) {
			cout << "No se encontró ningún paciente con ese nombre." << endl;
		}
	}
}