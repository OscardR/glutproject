cmake_minimum_required(VERSION 3.17)

project(glutproject C)

set(CMAKE_C_STANDARD 99)

add_executable(glutproject
        luces.c
        matematicas.c
        material.c
        modelado.c
        revolucion.c
        texturas.c
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(COPY tex DESTINATION "${CMAKE_BINARY_DIR}")

include_directories(. ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(glutproject m ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )