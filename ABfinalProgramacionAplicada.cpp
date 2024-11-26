#include <iostream>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>

int main() {
    try {
        // Establece la conexión
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection* conn = driver->connect("tcp://127.0.0.1:3306", "root", "9455");

        // Selecciona la base de datos
        conn->setSchema("abfinalprogramacionaplicada");

        // Ejecuta la consulta para mostrar las tablas
        sql::Statement* stmt = conn->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SHOW TABLES");

        // Muestra los resultados
        std::cout << "Tablas en la base de datos:" << std::endl;
        while (res->next()) {
            std::cout << " - " << res->getString(1) << std::endl;
        }

        // Limpia los recursos
        delete res;
        delete stmt;
        delete conn;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Hello CMake." << std::endl;
    return 0;
}
