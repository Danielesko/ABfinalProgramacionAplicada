// ABfinalProgramacionAplicada.cpp: define el punto de entrada de la aplicación.
//

#include "ABfinalProgramacionAplicada.h"

int main()
{
	int num;
	cout << "Hello CMake." << endl;
	cout << "Bienvenido a la aplicación" << endl;
	do {
		cout << "Seleccione una opción" << endl;
		cout << "1 Clientes" << endl;
		cout << "2 Empleados" << endl;
		cout << "3 Quejas" << endl;
		cout << "4 Citas" << endl;
		cout << "0. Salir" << endl;
		cin >> num;
		switch (num)
		{
		case 1:
			crearCliente();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 0:
			break;
		default:
			cout << "Opción no válida" << endl;
			break;
		}
		cout << "1. Ingresar un nuevo cliente" << endl;
		cout << "2. Mostrar todos los clientes" << endl;
		cout << "3. Buscar un cliente" << endl;
		cout << "4. Modificar un cliente" << endl;
		cout << "5. Eliminar un cliente" << endl;

	} while (num != 0);
	crearCliente();
	return 0;
}
