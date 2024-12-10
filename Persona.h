#ifndef PERSONA_H  
#define PERSONA_H

#include <string>  

class Persona {
public:
    int id;                
    std::string nombre;    
    std::string apellido;  
    std::string dni;       
    string tlf;               

public:
    Persona(int id, std::string nombre, std::string apellido, std::string dni, string tlf)
        : id(id), nombre(nombre), apellido(apellido), dni(dni), tlf(tlf) {
    }

    int getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getApellido() const { return apellido; }
    std::string getDni() const { return dni; }
    string getTlf() const { return tlf; }
};

#endif  
