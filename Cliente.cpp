#include "ABfinalProgramacionAplicada.h"
#include "Persona.h"
#include "Funciones.h"
int Cliente::idAnterior = 1;

void escribirClienteArchivo(json cliente) {
    json clientesExistentes;
    ifstream archivoLeer("clientes.json", ios::in | ios::binary);
    if (archivoLeer.is_open() && archivoLeer.peek() != ifstream::traits_type::eof()) {
        archivoLeer >> clientesExistentes;
        if (!clientesExistentes.is_array()) {
            clientesExistentes = json::array();
        }
        archivoLeer.close();
    }
    else {
        clientesExistentes = json::array();
    }
    clientesExistentes.push_back(cliente);

    ofstream archivoEscribir("clientes.json", ios::out | ios::binary);
    if (archivoEscribir.is_open()) {
        archivoEscribir << clientesExistentes.dump(4);
        archivoEscribir.close();
        cout << "Cliente guardado correctamente." << endl;
    }
    else {
        cout << "No se pudo abrir el archivo para guardar." << endl;
    }
    Cliente::guardarId();
}

void crearCliente() {
    string nombre = leerNombreApellido("Ingrese el nombre del cliente: ");
    string apellido = leerNombreApellido("Ingrese el apellido del cliente: ");
    string dni = leerDni("Ingrese el DNI del cliente: ");
    string tlf = leerTlf("Ingrese el tel�fono del cliente: ");
    string fechaNac = leerFechaNac("Ingrese la fecha de nacimiento del cliente: ");
    string historial = leerHistorial("Ingrese el historial del cliente: ");
    Cliente cliente = Cliente(nombre, apellido, dni, tlf, fechaNac, historial);
    escribirClienteArchivo(cliente.to_json());
}

void mostrarPacientes() {
    ifstream archivo;
    json datos;
    archivo.open("clientes.json");
    if (archivo.is_open()) {
        try {
            archivo >> datos;
        }
        catch (const json::parse_error& e) {
            cerr << "Error al leer el archivo JSON: " << e.what() << endl;
            archivo.close();
            return;
        }
        if (datos.size() == 0) {
            cout << "No hay pacientes registrados." << endl;
        }
        else if (datos.is_array()) {
            string pacientes = jsonToString(datos);
            cout << pacientes;
        }
    }
    else {
        cout << "No se pudo abrir el archivo para leer." << endl;
    }
}

void buscarPaciente(string nombre) {
    ifstream archivo("clientes.json", ios::in | ios::binary);
    int contador = 0;
    if (archivo.is_open()) {
        json pacientes;
        json pacientesFinal;
        archivo >> pacientes;
        for (int i = 0; i < pacientes.size(); i++) {
            if (pacientes[i].contains("nombre") && pacientes[i]["nombre"] == nombre) {
                pacientesFinal.push_back(pacientes[i]);
                contador++;
            }
        }
        if (contador == 0) {
            cout << "No se encontr� ning�n paciente con ese nombre." << endl;
        }
        else {
            string paciente = jsonToString(pacientesFinal);
            cout << paciente;
        }
    }
}

Cliente buscarPacienteDni(string dni) {
    Cliente c = Cliente();

    ifstream archivo("clientes.json");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
        return c;
    }

    json pacientes;
    try {
        archivo >> pacientes;
    }
    catch (const std::exception& e) {
        cerr << "Error al procesar el archivo JSON: " << e.what() << endl;
        return c;
    }
    archivo.close();

    for (const auto& paciente : pacientes) {
        if (paciente.contains("dni") && paciente["dni"] == dni) {
            return Cliente(
                paciente["id"].get<int>(),
                paciente["nombre"],
                paciente["apellido"],
                paciente["dni"],
                paciente["telefono"],
                paciente["fechaNac"],
                paciente["historial"]
            );
        }
    }

    cout << "No se encontr� ning�n paciente con ese DNI." << endl;
    return c;
}

void menuModificarPaciente() {
    cout << "1.Modificar dni" << endl;
    cout << "2.Modificar nombre" << endl;
    cout << "3.Modificar apellido" << endl;
    cout << "4.Modificar telefono" << endl;
    cout << "5.Modificar fecha de nacimiento" << endl;
    cout << "6.Modificar historial" << endl;
    cout << "0.Salir" << endl;
    int num = leerOpcion();
    string dni;
    dni = leerDni("Ingrese el dni del paciente para modificar: ");
    switch (num) {
    case 1:
        modificarPacienteDni(dni);
        break;
    case 2:
        mofificarPacienteNombre(dni);
        break;
    case 3:
        modificarPacienteApellido(dni);
        break;
    case 4:
        modificarPacienteTlf(dni);
        break;
    case 5:
        mofificarPacienteFechaNac(dni);
        break;
    case 6:
        modificarPacienteHistorial(dni);
        break;
    case 0:
        cout << "Saliendo del sistema de gesti�n de modificacion de pacientes..." << endl;
        break;
    default:
        cout << "Opci�n no v�lida. Intente nuevamente." << endl;
        break;
    }
}

