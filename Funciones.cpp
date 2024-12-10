#include "ABfinalProgramacionAplicada.h"

void menuPacientes() {
	int num;
	do() {
		cout << "1. Ingresar un nuevo cliente" << endl;
		cout << "2. Mostrar todos los clientes" << endl;
		cout << "3. Buscar un cliente" << endl;
		cout << "4. Modificar un cliente" << endl;
		cout << "5. Eliminar un cliente" << endl;
		cout << "0. Salir" << endl;
		cin >> num;
		switch (num) {
		case 1:
			crearCliente();
			break;
		case 2:
			//mostrarClientes();
			break;
		case 3:
			//buscarCliente();
			break;	
		case 4:
			//modificarCliente();
			break;
		case 5:
			//eliminarCliente();
			break;
		case 0:
			cout << "Saliendo." << endl;
			break;
		default:
			cout << "Opción no válida" << endl;
			break;
	}while (num != 0);
}
void menuEmpleados() {
}
void menuQuejas() {
}
void menuCitas() {
}
