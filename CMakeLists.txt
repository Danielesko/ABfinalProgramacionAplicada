cmake_minimum_required(VERSION 3.10)
project(ABfinalProgramacionAplicada)

set(CMAKE_CXX_STANDARD 17)

# Archivos fuente
add_executable(ABfinalProgramacionAplicada 
    ABfinalProgramacionAplicada.cpp 
    Persona.cpp 
    Empleado.cpp 
    Cliente.cpp 
    Cita.cpp 
    Quejas.cpp 
    conexion.cpp
)

# Agrega el directorio de encabezados del conector MySQL
include_directories("mysql-connector/include")

# Agrega el directorio de bibliotecas del conector MySQL
link_directories("mysql-connector/lib64/vs14")

# Enlaza la biblioteca MySQL Connector/C++
target_link_libraries(ABfinalProgramacionAplicada mysqlcppconn)  # O el nombre correcto de la librería



