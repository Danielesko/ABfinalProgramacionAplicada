# CMakeList.txt: proyecto de CMake para ABfinalProgramacionAplicada, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ABfinalProgramacionAplicada")

# Agregue un origen al ejecutable de este proyecto.
add_executable (ABfinalProgramacionAplicada "ABfinalProgramacionAplicada.cpp" "ABfinalProgramacionAplicada.h" "Persona.cpp" "Empleado.cpp" "Cliente.cpp" "Cita.cpp" "Quejas.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ABfinalProgramacionAplicada PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
