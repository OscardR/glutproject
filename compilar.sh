#!/bin/bash

gcc \
    matematicas.c \
    luces.c \
    material.c \
    texturas.c \
    modelado.c \
    revolucion.c \
    -o glutproject \
    -lm -lGL -lGLU -lglut \
    -std=c99
