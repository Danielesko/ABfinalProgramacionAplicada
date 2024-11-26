cmake_minimum_required(VERSION 3.10)
project(ABfinalProgramacionAplicada)

set(CMAKE_CXX_STANDARD 17)

# Directorios del MySQL Connector
include_directories(mysql-connector/include)
link_directories(mysql-connector/lib64/vs14)

# Archivos fuente
add_executable (ABfinalProgramacionAplicada "ABfinalProgramacionAplicada.cpp" "ABfinalProgramacionAplicada.h" "Persona.cpp" "Empleado.cpp" "Cliente.cpp" "Cita.cpp" "Quejas.cpp")

# Vincula la biblioteca MySQL Connector
target_link_libraries(ABfinalProgramacionAplicada mysqlcppconn)
