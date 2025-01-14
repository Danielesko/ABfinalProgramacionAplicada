#ifndef CLIENTE_H  
#define CLIENTE_H

#include "Persona.h" 
#include <string>      
#include <nlohmann/json.hpp>  
using json = nlohmann::json;  


class Cliente : public Persona {
private:
    static int idAnterior;
    std::string fechaNac;  
    std::string localidad; 

public:
    Cliente() : Persona(idAnterior++, "", "", "", ""), fechaNac(""), localidad("") {}

    Cliente(std::string nombre, std::string apellido, std::string dni, string tlf, std::string fechaNac, std::string localidad)
        : Persona(idAnterior++, nombre, apellido, dni, tlf), fechaNac(fechaNac), localidad(localidad) {}

    json to_json() const {
        return json{
            {"id", getId()},
            {"nombre", getNombre()},
            {"apellido", getApellido()},
            {"dni", getDni()},
            {"telefono", getTlf()},
            {"fechaNac", fechaNac},
            {"localidad", localidad}
        };
    }

    std::string getFechaNac() const { return fechaNac; }
    std::string getLocalidad() const { return localidad; }

    void setFechaNac(const std::string& fecha) { fechaNac = fecha; }
    void setLocalidad(const std::string& loc) { localidad = loc; }
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
void modificarPacienteLocalidad(string dni);
#endif  
