#include "ABfinalProgramacionAplicada.h"
int Cita::idAnterior = 1;
vector<string> buscarCitas(string dniEmpleado) {
	ifstream archivo;
	json datos;
	archivo.open("citas.json");
	vector<string> citas;
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

					string cita = "Hora: " + datos[i]["hora"].get<std::string>() + "\n";
					cita += "Fecha: " + datos[i]["fecha"].get<std::string>() + "\n";
					citas.push_back(cita);
				}
			}
		}
	}
	else {
		cout << "No se pudo abrir el archivo para leer." << endl;
	}
}
bool coincidirCitas(string hora,string fecha,string dniEmpleado) {
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
	bool sePuede = coincidirCitas(hora,fecha,dniEmpleado);


}