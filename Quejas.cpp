#include "ABfinalProgramacionAplicada.h"

class Quejas {
	int id;
	string descripcion;
	int idCliente;
	int idCatalogo;

public:
	Quejas(int id, int idCliente, int idCatalogo, string descripcion) {
		this->id = id;
		this->idCliente = idCliente;
		this->idCatalogo = idCatalogo;
		this->descripcion = descripcion;
	};
	Quejas() {
		this->id = 0;
		this->idCliente = 0;
		this->idCatalogo = 0;
		this->descripcion = "";
	};
	int getId() {
		return id;
	}
	int getIdCliente() {
		return idCliente;
	}
	int getIdCatalogo() {
		return idCatalogo;
	}
	string getDescripcion() {
		return descripcion;
	}
	void setId(int id) {
		this->id = id;
	}
	void setIdCliente(int idCliente) {
		this->idCliente = idCliente;
	}
	void setIdCatalogo(int idCatalogo) {
		this->idCatalogo = idCatalogo;
	}
	void setDescripcion(string descripcion) {
		this->descripcion = descripcion;
	}
};