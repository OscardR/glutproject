/*
 * escena_figuras.c
 *
 *  Created on: 07/01/2013
 *      Author: oscar
 */
#include <stdio.h>
#include <stdlib.h>

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "matematicas.h"
#include "modelado.h"
#include "material.h"
#include "texturas.h"

/**
 * Escena de figuras
 */
void escenaFiguras(void) {

	Plata(100.0f);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, dameTextura(1));
		glTranslatef(-1.0f, 1.2f, 0);
		cilindroSolido(M, M);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0f, 1.2f, 0);
		conoSolido(M, M);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(1.0f, 1.2f, 0);
	esferaSolida(M, M);
	glPopMatrix();

	for (int i = 0; i < 3; i++) {
		Cobre(i * 40.0f + 20.0f);
		glPushMatrix();
		glTranslatef(-1.0f + i, 0.0f, 0);
		glRotatef(i * 20.0f, 1.0f, 0.5f, 0.25f);
		jarronSolido(M, M);
		glPopMatrix();
	}

	for (int i = 0; i < 3; i++) {
		Cromo(i * 40.0f + 20.0f);
		glPushMatrix();
		glTranslatef(-1.0f + i, -1.2f, 0);
		conoSolido(M, M);
		glPopMatrix();
	}
}

/**
 * El generador de escena de la bola de pinchos
 */
void escenaBola(void) {
	bolaPinchosSolida(8, 0.25);
	Cobre(100.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, dameTextura(8));
	cuboSolido(6.0f, 6.0f, -1.0f);
	glDisable(GL_TEXTURE_2D);
}
