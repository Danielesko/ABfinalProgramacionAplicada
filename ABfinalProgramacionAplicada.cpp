// ABfinalProgramacionAplicada.cpp: define el punto de entrada de la aplicación.
//

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
		cin >> num;
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
