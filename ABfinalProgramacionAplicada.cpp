#include <iostream>

#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>

int main()
{
    try {
        // Crea el driver y establece conexión
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> conn(
            driver->connect("tcp://127.0.0.1:3306", "root", "")
        );

        // Selecciona la base de datos
        conn->setSchema("abfinalprogramacionaplicada");

        // Crea un Statement para ejecutar consultas
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM Empleados"));

        // Procesa los resultados
        std::cout << "Tablas en la base de datos:" << std::endl;
        while (res->next()) {
            std::cout << " - " << res->getString(1) << std::endl; // Las columnas empiezan en 1
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Código de error: " << e.getErrorCode() << std::endl;
        std::cerr << "Estado SQL: " << e.getSQLState() << std::endl;
        return 1; // Indica que ocurrió un error
    }

    // Mensaje final
    std::cout << "Hello CMake." << std::endl;
    return 0;
}
