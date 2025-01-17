#pragma once
#include "Persona.h"
#include <string>      
#include <nlohmann/json.hpp>  
class Cita {
private:
	int id;
	std::string hora;
	std::string fecha;
	int idEmpleado;
	int idCliente;
	std::string motivo;
	static int idAnterior;
public:
	Cita() : id(0), hora(""), fecha(""), idEmpleado(0), idCliente(0), motivo("") {}
	Cita(int id, std::string hora, std::string fecha, int idEmpleado, int idCliente, std::string motivo)
		: id(++idAnterior), hora(hora), fecha(fecha), idEmpleado(idEmpleado), idCliente(idCliente), motivo(motivo) {
	}
	static void guardarId() {
		ofstream archivo("idCita.json", std::ios::out);
		if (archivo.is_open()) {
			json config;
			config["idAnterior"] = idAnterior;
			archivo << config.dump(4);
			archivo.close();
		}
		else {
			std::cerr << "No se pudo guardar el idAnterior en el archivo." << std::endl;
		}
	}
	static void cargarId() {
		ifstream archivo("idCita.json", std::ios::in);
		if (archivo.is_open()) {
			json config;
			archivo >> config;
			idAnterior = config["idAnterior"];
			archivo.close();
		}
		else {
			std::cerr << "No se pudo cargar el idAnterior del archivo." << std::endl;
		}
	}
	json to_json() const {
		return json{
			{"id", id},
			{"hora", hora},
			{"fecha", fecha},
			{"idEmpleado", idEmpleado},
			{"idCliente", idCliente},
			{"motivo", motivo}
		};
	}
	int getId() const { return id; }
	std::string getHora() const { return hora; }
	std::string getFecha() const { return fecha; }
	int getIdEmpleado() const { return idEmpleado; }
	int getIdCliente() const { return idCliente; }
	std::string getMotivo() const { return motivo; }
		
};
void crearCita();
vector<string> buscarCitas(string dniEmpleado);
bool coincidirCitas(string dniEmpleado, string dniPaciente);