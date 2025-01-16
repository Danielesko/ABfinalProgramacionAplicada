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
			nombre = leerNombreApellido("Ingrese el nombre del paciente: ");
			buscarPaciente(nombre);
			break;
		case 4:
			menuModificarPaciente();
			break;
		case 5:
			mostrarPacientes();
			dni = leerDni("Ingrese el dni del paciente para eliminar: ");
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
	int num;
	do {
		cout << "1. Ingresar un nuevo empleado" << endl;
		cout << "2. Mostrar todos los empleados" << endl;
		cout << "3. Buscar un empleado" << endl;
		cout << "4. Modificar un empleado" << endl;
		cout << "5. Eliminar un empleado" << endl;
		cout << "0. Salir" << endl;
		num = leerOpcion();
		string dni;
		Empleado empleado = Empleado();
		string nombre;
		switch (num) {
		case 1:
			crearEmpleado();
			break;
		case 2:
			mostrarEmpleados();
			break;
		case 3:
			nombre = leerNombreApellido("Ingrese el nombre del empleado: ");
			buscarEmpleado(nombre);
			break;
		case 4:
			//menuModificarEmpleado();
			break;
		case 5:
			//mostrarEmpleados();
			dni = leerDni("Ingrese el dni del empleado para eliminar: ");
			//eliminarEmpleado(dni);
			break;
		case 0:
			cout << "Saliendo del sistema de gestión de empleados..." << endl;
			break;
		default:
			cout << "Opción no válida. Intente nuevamente." << endl;
			break;
		}
	} while (num != 0);
}	
void menuQuejas() {
}
void menuCitas() {
}
string jsonToString(json clientesJson) {
	string frase = "";
	for (int i = 0; i < clientesJson.size(); i++) {
		if (clientesJson[i].contains("nombre"))
			frase += "Nombre: " + clientesJson[i]["nombre"].get<std::string>() + "\n";
		if (clientesJson[i].contains("apellido"))
			frase += "Apellido: " + clientesJson[i]["apellido"].get<std::string>() + "\n";
		if (clientesJson[i].contains("dni"))
			frase += "DNI: " + clientesJson[i]["dni"].get<std::string>() + "\n";
		if (clientesJson[i].contains("telefono"))
			frase += "Telefono: " + clientesJson[i]["telefono"].get<std::string>() + "\n";
		if (clientesJson[i].contains("localidad"))
			frase += "Localidad: " + clientesJson[i]["localidad"].get<std::string>() + "\n";
		if (clientesJson[i].contains("fechaNac"))
			frase += "Fecha de nacimiento: " + clientesJson[i]["fechaNac"].get<std::string>() + "\n";
		if (clientesJson[i].contains("categoria"))
			frase += "Categoria: " + clientesJson[i]["categoria"].get<std::string>() + "\n";
		frase += "\n";
	}
	return frase;
}
string leerCadenaNoVacia(const string& mensaje) {
	string entrada;
	while (true) {
		cout << mensaje;
		getline(cin, entrada);
		if (!entrada.empty()) {
			break;
		}
		cout << "El campo no puede estar vacío. Intente nuevamente: ";
	}
	return entrada;
}
string leerNombreApellido(const string& mensaje) {
	string entrada;
	regex regexNombreApellido("^[A-Za-z]{2,}$"); 
	while (true) {
		cout << mensaje;
		getline(cin, entrada);
		if (!entrada.empty()){
			entrada[0] = toupper(entrada[0]);
			if (regex_match(entrada, regexNombreApellido)) {
				break;
			}
		}	
		cout << "Entrada inválida. Debe tener al menos 2 caracteres, solo letras, sin tildes ni ñ. Intente nuevamente: ";
	}
	return entrada;
}
string leerDni(const string& mensaje) {
	string entrada;
	regex dniRegex("^[0-9]{8}[A-HJ-NP-TV-Z]$");
	while (true) {
		entrada = leerCadenaNoVacia(mensaje);
		if (!entrada.empty() && entrada.length() == 9) {
			entrada[8] = toupper(entrada[8]); 
		}
		if (regex_match(entrada, dniRegex)) {
			break;
		}
		cout << "El DNI debe tener 8 números y luego una última. Intente nuevamente: ";
	}
	return entrada;
}
string leerFechaNac(const string& mensaje) {
	string entrada; 
	regex FechaNacRegex("^([0-2][0-9]|3[0-1])/(0[1-9]|1[0-2])/([0-9]{4})$");
	while (true) {
		entrada = leerCadenaNoVacia(mensaje);
		if (regex_match(entrada, FechaNacRegex)) {
			break;
		}
		cout << "La fecha tiene que estar en el formato dd/mm/yyyy. Intente nuevamente: ";
	}
	return entrada;
}
string leerTlf(const string& mensaje) {
	string entrada;
	regex tlfRegex("^[0-9]{9}$");
	while (true) {
		entrada = leerCadenaNoVacia(mensaje);
		if (regex_match(entrada, tlfRegex)) {
			break;
		}
		cout << "El telefono debe tener 9 números. Intente nuevamente: ";
	}
	return entrada;
}