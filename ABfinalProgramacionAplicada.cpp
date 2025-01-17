#include "ABfinalProgramacionAplicada.h"

int main()
{
	Cliente::cargarId();
	Empleado::cargarId();
	Cita::cargarIdCita();
	int num;
	do {
		cout << "Seleccione una opción" << endl;
		cout << "1 Pacientes" << endl;
		cout << "2 Empleados" << endl;
		cout << "3 Citas" << endl;
		cout << "0. Salir" << endl;
		while (!(cin >> num)) {
			cout << "Entrada no válida. Por favor, ingrese un número." << endl;
			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		}
		switch (num)
		{
		case 1:
			menuPacientes();
			break;
		case 2:
			menuEmpleados();
			break;
		case 3:
			menuCitas();
			break;
		case 0:
			cout << "¡Adiós!." << endl;
			break;
		default:
			cout << "Opción no válida" << endl;
			break;
		}
	} while (num != 0);
	return 0;
}