void modificarPacienteHistorial(string dni) {
    Cliente c = buscarPacienteDni(dni);
    if (c.getId() < 0) {
        cout << "El paciente no existe, no se puede modificar." << endl;
        return;
    }
    else {
        cout << "Paciente encontrado. Ingrese los nuevos datos." << endl;
    }

    string historialNuevo = leerHistorial("Ingrese el nuevo historial: ");
    ifstream archivoLectura("clientes.json");
    if (!archivoLectura.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
        return;
    }

    json pacientes;
    archivoLectura >> pacientes;
    archivoLectura.close();
    bool encontrado = false;
    for (auto& paciente : pacientes) {
        if (paciente.contains("dni") && paciente["dni"] == dni) {
            if (paciente.contains("historial")) {
                paciente["historial"] = paciente["historial"].get<std::string>() + "\n" + historialNuevo;
            }
            else {
                paciente["historial"] = historialNuevo;
            }
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout << "El paciente no fue encontrado en el archivo JSON." << endl;
        return;
    }
    ofstream archivoEscritura("clientes.json");
    if (!archivoEscritura.is_open()) {
        cerr << "Error: No se pudo escribir en el archivo de clientes." << endl;
        return;
    }
    archivoEscritura << pacientes.dump(4); 
    archivoEscritura.close();
    cout << "Historial del paciente modificado exitosamente." << endl;
}



void mofificarPacienteFechaNac(string dni) {
    Cliente c = buscarPacienteDni(dni);
    if (c.getId() == 0) {
        cout << "El paciente no existe, no se puede modificar." << endl;
        return;
    }
    else {
        cout << "Paciente encontrado. Ingrese los nuevos datos." << endl;
    }
    string fechaNueva = leerFechaNac("Ingrese la nueva fecha de nacimiento: ");
    Cliente clienteActualizado(
        c.getNombre(),
        c.getApellido(),
        c.getDni(),
        c.getTlf(),
        fechaNueva,
        c.getHistorial()
    );
    ifstream archivoLectura("clientes.json");
    if (!archivoLectura.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
        return;
    }
    json pacientes;
    archivoLectura >> pacientes;
    archivoLectura.close();
    for (auto& paciente : pacientes) {
        if (paciente.contains("dni") && paciente["dni"] == dni) {
            paciente = clienteActualizado.to_json();
            break;
        }
    }
    ofstream archivoEscritura("clientes.json");
    if (!archivoEscritura.is_open()) {
        cerr << "Error: No se pudo escribir en el archivo de clientes." << endl;
        return;
    }
    archivoEscritura << pacientes.dump(4);
    archivoEscritura.close();
    cout << "Paciente modificado exitosamente." << endl;
}

void modificarPacienteTlf(string dni) {
    Cliente c = buscarPacienteDni(dni);
    if (c.getId() == 0) {
        cout << "El paciente no existe, no se puede modificar." << endl;
        return;
    }
    else {
        cout << "Paciente encontrado. Ingrese los nuevos datos." << endl;
    }
    string tlfNuevo = leerTlf("Ingrese el nuevo telefono: ");

    Cliente clienteActualizado(
        c.getNombre(),
        c.getApellido(),
        c.getDni(),
        tlfNuevo,
        c.getFechaNac(),
        c.getHistorial()
    );
    ifstream archivoLectura("clientes.json");
    if (!archivoLectura.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
        return;
    }
    json pacientes;
    archivoLectura >> pacientes;
    archivoLectura.close();
    for (auto& paciente : pacientes) {
        if (paciente.contains("dni") && paciente["dni"] == dni) {
            paciente = clienteActualizado.to_json();
            break;
        }
    }

    ofstream archivoEscritura("clientes.json");
    if (!archivoEscritura.is_open()) {
        cerr << "Error: No se pudo escribir en el archivo de clientes." << endl;
        return;
    }

    archivoEscritura << pacientes.dump(4);
    archivoEscritura.close();

    cout << "Paciente modificado exitosamente." << endl;
}

void modificarPacienteApellido(string dni) {
    Cliente c = buscarPacienteDni(dni);
    if (c.getId() == 0) {
        cout << "El paciente no existe, no se puede modificar." << endl;
        return;
    }
    else {
        cout << "Paciente encontrado. Ingrese los nuevos datos." << endl;
    }
    string apellidoNuevo = leerNombreApellido("Ingrese el nuevo apellido: ");

    Cliente clienteActualizado(
        c.getNombre(),
        apellidoNuevo,
        c.getDni(),
        c.getTlf(),
        c.getFechaNac(),
        c.getHistorial()
    );
    ifstream archivoLectura("clientes.json");
    if (!archivoLectura.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
        return;
    }
    json pacientes;
    archivoLectura >> pacientes;
    archivoLectura.close();
    for (auto& paciente : pacientes) {
        if (paciente.contains("dni") && paciente["dni"] == dni) {
            paciente = clienteActualizado.to_json();
            break;
        }
    }

    ofstream archivoEscritura("clientes.json");
    if (!archivoEscritura.is_open()) {
        cerr << "Error: No se pudo escribir en el archivo de clientes." << endl;
        return;
    }

    archivoEscritura << pacientes.dump(4);
    archivoEscritura.close();

    cout << "Paciente modificado exitosamente." << endl;
}

void mofificarPacienteNombre(string dni) {
    Cliente c = buscarPacienteDni(dni);
    if (c.getId() == 0) {
        cout << "El paciente no existe, no se puede modificar." << endl;
        return;
    }
    else {
        cout << "Paciente encontrado. Ingrese los nuevos datos." << endl;
    }
    string nombreNuevo = leerNombreApellido("Ingrese el nuevo nombre: ");

    Cliente clienteActualizado(
        nombreNuevo,
        c.getApellido(),
        c.getDni(),
        c.getTlf(),
        c.getFechaNac(),
        c.getHistorial()
    );
    ifstream archivoLectura("clientes.json");
    if (!archivoLectura.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
        return;
    }
    json pacientes;
    archivoLectura >> pacientes;
    archivoLectura.close();
    for (auto& paciente : pacientes) {
        if (paciente.contains("dni") && paciente["dni"] == dni) {
            paciente = clienteActualizado.to_json();
            break;
        }
    }

    ofstream archivoEscritura("clientes.json");
    if (!archivoEscritura.is_open()) {
        cerr << "Error: No se pudo escribir en el archivo de clientes." << endl;
        return;
    }

    archivoEscritura << pacientes.dump(4);
    archivoEscritura.close();

    cout << "Paciente modificado exitosamente." << endl;
}

void modificarPacienteDni(string dni) {
    Cliente c = buscarPacienteDni(dni);
    if (c.getId() == 0) {
        cout << "El paciente no existe, no se puede modificar." << endl;
        return;
    }
    else {
        cout << "Paciente encontrado. Ingrese los nuevos datos." << endl;
    }
    string dniNuevo = leerDni("Ingrese el nuevo dni: ");

    Cliente clienteActualizado(
        c.getNombre(),
        c.getApellido(),
        dniNuevo,
        c.getTlf(),
        c.getFechaNac(),
        c.getHistorial()
    );
    ifstream archivoLectura("clientes.json");
    if (!archivoLectura.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
        return;
    }
    json pacientes;
    archivoLectura >> pacientes;
    archivoLectura.close();
    for (auto& paciente : pacientes) {
        if (paciente.contains("dni") && paciente["dni"] == dni) {
            paciente = clienteActualizado.to_json();
            break;
        }
    }

    ofstream archivoEscritura("clientes.json");
    if (!archivoEscritura.is_open()) {
        cerr << "Error: No se pudo escribir en el archivo de clientes." << endl;
        return;
    }

    archivoEscritura << pacientes.dump(4);
    archivoEscritura.close();

    cout << "Paciente modificado exitosamente." << endl;
}

void eliminarPaciente(string dni) {
    Cliente c = buscarPacienteDni(dni);
    if (c.getId() < 0) {
        cout << "El paciente no existe, no se puede modificar." << endl;
        return;
    }
    ifstream archivoLectura("clientes.json");
    if (!archivoLectura.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
        return;
    }
    json pacientes;
    archivoLectura >> pacientes;
    archivoLectura.close();
    json pacientesActualizados;
    for (int i = 0; i < pacientes.size(); i++) {
        if (pacientes[i].contains("dni") && pacientes[i]["dni"] != dni) {
            pacientesActualizados.push_back(pacientes[i]);
        }
    }
    ofstream archivo("clientes.json");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
        return;
    }
    else {
        archivo << pacientesActualizados.dump(4);
        archivo.close();
        cout << "Paciente eliminado exitosamente." << endl;
    }
}
void mostrarHistorialPaciente(string dni) {
	Cliente c = buscarPacienteDni(dni);
	if (c.getId() < 0) {
		cout << "El paciente no existe, no se puede mostrar el historial." << endl;
		return;
	}
	ifstream archivo("clientes.json");
	json pacientes;
	if (archivo.is_open()) {
		archivo >> pacientes;
		archivo.close();
		int contador = 0;
		for (int i = 0; i < pacientes.size(); i++) {
			if (pacientes[i].contains("dni") && pacientes[i]["dni"] == dni) {
				contador++;
				cout << "Historial: " << pacientes[i]["historial"].get<std::string>() << endl;
			}
		}
		if (contador == 0) {
			cout << "No se encontr� historial para el paciente." << endl;
		}
	}
}





