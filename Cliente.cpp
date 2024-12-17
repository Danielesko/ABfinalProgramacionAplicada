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
		try {
			archivo >> datos; 
		}
		catch (const json::parse_error& e) {
			cerr << "Error al leer el archivo JSON: " << e.what() << endl;
			archivo.close();
			return;
		}
		if (datos.size() == 0) {
			cout << "No hay pacientes registrados." << endl;
		}
		else if (datos.is_array()) {
			string pacientes = jsonToString(datos);
			cout << pacientes;
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
		json pacientesFinal;
		archivo >> pacientes;
		for (int i = 0; i < pacientes.size(); i++) {
			if (pacientes[i].contains("nombre") && pacientes[i]["nombre"] == nombre) {
				pacientesFinal.push_back(pacientes[i]);
				contador++;
			}
		}
		if (contador == 0) {
			cout << "No se encontró ningún paciente con ese nombre." << endl;
		}else {
			string paciente = jsonToString(pacientesFinal);
			cout << paciente;
		}
	}
}
Cliente buscarPacienteDni(string dni) {
	Cliente c = Cliente();

	ifstream archivo("clientes.json");
	if (!archivo.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
		return c;
	}

	json pacientes;
	try {
		archivo >> pacientes;
	}
	catch (const std::exception& e) {
		cerr << "Error al procesar el archivo JSON: " << e.what() << endl;
		return c;
	}
	archivo.close();

	for (const auto& paciente : pacientes) {
		if (paciente.contains("dni") && paciente["dni"] == dni) {
			return Cliente(
				paciente["id"],
				paciente["nombre"],
				paciente["apellido"],
				paciente["dni"],
				paciente["telefono"],
				paciente["fechaNac"],
				paciente["localidad"]
			);
		}
	}

	cout << "No se encontró ningún paciente con ese DNI." << endl;
	return c; 
}
void menuModificarPaciente() {
	cout << "1.Modificar dni" << endl;
	cout << "2.Modificar nombre" << endl;
	cout << "3.Modificar apellido" << endl;
	cout << "4.Modificar telefono" << endl;
	cout << "5.Modificar fecha de nacimiento" << endl;
	cout << "6.Modificar localidad" << endl;
	cout << "0.Salir" << endl;
	int num = leerOpcion();
	string dni;
	switch (num) {
	case 1:
		dni = leerCadenaNoVacia("Ingrese el dni del paciente para modificar: ");
		modificarPacienteDni(dni);
		break;
	case 2:
		dni = leerCadenaNoVacia("Ingrese el dni del paciente para modificar: ");
		mofificarPacienteNombre(dni);
		break;
	case 3:
		dni = leerCadenaNoVacia("Ingrese el dni del paciente para modificar: ");
		modificarPacienteApellido(dni);
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 0:
		cout << "Saliendo del sistema de gestión de modificacion de pacientes..." << endl;
		break;
	default:
		cout << "Opción no válida. Intente nuevamente." << endl;
		break;
	}

}
void modificarPacienteApellido(string dni) {
	Cliente c = buscarPacienteDni(dni);
	if (c.getId() == -1) {
		cout << "El paciente no existe, no se puede modificar." << endl;
		return;
	}
	cout << "Paciente encontrado. Ingrese los nuevos datos." << endl;
	string apellidoNuevo = leerCadenaNoVacia("Ingrese el nuevo apellido: ");

	Cliente clienteActualizado(
		c.getId(),
		c.getNombre(),
		apellidoNuevo,
		c.getDni(),
		c.getTlf(),
		c.getFechaNac(),
		c.getLocalidad()
	);
	ifstream archivoLectura("clientes.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
		return;
	}
	json pacientes;
	archivoLectura >> pacientes;
	archivoLectura.close();
	for (auto& paciente : pacientes) {
		if (paciente.contains("dni") && paciente["dni"] == dni) {
			paciente = clienteActualizado.to_json();
			break;
		}
	}

	ofstream archivoEscritura("clientes.json");
	if (!archivoEscritura.is_open()) {
		cerr << "Error: No se pudo escribir en el archivo de clientes." << endl;
		return;
	}

	archivoEscritura << pacientes.dump(4);
	archivoEscritura.close();

	cout << "Paciente modificado exitosamente." << endl;
}
void mofificarPacienteNombre(string dni) {
	Cliente c = buscarPacienteDni(dni);
	if (c.getId() == -1) {
		cout << "El paciente no existe, no se puede modificar." << endl;
		return;
	}
	cout << "Paciente encontrado. Ingrese los nuevos datos." << endl;
	string nombreNuevo = leerCadenaNoVacia("Ingrese el nuevo nombre: ");

	Cliente clienteActualizado(
		c.getId(),
		nombreNuevo,
		c.getApellido(),
		c.getDni(),
		c.getTlf(),
		c.getFechaNac(),
		c.getLocalidad()
	);
	ifstream archivoLectura("clientes.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
		return;
	}
	json pacientes;
	archivoLectura >> pacientes;
	archivoLectura.close();
	for (auto& paciente : pacientes) {
		if (paciente.contains("dni") && paciente["dni"] == dni) {
			paciente = clienteActualizado.to_json();
			break;
		}
	}

	ofstream archivoEscritura("clientes.json");
	if (!archivoEscritura.is_open()) {
		cerr << "Error: No se pudo escribir en el archivo de clientes." << endl;
		return;
	}

	archivoEscritura << pacientes.dump(4);
	archivoEscritura.close();

	cout << "Paciente modificado exitosamente." << endl;
}
void modificarPacienteDni(string dni) {
	Cliente c = buscarPacienteDni(dni);
	if (c.getId() == -1) {
		cout << "El paciente no existe, no se puede modificar." << endl;
		return;
	}
	cout << "Paciente encontrado. Ingrese los nuevos datos." << endl;
	string dniNuevo = leerCadenaNoVacia("Ingrese el nuevo dni: ");

	Cliente clienteActualizado(
		c.getId(),
		c.getNombre(),
		c.getApellido(),
		dniNuevo,
		c.getTlf(),
		c.getFechaNac(),
		c.getLocalidad()
	);
	ifstream archivoLectura("clientes.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
		return;
	}
	json pacientes;
	archivoLectura >> pacientes;
	archivoLectura.close();
	for (auto& paciente : pacientes) {
		if (paciente.contains("dni") && paciente["dni"] == dni) {
			paciente = clienteActualizado.to_json();
			break;
		}
	}

	ofstream archivoEscritura("clientes.json");
	if (!archivoEscritura.is_open()) {
		cerr << "Error: No se pudo escribir en el archivo de clientes." << endl;
		return;
	}

	archivoEscritura << pacientes.dump(4); 
	archivoEscritura.close();

	cout << "Paciente modificado exitosamente." << endl;
}
void eliminarPaciente(string dni) {
	Cliente c = buscarPacienteDni(dni);
	if (c.getId() == -1) {
		cout << "El paciente no existe, no se puede eliminar." << endl;
		return;
	}
	ifstream archivoLectura("clientes.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
		return;
	}
	json pacientes;
	archivoLectura >> pacientes;
	archivoLectura.close();
	json pacientesActualizados;
	for (int i = 0; i < pacientes.size(); i++) {
		if (pacientes[i].contains("dni") && pacientes[i]["dni"] != dni) {
			pacientesActualizados.push_back(pacientes[i]);
		}
	}
	ofstream archivo("clientes.json");
	if (!archivo.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
		return;
	}
	else {
		archivo << pacientesActualizados.dump(4);
		archivo.close();
		cout << "Paciente eliminado exitosamente." << endl;
	}
}