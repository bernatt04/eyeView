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

# Buscar paquetes de OpenCV y Dlib
find_package(OpenCV REQUIRED)
find_package(dlib REQUIRED)

# Definir el ejecutable
add_executable(eyeView
    src/main.cpp
)

# Incluir cabeceras de OpenCV y del proyecto
target_include_directories(eyeView PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src
)

# Enlazar OpenCV, Dlib y las librerías matemáticas (lapack y blas)
target_link_libraries(eyeView PRIVATE
    ${OpenCV_LIBS}
    dlib::dlib 
    lapack 
    blas
)