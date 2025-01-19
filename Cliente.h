#ifndef CLIENTE_H  
#define CLIENTE_H
#pragma once

#include "Persona.h" 
#include <string>      
#include <nlohmann/json.hpp>  
using json = nlohmann::json;


class Cliente : public Persona {
private:
    static int idAnterior;
    std::string fechaNac;
    std::string historial;

public:
    Cliente() : Persona(0, "", "", "", ""), fechaNac(""), historial("") {}

    Cliente(std::string nombre, std::string apellido, std::string dni, string tlf, std::string fechaNac, std::string historial)
        : Persona(idAnterior++, nombre, apellido, dni, tlf), fechaNac(fechaNac), historial(historial) {
    }
    Cliente(int id, std::string nombre, std::string apellido, std::string dni, std::string tlf, std::string fechaNac, std::string historial)
        : Persona(id, nombre, apellido, dni, tlf), fechaNac(fechaNac), historial(historial) {
    }
    static void guardarId() {
        ofstream archivo("id.json", std::ios::out);
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
        ifstream archivo("id.json", std::ios::in);
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
            {"id", getId()},
            {"nombre", getNombre()},
            {"apellido", getApellido()},
            {"dni", getDni()},
            {"telefono", getTlf()},
            {"fechaNac", fechaNac},
            {"historial", historial}
        };
    }
    static int getIdAnterior() { return idAnterior; }
    std::string getFechaNac() const { return fechaNac; }
    std::string getHistorial() const { return historial; }

    void setFechaNac(const std::string& fecha) { fechaNac = fecha; }
    void setHistorial(const std::string& hist) { historial = hist; }
};

void escribirClienteArchivo(json cliente);
void crearCliente();
void mostrarPacientes();
void buscarPaciente(string nombre);
Cliente buscarPacienteDni(string dni);
void menuModificarPaciente();
void eliminarPaciente(string dni);
void modificarPacienteDni(string dni);
void mofificarPacienteNombre(string dni);
void modificarPacienteApellido(string dni);
void modificarPacienteTlf(string dni);
void mofificarPacienteFechaNac(string dni);
void modificarPacienteHistorial(string dni);
void mostrarHistorialPaciente(string dni);
#endif  






