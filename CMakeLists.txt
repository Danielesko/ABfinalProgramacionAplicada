cmake_minimum_required(VERSION 3.10)
project(ABfinalProgramacionAplicada)

set(CMAKE_CXX_STANDARD 17)


# Agregue un origen al ejecutable de este proyecto.
add_executable(ABfinalProgramacionAplicada
    ABfinalProgramacionAplicada.cpp
    Persona.cpp
    Empleado.cpp
    Cliente.cpp  # Asegúrate de que este archivo está aquí
    Cita.cpp
    Quejas.cpp
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ABfinalProgramacionAplicada PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
# CMakeLists.txt
include_directories(${CMAKE_SOURCE_DIR}/single_include)