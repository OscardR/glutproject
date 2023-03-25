#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "texturas.h"

Textura * texturas;

/**
 * Lee una imagen de textura en formato tga
 * Parametros --> char *fichero : Cadena de caracteres con el nombre
 * del fichero
 * int num: Numero que identifica la textura
 * Salida --> Ninguna
 */bool leeTextura(char *fichero, int n) {
	FILE *tga;

	// Apertura del fichero TGA
	if ((tga = fopen(fichero, "rb")) == NULL ) {
		printf("Error abriendo el fichero: %s\n", fichero);
		return false;
	} else {
		// Lee los 12 primeros caracteres de la cabecera
		fread(texturas[n].data, sizeof(GLubyte), 0x0C, tga);

		// Leemos la anchura y altura de la imagen por si no coincide
		short w, h, temp;
		fread(&w, sizeof(char), 2, tga);
		fread(&h, sizeof(char), 2, tga);

		printf("Dimensiones del archivo: %dx%d\n", w, h);
		if (w > MAX_W || h > MAX_H) {
			printf("Exceden el tamaño máximo!");
			return false;
		}

		printf("Tamaño en bytes: %d\n", w * h * 3);

		// Asignamos la anchura y altura a la textura actual
		texturas[n].w = w;
		texturas[n].h = h;

		// Leemos 2 bytes más de la cabecera para alinear con el
		// inicio de los datos
		fread(&temp, sizeof(char), 2, tga);

		// Lee la imagen
		fread(texturas[n].data, sizeof(GLubyte), w * h * 3, tga);

		// Cierre del fichero TGA
		fclose(tga);
		return true;
	}
}

/**
 * Llama al método que lee los píxeles del fichero,
 * genera una textura con esos píxeles y asigna la textura
 * generada a un nombre de textura
 */
//
bool cargaTextura(char *fichero, int num) {
	if (leeTextura(fichero, num)) {
		glBindTexture(GL_TEXTURE_2D, texturas[num].name);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturas[num].w, texturas[num].h,
				0, GL_BGR, GL_UNSIGNED_BYTE, texturas[num].data);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // GL_BLEND
		return true;
	} else {
		return false;
	}
}

/**
 * Carga todas las texturas y las inicializa en OpenGL
 */
void inicializaTexturas(void) {
	// Alojamos memoria para ellas
	texturas = malloc(MAX_TEX * sizeof(Textura));

	char *archivos[] = { "alriver.tga", "brick.tga", "dirt.tga", "eye.tga",
			"icetips.tga", "lava.tga", "marble.tga", "ojo.tga", "pixels.tga",
			"random.tga", "rock.tga", "roof.tga", "Terrain0.tga",
			"Terrain1.tga", "Terrain2.tga", "Terrain3.tga", "tree1.tga",
			"water.tga", "wood.tga", "yellow.tga", "clouds-360.tga",
			"clouds2-360.tga", "clouds-tiled.tga", "landscape-1024.tga",
			"nightsky-360-1024.tga", "sky-circular.tga", "space-tiled.tga",
			"spaceship-1024.tga", "aluminio-1024.tga" };

	for (int i = 0; i < sizeof(archivos) / sizeof(*archivos); i++) {
		glGenTextures(1, &texturas[i].name);

		char *ruta = malloc(256);
		strcpy(ruta, "tex/");
		strcat(ruta, archivos[i]);

		if (cargaTextura(ruta, i)) {
			printf("Archivo %s cargado en la textura %d:[%d]\n", ruta, i,
					texturas[i].name);
		}
		free(ruta);
	}
}

/**
 * Devuelve el nombre de la textura en el índice n
 */
GLuint dameTextura(int n) {
	return texturas[n].name;
}

/**
 * Libera la memoria ocupada por las texturas
 */
void finalizaTexturas(void) {
	printf("Liberando memoria de texturas...\n");
	free(texturas);
}
