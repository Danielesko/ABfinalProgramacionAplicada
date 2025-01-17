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
	static int idAnteriorCita;
public:
	Cita() : id(0), hora(""), fecha(""), idEmpleado(0), idCliente(0), motivo("") {}
	Cita(std::string hora, std::string fecha, int idEmpleado, int idCliente, std::string motivo)
		: id(++idAnteriorCita), hora(hora), fecha(fecha), idEmpleado(idEmpleado), idCliente(idCliente), motivo(motivo) {
	}
	static void guardarIdCita() {
		ofstream archivo("idCita.json", std::ios::out);
		if (archivo.is_open()) {
			json config;
			config["idAnteriorCita"] = idAnteriorCita;
			archivo << config.dump(4);
			archivo.close();
		}
		else {
			std::cerr << "No se pudo guardar el idAnterior en el archivo." << std::endl;
		}
	}
	static void cargarIdCita() {
		ifstream archivo("idCita.json", std::ios::in);
		if (archivo.is_open()) {
			json config;
			archivo >> config;
			idAnteriorCita = config["idAnteriorCita"];
			archivo.close();
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
vector <vector<string>> buscarCitas(string dniEmpleado);
bool coincidirCitas(string hora, string fecha, vector<vector<string>> citas);
void escribirCita(json cita);
void mostrarCitas();
void buscarCitasPaciente(string nombre);