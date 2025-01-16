#include "ABfinalProgramacionAplicada.h"

int Empleado::idAnterior = 1;
void crearEmpleado() {
	string nombre = leerNombreApellido("Ingrese el nombre del empleado: ");
	string apellido = leerNombreApellido("Ingrese el apellido del empleado: ");
	string dni = leerDni("Ingrese el DNI del empleado: ");
	string tlf = leerTlf("Ingrese el tel�fono del empleado: ");
	string categoria = leerCadenaNoVacia("Ingrese la categor�a del empleado: ");
	Empleado empleado = Empleado(nombre, apellido, dni, tlf, categoria);
	escribirEmpleadoArchivo(empleado.to_json());
}
void escribirEmpleadoArchivo(json empleado) {
	json empleadosExistentes;
	ifstream archivoLeer("empleados.json", ios::in | ios::binary);
	if (archivoLeer.is_open() && archivoLeer.peek() != ifstream::traits_type::eof()) {
		archivoLeer >> empleadosExistentes;
		if (!empleadosExistentes.is_array()) {
			empleadosExistentes = json::array();
		}
		archivoLeer.close();
	}
	else {
		empleadosExistentes = json::array();
	}
	empleadosExistentes.push_back(empleado);
	ofstream archivoEscribir("empleados.json", ios::out | ios::binary);
	if (archivoEscribir.is_open()) {
		archivoEscribir << empleadosExistentes.dump(4);
		archivoEscribir.close();
		cout << "Empleado guardado correctamente." << endl;
	}
	else {
		cout << "No se pudo abrir el archivo para guardar." << endl;
	}
	Empleado::guardarId();
}
void mostrarEmpleados() {
	ifstream archivo;
	json datos;
	archivo.open("empleados.json");
	if (archivo.is_open()) {
		try {
			archivo >> datos;
		}
		catch (const json::parse_error& e) {
			cerr << "Error al leer el archivo JSON: " << e.what() << endl;
			archivo.close();
			return;
		}
		if (datos.size() == 0) {
			cout << "No hay empleados registrados." << endl;
		}else if (datos.is_array()) {
			string empleados = jsonToString(datos);
			cout << empleados;
		}
	}else {
		cout << "No se pudo abrir el archivo para leer." << endl;
	}
}
void buscarEmpleado(string nombre) {
	ifstream archivo("empleados.json", ios::in | ios::binary);
	int contador = 0;
	if (archivo.is_open()) {
		json empleados;
		json empleadosFinal;
		archivo >> empleados;
		for (int i = 0; i < empleados.size(); i++) {
			if (empleados[i].contains("nombre") && empleados[i]["nombre"] == nombre) {
				empleadosFinal.push_back(empleados[i]);
				contador++;
			}
		}
		if (contador == 0) {
			cout << "No se encontr� ning�n empleado con ese nombre." << endl;
		}
		else {
			string empleado = jsonToString(empleadosFinal);
			cout << empleado;
		}
	}
}