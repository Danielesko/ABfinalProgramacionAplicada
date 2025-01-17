#include "ABfinalProgramacionAplicada.h"
int Cita::idAnterior = 1;
void crearCita() {
	string dniPaciente = leerDni("Ingrese el DNI del paciente: ");
	string dniEmpleado = leerDni("Ingrese el DNI del empleado: ");
	string hora = leerHora("Ingrese la hora de la cita: ");
	string fecha = leerFechaNac("Ingrese la fecha de la cita: ");
	string motivo = leerCadenaNoVacia("Ingrese el motivo de la cita: ");
	Cliente c = buscarPacienteDni(dniPaciente);
	Empleado e = buscarEmpleadoDni(dniEmpleado);

}