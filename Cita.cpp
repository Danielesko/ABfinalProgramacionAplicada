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
	bool coindide = false;

}
void crearCita() {
	string dniPaciente = leerDni("Ingrese el DNI del paciente: ");
	string dniEmpleado = leerDni("Ingrese el DNI del empleado: ");
	string hora = leerHora("Ingrese la hora de la cita: ");
	string fecha = leerFechaNac("Ingrese la fecha de la cita: ");
	string motivo = leerCadenaNoVacia("Ingrese el motivo de la cita: ");
	Cliente c = buscarPacienteDni(dniPaciente);
	Empleado e = buscarEmpleadoDni(dniEmpleado);
	vector <vector<string>> citas = buscarCitas(dniEmpleado);
	bool sePuede = coincidirCitas(hora,fecha,citas);


}