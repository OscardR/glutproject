#ifndef TEXTURAS_H
#define TEXTURAS_H

#define MAX_W	1024
#define MAX_H	1024

#define MAX_TEX	30

#include <stdbool.h>

typedef struct _textura {
	short w;
	short h;
	GLuint name;
	GLuint data[MAX_W * MAX_H * 3];
} Textura;

Textura * texturas;

GLuint dameTextura(int n);
bool leeTextura(char *fichero, int num);
bool cargaTextura(char *fichero, int num);
void inicializaTexturas(void);
void finalizaTexturas(void);
#endif
