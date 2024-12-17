#include "ABfinalProgramacionAplicada.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
int leerOpcion() {
	int opcion;
	while (true) {
		cout << "Ingrese una opción: ";
		cin >> opcion;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Entrada inválida. Intente nuevamente." << endl;
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return opcion;
		}
	}
}
void menuPacientes() {
	int num;
	do {
		cout << "1. Ingresar un nuevo paciente" << endl;
		cout << "2. Mostrar todos los pacientes" << endl;
		cout << "3. Buscar un paciente" << endl;
		cout << "4. Modificar un paciente" << endl;
		cout << "5. Eliminar un paciente" << endl;
		cout << "0. Salir" << endl;

		num = leerOpcion(); 
		string dni;
		Cliente paciente = Cliente();
		string nombre;
		switch (num) {
		case 1:
			crearCliente();
			break;
		case 2:
			mostrarPacientes();
			break;
		case 3:
			nombre = leerCadenaNoVacia("Ingrese el nombre del paciente: ");
			buscarPaciente(nombre);
			break;
		case 4:
			menuModificarPaciente();
			break;
		case 5:
			mostrarPacientes();
			dni = leerCadenaNoVacia("Ingrese el dni del paciente para eliminar: ");
			eliminarPaciente(dni); 
			break;
		case 0:
			cout << "Saliendo del sistema de gestión de pacientes..." << endl;
			break;
		default:
			cout << "Opción no válida. Intente nuevamente." << endl;
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
string leerCadenaNoVacia(const string& mensaje) {
	string entrada;
	cout << mensaje;
	while (true) {
		getline(cin, entrada);
		if (!entrada.empty()) {
			break; 
		}
		cout << "El campo no puede estar vacío. Intente nuevamente: ";
	}
	return entrada;
}
