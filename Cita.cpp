#include "ABfinalProgramacionAplicada.h"
int Cita::idAnteriorCita = 1;
vector<vector<string>> buscarCitas(string dniEmpleado) {
	ifstream archivo;
	json datos;
	archivo.open("citas.json");
	vector<vector<string>> citas;
	if (archivo.is_open()) {
		try {
			archivo >> datos;
		}
		catch (const json::parse_error& e) {
			cerr << "Error al leer el archivo JSON: " << e.what() << endl;
			archivo.close();
			return citas;
		}
		if (datos.is_array()) {
			for (int i = 0; i < datos.size(); i++) {
				vector<string> cita;
				if (datos[i].contains("fecha") && datos[i].contains("hora")) {
					cita.push_back(datos[i]["fecha"].get<std::string>());
					cita.push_back(datos[i]["hora"].get<std::string>());
					citas.push_back(cita);
				}
				
			}
		}
		archivo.close();
	}
	return citas;
}
bool coincidirCitas(string hora, string fecha, vector<vector<string>> citas) {
	for (const auto& cita : citas) {
		if (cita[0] == fecha && cita[1] == hora) {
			return true; 
		}
	}
	return false; 
}
void escribirCita(json cita) {
	json citasExistentes;
	ifstream archivoLeer("citas.json", ios::in | ios::binary);
	if (archivoLeer.is_open() && archivoLeer.peek() != ifstream::traits_type::eof()) {
		archivoLeer >> citasExistentes;
		if (!citasExistentes.is_array()) {
			citasExistentes = json::array();
		}
		archivoLeer.close();
	}else {
		citasExistentes = json::array();
	}
	citasExistentes.push_back(cita);
	ofstream archivoEscribir("citas.json", ios::out | ios::binary);
	if (archivoEscribir.is_open()) {
		archivoEscribir << citasExistentes.dump(4);
		archivoEscribir.close();
		cout << "Cita guardada correctamente." << endl;
	}else {
		cout << "No se pudo abrir el archivo para guardar." << endl;
	}
	Cita::guardarIdCita();
}
void crearCita() {
	string dniPaciente = leerDni("Ingrese el DNI del paciente: ");
	string dniEmpleado = leerDni("Ingrese el DNI del empleado: ");
	string hora = leerHora("Ingrese la hora de la cita: ");
	string fecha = leerFechaNac("Ingrese la fecha de la cita: ");
	string motivo = leerCadenaNoVacia("Ingrese el motivo de la cita: ");
	Cliente c = buscarPacienteDni(dniPaciente);
	Empleado e = buscarEmpleadoDni(dniEmpleado);
	if (c.getId() != 0 && e.getId() != 0) {
		vector<vector<string>> citas = buscarCitas(dniEmpleado);
		bool coincide = coincidirCitas(hora, fecha, citas);
		if (coincide) {
			cout << "El empleado ya tiene una cita a esa hora y fecha." << endl;
			return;
		}else {
			Cita cita = Cita(hora, fecha, e.getId(), c.getId(), motivo);
			escribirCita(cita.to_json());
		}
	}
}
void mostrarCitas() {
	ifstream archivo;
	json datos;
	archivo.open("citas.json");
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
			cout << "No hay citas registradas." << endl;
		}
		else if (datos.is_array()) {
			string citas = jsonToString(datos);
			cout << citas;
		}
	}
	else {
		cout << "No se pudo abrir el archivo para leer." << endl;
	}
}
void buscarCitasPaciente(string dni) {
	Cliente c = buscarPacienteDni(dni);
	ifstream archivo("citas.json");
	json citas;
	if (archivo.is_open()) {
		archivo >> citas;
		archivo.close();
		int contador = 0;
		for (int i = 0; i < citas.size(); i++) {
			if (citas[i].contains("idCliente") && citas[i]["idCliente"] == c.getId()) {
				contador++;
                cout << "Fecha: " << citas[i]["fecha"].get<std::string>() << " Hora: " << citas[i]["hora"].get<std::string>() << " Motivo: " << citas[i]["motivo"].get<std::string>() << " ID Empleado: " << citas[i]["idEmpleado"].get<int>() << endl;
                }
		}
		if (contador == 0) {
			cout << "No se encontraron citas para el paciente." << endl;
		}
	}
}
void buscarCitaEmpleado(string dni) {
	Empleado e = buscarEmpleadoDni(dni);
	ifstream archivo("citas.json");
	json citas;
	if (archivo.is_open()) {
		archivo >> citas;
		archivo.close();
		int contador = 0;
		for (int i = 0; i < citas.size(); i++) {
			if (citas[i].contains("idEmpleado") && citas[i]["idEmpleado"] == e.getId()) {
				contador++;
                cout << "Fecha: " << citas[i]["fecha"].get<std::string>() << " Hora: " << citas[i]["hora"].get<std::string>() << " Motivo: " << citas[i]["motivo"].get<std::string>() << " ID Paciente: " << citas[i]["idCliente"].get<int>() << endl;
                }
		}
		if (contador == 0) {
			cout << "No se encontraron citas para el empleado." << endl;
		}
	}
}
void eliminarCita(string dni) {
	Cliente c = buscarPacienteDni(dni);
	if (c.getId() < 0) {
		cout << "El paciente no existe, no se puede modificar." << endl;
		return;
	}
	ifstream archivo("citas.json");
	json citas;
	if (archivo.is_open()) {
		archivo >> citas;
		archivo.close();
		int contador = 0;
		for (int i = 0; i < citas.size(); i++) {
			if (citas[i].contains("idCliente") && citas[i]["idCliente"] == c.getId()) {
				contador++;
				cout << "ID: " << citas[i]["id"].get<int>() << " Fecha: " << citas[i]["fecha"].get<std::string>() << " Hora: " << citas[i]["hora"].get<std::string>() << " Motivo: " << citas[i]["motivo"].get<std::string>() << endl;
			}
		}
		if (contador == 0) {
			cout << "No se encontraron citas para el paciente." << endl;
			return;
		}
	}else {
		cout << "No se pudo abrir el archivo para leer." << endl;
		return;
	}
	int idEliminar;
	cout << "¿Qué cita desea eliminar? Añade su ID: ";
	cin >> idEliminar;
	ifstream archivoLectura("citas.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de citas." << endl;
		return;
	}
	json citasActualizadas;
	archivoLectura >> citas;
	archivoLectura.close();
	for (int i = 0; i < citas.size(); i++) {
		if (citas[i].contains("id") && citas[i]["id"] != idEliminar) {
			citasActualizadas.push_back(citas[i]);
		}
	}
	ofstream archivoEscribir("citas.json");
	if (!archivoEscribir.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de citas." << endl;
		return;
	}else {
		archivoEscribir << citasActualizadas.dump(4);
		archivoEscribir.close();
		cout << "Cita eliminada exitosamente." << endl;
	}
}
void modificarCitaFecha(string dni) {
	Cliente c = buscarPacienteDni(dni);
	if (c.getId() < 0) {
		cout << "El paciente no existe, no se puede modificar." << endl;
		return;
	}
	ifstream archivo("citas.json");
	json citas;
	if (archivo.is_open()) {
		archivo >> citas;
		archivo.close();
		int contador = 0;
		for (int i = 0; i < citas.size(); i++) {
			if (citas[i].contains("idCliente") && citas[i]["idCliente"] == c.getId()) {
				contador++;
				cout << "ID: " << citas[i]["id"].get<int>() << " Fecha: " << citas[i]["fecha"].get<std::string>() << " Hora: " << citas[i]["hora"].get<std::string>() << " Motivo: " << citas[i]["motivo"].get<std::string>() << endl;
			}
		}
		if (contador == 0) {
			cout << "No se encontraron citas para el paciente." << endl;
			return;
		}
	}else {
		cout << "No se pudo abrir el archivo para leer." << endl;
		return;
	}
	int idModificar;
	cout << "¿Qué cita desea modificar? Añade su ID: ";
	cin >> idModificar;
	string nuevaFecha;
	do {
		cout << "Ingrese la nueva fecha de la cita: ";
		cin.ignore();  
		getline(cin, nuevaFecha);
		if (nuevaFecha.empty()) {
			cout << "La fecha no puede estar vacía. Por favor ingrese una fecha válida." << endl;
		}
	} while (nuevaFecha.empty());  
	ifstream archivoLectura("citas.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de citas." << endl;
		return;
	}
	json citasActualizadas;
	archivoLectura >> citas;
	archivoLectura.close();
	for (int i = 0; i < citas.size(); i++) {
		if (citas[i].contains("id") && citas[i]["id"] == idModificar) {
			citas[i]["fecha"] = nuevaFecha;
		}
		citasActualizadas.push_back(citas[i]);
	}
	ofstream archivoEscritura("citas.json");
	if (archivoEscritura.is_open()) {
		archivoEscritura << citasActualizadas.dump(4); 
		archivoEscritura.close();
		cout << "La cita ha sido modificada exitosamente." << endl;
	}else {
		cerr << "No se pudo abrir el archivo para guardar los cambios." << endl;
	}
}
void modificarCitaHora(string dni) {
	Cliente c = buscarPacienteDni(dni);
	if (c.getId() < 0) {
		cout << "El paciente no existe, no se puede modificar." << endl;
		return;
	}
	ifstream archivo("citas.json");
	json citas;
	if (archivo.is_open()) {
		archivo >> citas;
		archivo.close();
		int contador = 0;
		for (int i = 0; i < citas.size(); i++) {
			if (citas[i].contains("idCliente") && citas[i]["idCliente"] == c.getId()) {
				contador++;
				cout << "ID: " << citas[i]["id"].get<int>() << " Fecha: " << citas[i]["fecha"].get<std::string>() << " Hora: " << citas[i]["hora"].get<std::string>() << " Motivo: " << citas[i]["motivo"].get<std::string>() << endl;
			}
		}
		if (contador == 0) {
			cout << "No se encontraron citas para el paciente." << endl;
			return;
		}
	}else {
		cout << "No se pudo abrir el archivo para leer." << endl;
		return;
	}
	int idModificar;
	cout << "¿Qué cita desea modificar? Añade su ID: ";
	cin >> idModificar;
	string nuevaHora;
	do {
		cout << "Ingrese la nueva hora de la cita: ";
		cin.ignore();
		getline(cin, nuevaHora);
		if (nuevaHora.empty()) {
			cout << "La hora no puede estar vacía. Por favor ingrese una hora válida." << endl;
		}
	} while (nuevaHora.empty());
	ifstream archivoLectura("citas.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de citas." << endl;
		return;
	}
	json citasActualizadas;
	archivoLectura >> citas;
	archivoLectura.close();
	for (int i = 0; i < citas.size(); i++) {
		if (citas[i].contains("id") && citas[i]["id"] == idModificar) {
			citas[i]["hora"] = nuevaHora;
		}
		citasActualizadas.push_back(citas[i]);
	}
	ofstream archivoEscritura("citas.json");
	if (archivoEscritura.is_open()) {
		archivoEscritura << citasActualizadas.dump(4);
		archivoEscritura.close();
		cout << "La cita ha sido modificada exitosamente." << endl;
	}else {
		cerr << "No se pudo abrir el archivo para guardar los cambios." << endl;
	}
}
void modificarCitaMotivo(string dni) {
	Cliente c = buscarPacienteDni(dni);
	if (c.getId() < 0) {
		cout << "El paciente no existe, no se puede modificar." << endl;
		return;
	}
	ifstream archivo("citas.json");
	json citas;
	if (archivo.is_open()) {
		archivo >> citas;
		archivo.close();
		int contador = 0;
		for (int i = 0; i < citas.size(); i++) {
			if (citas[i].contains("idCliente") && citas[i]["idCliente"] == c.getId()) {
				contador++;
				cout << "ID: " << citas[i]["id"].get<int>() << " Fecha: " << citas[i]["fecha"].get<std::string>() << " Hora: " << citas[i]["hora"].get<std::string>() << " Motivo: " << citas[i]["motivo"].get<std::string>() << endl;
			}
		}
		if (contador == 0) {
			cout << "No se encontraron citas para el paciente." << endl;
			return;
		}
	}else {
		cout << "No se pudo abrir el archivo para leer." << endl;
		return;
	}
	int idModificar;
	cout << "¿Qué cita desea modificar? Añade su ID: ";
	cin >> idModificar;
	string nuevoMotivo;
	do {
		cout << "Ingrese el nuevo motivo de la cita: ";
		cin.ignore();
		getline(cin, nuevoMotivo);
		if (nuevoMotivo.empty()) {
			cout << "El motivo no puede estar vacío. Por favor ingrese un motivo válido." << endl;
		}
	} while (nuevoMotivo.empty());
	ifstream archivoLectura("citas.json");
	if (!archivoLectura.is_open()) {
		cerr << "Error: No se pudo abrir el archivo de citas." << endl;
		return;
	}
	json citasActualizadas;
	archivoLectura >> citas;
	archivoLectura.close();
	for (int i = 0; i < citas.size(); i++) {
		if (citas[i].contains("id") && citas[i]["id"] == idModificar) {
			citas[i]["motivo"] = nuevoMotivo;
		}
		citasActualizadas.push_back(citas[i]);
	}
	ofstream archivoEscritura("citas.json");
	if (archivoEscritura.is_open()) {
		archivoEscritura << citasActualizadas.dump(4);
		archivoEscritura.close();
		cout << "La cita ha sido modificada exitosamente." << endl;
	}else {
		cerr << "No se pudo abrir el archivo para guardar los cambios." << endl;
	}
}
void menuModificarCita() {
	cout << "1.Modificar fecha" << endl;
	cout << "2.Modificar hora" << endl;
	cout << "3.Modificar motivo" << endl;
	cout << "0. Salir" << endl;
	int num = leerOpcion();
	string dni;
	dni = leerDni("Ingrese el dni del paciente para modificar: ");
	switch (num) {
	case 1:
		modificarCitaFecha(dni);
		break;
	case 2:
		modificarCitaHora(dni);
		break;
	case 3:
		modificarCitaMotivo(dni);
		break;
	case 0:
		cout << "Saliendo del menú de modificación de citas..." << endl;
		break;
	default:
		cout << "Opción no válida. Intente nuevamente." << endl;
		break;
	}
}
