#pragma once
#include "Persona.h" 
#include <string>      
#include <nlohmann/json.hpp>  
using json = nlohmann::json;
class Empleado : public Persona {	
private:
    static int idAnterior;
    std::string categoria;
public:
	Empleado() : Persona(0, "", "", "", ""), categoria("") {}
	Empleado(std::string nombre, std::string apellido, std::string dni, string tlf, std::string categoria)
		: Persona(idAnterior++, nombre, apellido, dni, tlf), categoria(categoria) {
	}
	Empleado(int id, std::string nombre, std::string apellido, std::string dni, std::string tlf, std::string categoria)
		: Persona(id, nombre, apellido, dni, tlf), categoria(categoria) {
	}
	static void guardarId() {
		ofstream archivo("idEmpleado.json", std::ios::out);
		if (archivo.is_open()) {
			json config;
			config["idAnterior"] = idAnterior;
			archivo << config.dump(4);
			archivo.close();
		}
		else {
		}
	}
	static void cargarId() {
		ifstream archivo("idEmpleado.json", std::ios::in);
		if (archivo.is_open()) {
			json config;
			archivo >> config;
			idAnterior = config["idAnterior"];
			archivo.close();
		}
		else {
		}
	}
	json to_json() const {
		return json{
			{"id", getId()},
			{"nombre", getNombre()},
			{"apellido", getApellido()},
			{"dni", getDni()},
			{"telefono", getTlf()},
			{"categoria", categoria}
		};
	}
	static int getIdAnterior() { return idAnterior; }
	std::string getCategoria() const { return categoria; }
};
void crearEmpleado();
void escribirEmpleadoArchivo(json empleado);
void mostrarEmpleados();
void buscarEmpleado(string nombre);
Empleado buscarEmpleadoDni(string dni);
void eliminarEmpleado(string dni);
void menuModificarEmpleado();
void modificarEmpleadoDni(string dni);
void modificarEmpleadoNombre(string dni);
void modificarEmpleadoApellido(string dni);
void modificarEmpleadoTlf(string dni);
void modificarEmpleadoCategoria(string dni);
void mostrarEmpleadosPorCategoria(string categoria);
