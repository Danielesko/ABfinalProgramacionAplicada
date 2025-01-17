#include "ABfinalProgramacionAplicada.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int leerOpcion() {
    int opcion;
    while (true) {
        cout << "Ingrese una opci�n: ";
        cin >> opcion;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inv�lida. Intente nuevamente." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return opcion;
        }
    }
}

void menuPacientes() {
    int num;
    do {
        cout << "1. Ingresar un nuevo paciente" << endl;
        cout << "2. Mostrar todos los pacientes" << endl;
        cout << "3. Buscar un paciente" << endl;
        cout << "4. Modificar un paciente" << endl;
        cout << "5. Eliminar un paciente" << endl;
		cout << "6. Mostrar historial de un paciente" << endl;
        cout << "0. Salir" << endl;

        num = leerOpcion();
        string dni;
        Cliente paciente = Cliente();
        string nombre;
        switch (num) {
        case 1:
            crearCliente();
            break;
        case 2:
            mostrarPacientes();
            break;
        case 3:
            nombre = leerNombreApellido("Ingrese el nombre del paciente: ");
            buscarPaciente(nombre);
            break;
        case 4:
            menuModificarPaciente();
            break;
        case 5:
            mostrarPacientes();
            dni = leerDni("Ingrese el dni del paciente para eliminar: ");
            eliminarPaciente(dni);
            break;
        case 6:
			dni = leerDni("Ingrese el dni del paciente para mostrar su historial: ");
            mostrarHistorialPaciente(dni);
			break;
        case 0:
            cout << "Saliendo del sistema de gesti�n de pacientes..." << endl;
            break;
        default:
            cout << "Opci�n no v�lida. Intente nuevamente." << endl;
            break;
        }
    } while (num != 0);
}

void menuEmpleados() {
    int num;
    do {
        cout << "1. Ingresar un nuevo empleado" << endl;
        cout << "2. Mostrar todos los empleados" << endl;
        cout << "3. Buscar un empleado" << endl;
        cout << "4. Modificar un empleado" << endl;
        cout << "5. Eliminar un empleado" << endl;
		cout << "6. Mostrar empleados por categoria" << endl;
        cout << "0. Salir" << endl;
        num = leerOpcion();
        string dni;
        Empleado empleado = Empleado();
        string nombre;
        switch (num) {
        case 1:
            crearEmpleado();
            break;
        case 2:
            mostrarEmpleados();
            break;
        case 3:
            nombre = leerNombreApellido("Ingrese el nombre del empleado: ");
            buscarEmpleado(nombre);
            break;
        case 4:
            menuModificarEmpleado();
            break;
        case 5:
            mostrarEmpleados();
            dni = leerDni("Ingrese el dni del empleado para eliminar: ");
            eliminarEmpleado(dni);
            break;
        case 6:
            nombre = leerCategoria("�Por que categoria quieres buscar? medico o enfermero : " );
            mostrarEmpleadosPorCategoria(nombre);
            break;
        case 0:
            cout << "Saliendo del sistema de gesti�n de empleados..." << endl;
            break;
        default:
            cout << "Opci�n no v�lida. Intente nuevamente." << endl;
            break;
        }
    } while (num != 0);
}

void menuCitas() {
    int num;
    do {
        cout << "1. Ingresar una nueva cita" << endl;
        cout << "2. Mostrar todas las citas" << endl;
        cout << "3. Buscar una citas de un paciente" << endl;
        cout << "4. Modificar una cita" << endl;
        cout << "5. Eliminar una cita" << endl;
		cout << "6. Mostrar citas de un empleado" << endl;
		cout << "7. Guardar en un archivo las citas entre dos fechas" << endl;
        cout << "0. Salir" << endl;
        num = leerOpcion();
        string dni;
        string fechaInicio;
        string fechaFin;
        string nombreArchivo;
        Cita cita = Cita();
        switch (num) {
        case 1:
            crearCita();
            break;
        case 2:
            mostrarCitas();
            break;
        case 3:
            dni = leerDni("Ingrese el dni del paciente: ");
            buscarCitasPaciente(dni);
            break;
        case 4:
            menuModificarCita();
            break;
        case 5:
            dni = leerDni("Ingrese el dni del paciente para eliminar: ");
            eliminarCita(dni);
            break;
        case 6:
            dni = leerDni("Ingrese el dni del empleado: ");
            buscarCitaEmpleado(dni);
			break;
		case 7:
            fechaInicio = leerFechaNac("Ingrese la fecha de inicio (YYYY-MM-DD): ");
            fechaFin = leerFechaNac("Ingrese la fecha de fin (YYYY-MM-DD): ");
            nombreArchivo = leerCadenaNoVacia("Ingrese el nombre del archivo de salida: ");
            guardarCitasEntreFechas(fechaInicio,fechaFin,nombreArchivo);
            break;
        case 0:
            cout << "Saliendo del sistema de gesti�n de citas..." << endl;
            break;
        default:
            cout << "Opci�n no v�lida. Intente nuevamente." << endl;
            break;
        }
    } while (num != 0);
}

string jsonToString(json clientesJson) {
    string frase = "";
    for (int i = 0; i < clientesJson.size(); i++) {
        if (clientesJson[i].contains("idEmpleado"))
            frase += "Id Empleado: " + to_string(clientesJson[i]["idEmpleado"].get<int>()) + "\n";
        if (clientesJson[i].contains("idCliente"))
            frase += "Id Paciente: " + to_string(clientesJson[i]["idCliente"].get<int>()) + "\n";
        if (clientesJson[i].contains("nombre"))
            frase += "Nombre: " + clientesJson[i]["nombre"].get<std::string>() + "\n";
        if (clientesJson[i].contains("apellido"))
            frase += "Apellido: " + clientesJson[i]["apellido"].get<std::string>() + "\n";
        if (clientesJson[i].contains("dni"))
            frase += "DNI: " + clientesJson[i]["dni"].get<std::string>() + "\n";
        if (clientesJson[i].contains("telefono"))
            frase += "Telefono: " + clientesJson[i]["telefono"].get<std::string>() + "\n";
        if (clientesJson[i].contains("historial"))
            frase += "Historial: " + clientesJson[i]["historial"].get<std::string>() + "\n";
        if (clientesJson[i].contains("fechaNac"))
            frase += "Fecha de nacimiento: " + clientesJson[i]["fechaNac"].get<std::string>() + "\n";
        if (clientesJson[i].contains("categoria"))
            frase += "Categoria: " + clientesJson[i]["categoria"].get<std::string>() + "\n";
        if (clientesJson[i].contains("fecha") && clientesJson[i].contains("hora"))
            frase += "Fecha: " + clientesJson[i]["fecha"].get<std::string>() + " Hora: " + clientesJson[i]["hora"].get<std::string>() + "\n";
        if (clientesJson[i].contains("motivo"))
            frase += "Motivo: " + clientesJson[i]["motivo"].get<std::string>() + "\n";
        if (clientesJson[i].contains("id"))
            frase += "ID: " + to_string(clientesJson[i]["id"].get<int>()) + "\n";
        frase += "\n";
    }
    return frase;
}

string leerCadenaNoVacia(const string& mensaje) {
    string entrada;
    while (true) {
        cout << mensaje;
        getline(cin, entrada);
        if (!entrada.empty()) {
            break;
        }
        cout << "El campo no puede estar vac�o. Intente nuevamente: ";
    }
    return entrada;
}

string leerNombreApellido(const string& mensaje) {
    string entrada;
    regex regexNombreApellido("^[A-Za-z]{2,}$");
    while (true) {
        cout << mensaje;
        getline(cin, entrada);
        if (!entrada.empty()) {
            entrada[0] = toupper(entrada[0]);
            if (regex_match(entrada, regexNombreApellido)) {
                break;
            }
        }
        cout << "Entrada inv�lida. Debe tener al menos 2 caracteres, solo letras, sin tildes ni �. Intente nuevamente: ";
    }
    return entrada;
}

string leerDni(const string& mensaje) {
    string entrada;
    regex dniRegex("^[0-9]{8}[A-HJ-NP-TV-Z]$");
    while (true) {
        entrada = leerCadenaNoVacia(mensaje);
        if (!entrada.empty() && entrada.length() == 9) {
            entrada[8] = toupper(entrada[8]);
        }
        if (regex_match(entrada, dniRegex)) {
            break;
        }
        cout << "El DNI debe tener 8 n�meros y luego una �ltima. Intente nuevamente: ";
    }
    return entrada;
}

string leerFechaNac(const string& mensaje) {
    string entrada;
    regex FechaNacRegex("^([0-2][0-9]|3[0-1])/(0[1-9]|1[0-2])/([0-9]{4})$");
    while (true) {
        entrada = leerCadenaNoVacia(mensaje);
        if (regex_match(entrada, FechaNacRegex)) {
            break;
        }
        cout << "La fecha tiene que estar en el formato dd/mm/yyyy. Intente nuevamente: ";
    }
    return entrada;
}

string leerTlf(const string& mensaje) {
    string entrada;
    regex tlfRegex("^[0-9]{9}$");
    while (true) {
        entrada = leerCadenaNoVacia(mensaje);
        if (regex_match(entrada, tlfRegex)) {
            break;
        }
        cout << "El telefono debe tener 9 n�meros. Intente nuevamente: ";
    }
    return entrada;
}

string leerHora(const string& mensaje) {
    string entrada;
    regex horaRegex("^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$");
    while (true) {
        entrada = leerCadenaNoVacia(mensaje);
        if (regex_match(entrada, horaRegex)) {
            break;
        }
        cout << "La hora debe estar en el formato hh:mm. Intente nuevamente: ";
    }
    return entrada;
}
string leerHistorial(const string& mensaje) {
	string entrada;
    regex historialRegex("^[A-Za-z0-9 ]+$");
	while (true) {
        entrada = leerCadenaNoVacia(mensaje);
		if (!entrada.empty()) {
			if (regex_match(entrada, historialRegex)) {
				break;
			}
		}
		cout << "Entrada inv�lida.Si no tiene historial aun escribalo ya que no puede estar vacio,n�meros y espacios. Intente nuevamente: ";
	}
	return entrada;
}
string leerCategoria(const string& mensaje) {
    string entrada;
    while (true) {
        cout << mensaje; 
        entrada = leerCadenaNoVacia(""); 
        transform(entrada.begin(), entrada.end(), entrada.begin(), ::tolower); 

        if (entrada == "enfermero" || entrada == "medico") {
            break; 
        }
        cout << "La categor�a debe ser 'enfermero' o 'medico'. Intente nuevamente." << endl;
    }
    return entrada;
}






