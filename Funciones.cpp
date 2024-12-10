#include "ABfinalProgramacionAplicada.h"

void abrirArchivo(string nombreArchivo) {
	ofstream archivo;
	archivo.open(nombreArchivo);
	if (!archivo.is_open()) {
		cout << "Error al abrir el archivo " << nombreArchivo << endl;
		exit(1);
	}
}
