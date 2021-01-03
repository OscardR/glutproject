cmake_minimum_required(VERSION 3.17)

project(glutproject C)

set(CMAKE_C_STANDARD 99)

add_executable(glutproject
        luces.c
        luces.h
        matematicas.c
        matematicas.h
        material.c
        material.h
        modelado.c
        modelado.h
        otras_escenas.c
        revolucion.c
        revolucion.h
        texturas.c
        texturas.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(COPY tex DESTINATION "${CMAKE_BINARY_DIR}")

include_directories(. ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(glutproject ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )