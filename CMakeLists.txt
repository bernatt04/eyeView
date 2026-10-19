cmake_minimum_required(VERSION 3.16)

project(EyeViewProject
    VERSION 1.0.0
    LANGUAGES CXX
)

# Estándar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Exporta compile_commands.json para autocompletado del IDE (clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Buscar paquete de OpenCV
find_package(OpenCV REQUIRED)

# Definir el ejecutable
add_executable(eyeView
    src/main.cpp
)

# Incluir cabeceras de OpenCV y del proyecto (Buenas prácticas de Modern CMake)
target_include_directories(eyeView PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src
)

# Enlazar las librerías de OpenCV al ejecutable
target_link_libraries(eyeView PRIVATE
    ${OpenCV_LIBS}
)