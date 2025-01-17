#include "ABfinalProgramacionAplicada.h"
int Cita::idAnterior = 1;
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
		if (datos.size() == 0) {
			cout << "No hay citas registradas." << endl;
		}
		else if (datos.is_array()) {
			for (int i = 0; i < datos.size(); i++) {
				if (datos[i].contains("idEmpleado") && datos[i]["idEmpleado"] == dniEmpleado) {
					vector<string> cita;
					cita.push_back(datos[i]["fecha"].get<std::string>());
					cita.push_back(datos[i]["hora"].get<std::string>());
					citas.push_back(cita);

				}
			}
		}
	}
	else {
		cout << "No se pudo abrir el archivo para leer." << endl;
	}
	return citas;
}
bool coincidirCitas(string hora,string fecha, vector<vector<string>> citas) {
	bool coincide = false;
	for (int i = 0; i < citas.size(); i++) {
		if (citas[i][0] == fecha && citas[i][1] == hora) {
			coincide = true;
			break;
		}
	}
	return coincide;
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
	Cita::guardarId();
}
void crearCita() {
	string dniPaciente = leerDni("Ingrese el DNI del paciente: ");
	string dniEmpleado = leerDni("Ingrese el DNI del empleado: ");
	string hora = leerHora("Ingrese la hora de la cita: ");
	string fecha = leerFechaNac("Ingrese la fecha de la cita: ");
	string motivo = leerCadenaNoVacia("Ingrese el motivo de la cita: ");
	Cliente c = buscarPacienteDni(dniPaciente);
	Empleado e = buscarEmpleadoDni(dniEmpleado);
	if (c.getId() != 0 && e.getId() !=0) {
		vector <vector<string>> citas = buscarCitas(dniEmpleado);
		bool sePuede = coincidirCitas(hora, fecha, citas);
		if (sePuede = false) {
			cout << "El empleado ya tiene una cita a esa hora y fecha." << endl;
			return;
		}
		else {
			Cita cita = Cita(0, hora, fecha, e.getId(), c.getId(), motivo);
			escribirCita(cita.to_json());
		}
	}
}