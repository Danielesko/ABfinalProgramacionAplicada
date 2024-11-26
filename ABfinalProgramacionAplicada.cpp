#include <iostream>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>

int main() {
    try {
        // Establece la conexión
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> conn(driver->connect("tcp://127.0.0.1:3307", "root", "9455"));

        // Selecciona la base de datos
        conn->setSchema("abfinalprogramacionaplicada");

        // Ejecuta la consulta para mostrar los datos de la tabla Empleados
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM Empleados"));

        // Muestra los resultados
        std::cout << "Datos en la tabla Empleados:" << std::endl;
        while (res->next()) {
            std::cout << " - ID: " << res->getInt("id") << ", Nombre: " << res->getString("nombre") << std::endl;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Código de error: " << e.getErrorCode() << std::endl;
        std::cerr << "Estado SQL: " << e.getSQLState() << std::endl;
        return 1;
    }

    std::cout << "Conexión y consulta ejecutadas exitosamente." << std::endl;
    return 0;
}
