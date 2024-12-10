// ABfinalProgramacionAplicada.cpp: define el punto de entrada de la aplicación.
//

#include "ABfinalProgramacionAplicada.h"

int main()
{
	cout << "Hello CMake." << endl;
	cout << "Bienvenido a la aplicación" << endl;
	/*do {
		int num;
		cout << "Seleccione una opción" << endl;
		cout << "Clientes" << endl;
		cout << "Empleados" << endl;
		cout << "Quejas" << endl;
		cout << "Citas" << endl;
		cout << "0. Salir" << endl;
		cin >> num;
		cout << "1. Ingresar un nuevo cliente" << endl;
		cout << "2. Mostrar todos los clientes" << endl;
		cout << "3. Buscar un cliente" << endl;
		cout << "4. Modificar un cliente" << endl;
		cout << "5. Eliminar un cliente" << endl;

	} while (num != 0);*/
	Cliente cliente = Cliente();
	cliente.crearCliente();
	return 0;
}
