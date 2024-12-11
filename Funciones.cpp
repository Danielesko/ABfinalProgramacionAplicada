#include "ABfinalProgramacionAplicada.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
void menuPacientes() {
	int num;
	do {
		cout << "1. Ingresar un nuevo paciente" << endl;
		cout << "2. Mostrar todos los pacientes" << endl;
		cout << "3. Buscar un paciente" << endl;
		cout << "4. Modificar un paciente" << endl;
		cout << "5. Eliminar un paciente" << endl;
		cout << "0. Salir" << endl;
		cin >> num;
		switch (num) {
		case 1:
			crearCliente();
			break;
		case 2:
			mostrarPacientes();
			break;
		case 3:
			//buscarCliente();
			break;	
		case 4:
			//modificarCliente();
			break;
		case 5:
			//eliminarCliente();
			break;
		case 0:
			cout << "Saliendo." << endl;
			break;
		default:
			cout << "Opción no válida" << endl;
			break;
		}
	} while (num != 0);
}
void menuEmpleados() {
}
void menuQuejas() {
}
void menuCitas() {
}
string jsonToString(json clientesJson) {
	string pacientes = "";
	cout << "Pacientes: " << endl;
	for (int i = 0; i < clientesJson.size(); i++) {
		if (clientesJson[i].contains("nombre"))
			pacientes += "Nombre: " + clientesJson[i]["nombre"].get<std::string>() + "\n";
		if (clientesJson[i].contains("apellido"))
			pacientes += "Apellido: " + clientesJson[i]["apellido"].get<std::string>() + "\n";
		if (clientesJson[i].contains("dni"))
			pacientes += "DNI: " + clientesJson[i]["dni"].get<std::string>() + "\n";
		if (clientesJson[i].contains("telefono"))
			pacientes += "Telefono: " + clientesJson[i]["telefono"].get<std::string>() + "\n";
		if (clientesJson[i].contains("localidad"))
			pacientes += "Localidad: " + clientesJson[i]["localidad"].get<std::string>() + "\n";
		if (clientesJson[i].contains("fechaNac"))
			pacientes += "Fecha de nacimiento: " + clientesJson[i]["fechaNac"].get<std::string>() + "\n";
		pacientes += "\n";
	}
	return pacientes;
}
string leerCadenaNoVacia(const string &mensaje) {
	string entrada;
	cout << mensaje;
	while (getline(cin, entrada), entrada.empty()) {
		cout << "El campo no puede estar vacío. " << mensaje;
	}
	return entrada;
}