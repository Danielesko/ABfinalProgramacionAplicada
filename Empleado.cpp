#include "ABfinalProgramacionAplicada.h"

int Empleado::idAnterior = 1;
void crearEmpleado() {
	string nombre = leerNombreApellido("Ingrese el nombre del empleado: ");
	string apellido = leerNombreApellido("Ingrese el apellido del empleado: ");
	string dni = leerDni("Ingrese el DNI del empleado: ");
	string tlf = leerTlf("Ingrese el teléfono del empleado: ");
	string categoria = leerCadenaNoVacia("Ingrese la categoría del empleado: ");
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