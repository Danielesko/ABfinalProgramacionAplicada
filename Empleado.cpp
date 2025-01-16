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
			cout << "No se encontró ningún empleado con ese nombre." << endl;
		}
		else {
			string empleado = jsonToString(empleadosFinal);
			cout << empleado;
		}
	}
}
void eliminarEmpleado(string dni) {
	Empleado e = buscarEmpleadoDni(dni);
	if (e.getId() < 0) {
		cout << "El empleado no existe, no se puede modificar." << endl;
		return;
	}
	else {
		cout << "Empleado encontrado. Ingrese los nuevos datos." << endl;
	}
	ifstream archivoLectura("empleados.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de empleados." << endl;
		return;
	}
	json empleados;
	archivoLectura >> empleados;
	archivoLectura.close();
	json empleadosActualizados;
	for (int i = 0; i < empleados.size(); i++) {
		if (empleados[i].contains("dni") && empleados[i]["dni"] != dni) {
			empleadosActualizados.push_back(empleados[i]);
		}
	}
	ofstream archivo("empleados.json");
	if (!archivo.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de empleados." << endl;
		return;
	}
	else {
		archivo << empleadosActualizados.dump(4);
		archivo.close();
		cout << "Empleado eliminado exitosamente." << endl;
	}
}
Empleado buscarEmpleadoDni(string dni) {
	Empleado e = Empleado();
	ifstream archivo("empleados.json");
	if (!archivo.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de empleados." << endl;
		return e;
	}
	json empleados;
	try {
		archivo >> empleados;
	}
	catch (const json::parse_error& er) {
		cerr << "Error al leer el archivo JSON: " << er.what() << endl;
		return e;
	}
	archivo.close();
	for (int i = 0; i < empleados.size(); i++) {
		if (empleados[i].contains("dni") && empleados[i]["dni"] == dni) {
			e = Empleado(
				empleados[i]["nombre"].get<std::string>(),
				empleados[i]["apellido"].get<std::string>(),
				empleados[i]["dni"].get<std::string>(),
				empleados[i]["telefono"].get<std::string>(),
				empleados[i]["categoria"].get<std::string>()
			);
			break;
		}
	}
	archivo.close();
	return e;
}
void menuModificarEmpleado() {
	cout << "1.Modificar dni" << endl;
	cout << "2.Modificar nombre" << endl;
	cout << "3.Modificar apellido" << endl;
	cout << "4.Modificar telefono" << endl;
	cout << "5.Modificar categoria" << endl;
	cout << "0.Salir" << endl;
	int num = leerOpcion();
	string dni;
	dni = leerDni("Ingrese el dni del empleado para modificar: ");
	switch (num) {
	case 1:
		modificarEmpleadoDni(dni);
		break;
	case 2:
		modificarEmpleadoNombre(dni);
		break;
	case 3:
		modificarEmpleadoApellido(dni);
		break;
	case 4:
		modificarEmpleadoTlf(dni);
		break;
	case 5:
		//mofificarEmpleadoCategoria(dni);
		break;
	case 0:
		cout << "Saliendo del sistema de gestión de modificacion de pacientes..." << endl;
		break;
	default:
		cout << "Opción no válida. Intente nuevamente." << endl;
		break;
	}
}
void modificarEmpleadoDni(string dni) {
	Empleado e = buscarEmpleadoDni(dni);
	if (e.getId() == 0) {
		cout << "El empleado no existe, no se puede modificar." << endl;
		return;
	}
	else {
		cout << "Empleado encontrado. Ingrese los nuevos datos." << endl;
	}
	string dniNuevo = leerDni("Ingrese el nuevo DNI: ");
	Empleado empleadoActualizado(
		e.getNombre(),
		e.getApellido(),
		dniNuevo,
		e.getTlf(),
		e.getCategoria()
	);
	ifstream archivoLectura("empleados.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de empleados." << endl;
		return;
	}
	json empleados;
	archivoLectura >> empleados;
	archivoLectura.close();
	for (auto& empleado : empleados) {
		if (empleado.contains("dni") && empleado["dni"] == dni) {
			empleado = empleadoActualizado.to_json();
			break;
		}
	}
	ofstream archivoEscritura("empleados.json");
	if (!archivoEscritura.is_open()) {
		cerr << "Error: No se pudo escribir en el archivo de empleados." << endl;
		return;
	}
	archivoEscritura << empleados.dump(4);
	archivoEscritura.close();
	cout << "Empleado modificado exitosamente." << endl;
}
void modificarEmpleadoNombre(string dni) {
	Empleado e = buscarEmpleadoDni(dni);
	if (e.getId() == 0) {
		cout << "El empleado no existe, no se puede modificar." << endl;
		return;
	}
	else {
		cout << "Empleado encontrado. Ingrese los nuevos datos." << endl;
	}
	string nombreNuevo = leerNombreApellido("Ingrese el nuevo nombre: ");
	Empleado empleadoActualizado(
		nombreNuevo,
		e.getApellido(),
		e.getDni(),
		e.getTlf(),
		e.getCategoria()
	);
	ifstream archivoLectura("empleados.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de empleados." << endl;
		return;
	}
	json empleados;
	archivoLectura >> empleados;
	archivoLectura.close();
	for (auto& empleado : empleados) {
		if (empleado.contains("dni") && empleado["dni"] == dni) {
			empleado = empleadoActualizado.to_json();
			break;
		}
	}
	ofstream archivoEscritura("empleados.json");
	if (!archivoEscritura.is_open()) {
		cerr << "Error: No se pudo escribir en el archivo de empleados." << endl;
		return;
	}
	archivoEscritura << empleados.dump(4);
	archivoEscritura.close();
	cout << "Empleado modificado exitosamente." << endl;
}
void modificarEmpleadoApellido(string dni) {
	Empleado e = buscarEmpleadoDni(dni);
	if (e.getId() == 0) {
		cout << "El empleado no existe, no se puede modificar." << endl;
		return;
	}
	else {
		cout << "Empleado encontrado. Ingrese los nuevos datos." << endl;
	}
	string apellidoNuevo = leerNombreApellido("Ingrese el nuevo apellido: ");
	Empleado empleadoActualizado(
		e.getNombre(),
		apellidoNuevo,
		e.getDni(),
		e.getTlf(),
		e.getCategoria()
	);
	ifstream archivoLectura("empleados.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de empleados." << endl;
		return;
	}
	json empleados;
	archivoLectura >> empleados;
	archivoLectura.close();
	for (auto& empleado : empleados) {
		if (empleado.contains("dni") && empleado["dni"] == dni) {
			empleado = empleadoActualizado.to_json();
			break;
		}
	}
	ofstream archivoEscritura("empleados.json");
	if (!archivoEscritura.is_open()) {
		cerr << "Error: No se pudo escribir en el archivo de empleados." << endl;
		return;
	}
	archivoEscritura << empleados.dump(4);
	archivoEscritura.close();
	cout << "Empleado modificado exitosamente." << endl;
}
void modificarEmpleadoTlf(string dni) {
	Empleado e = buscarEmpleadoDni(dni);
	if (e.getId() == 0) {
		cout << "El empleado no existe, no se puede modificar." << endl;
		return;
	}
	else {
		cout << "Empleado encontrado. Ingrese los nuevos datos." << endl;
	}
	string tlfNuevo = leerTlf("Ingrese el nuevo teléfono: ");
	Empleado empleadoActualizado(
		e.getNombre(),
		e.getApellido(),
		e.getDni(),
		tlfNuevo,
		e.getCategoria()
	);
	ifstream archivoLectura("empleados.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de empleados." << endl;
		return;
	}
	json empleados;
	archivoLectura >> empleados;
	archivoLectura.close();
	for (auto& empleado : empleados) {
		if (empleado.contains("dni") && empleado["dni"] == dni) {
			empleado = empleadoActualizado.to_json();
			break;
		}
	}
	ofstream archivoEscritura("empleados.json");
	if (!archivoEscritura.is_open()) {
		cerr << "Error: No se pudo escribir en el archivo de empleados." << endl;
		return;
	}
	archivoEscritura << empleados.dump(4);
	archivoEscritura.close();
	cout << "Empleado modificado exitosamente." << endl;
}