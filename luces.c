#include <stdlib.h>
#include <stdbool.h>

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "luces.h"

void Luz0(bool mostrar) {
	if (mostrar) {
		float luz0_posicion[] = { -0.75f, 0.65f, 0.75f, 0.0f };
		float luz0_ambiente[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float luz0_difusa[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		float luz0_especular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicion);
		glLightfv(GL_LIGHT0, GL_AMBIENT, luz0_ambiente);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, luz0_difusa);
		glLightfv(GL_LIGHT0, GL_SPECULAR, luz0_especular);
		glEnable(GL_LIGHT0);
	} else
		glDisable(GL_LIGHT0);
}

void Luz1(bool mostrar) {
	if (mostrar) {
		float luz1_posicion[] = { 0.75f, 0.65f, 0.75f, 0.0f };
		float luz1_ambiente[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		float luz1_difusa[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		float luz1_especular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT1, GL_POSITION, luz1_posicion);
		glLightfv(GL_LIGHT1, GL_AMBIENT, luz1_ambiente);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, luz1_difusa);
		glLightfv(GL_LIGHT1, GL_SPECULAR, luz1_especular);
		glEnable(GL_LIGHT1);
	} else
		glDisable(GL_LIGHT1);
}

void Luz2(bool mostrar) {
	if (mostrar) {
		float luz2_posicion[] = { 0.0f, -0.65f, 0.75f, 0.0f };
		float luz2_ambiente[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		float luz2_difusa[] = { 0.6f, 0.6f, 0.6f, 1.0f };
		float luz2_especular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
		glLightfv(GL_LIGHT2, GL_POSITION, luz2_posicion);
		glLightfv(GL_LIGHT2, GL_AMBIENT, luz2_ambiente);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, luz2_difusa);
		glLightfv(GL_LIGHT2, GL_SPECULAR, luz2_especular);
		glEnable(GL_LIGHT2);
	} else
		glDisable(GL_LIGHT2);
}

void LuzFocoAzul(bool mostrar) {
	if (mostrar) {
		GLfloat posicion[] = { 1.0f, 0.0f, 0.0f, 0.0f };
		GLfloat ambiente[] = { 0.0f, 0.0f, 0.2f, 1.0f };
		GLfloat difusa[] = { 0.1f, 0.0f, 0.4f, 1.0f };
		GLfloat especular[] = { 0.2f, 0.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT3, GL_POSITION, posicion);
		glLightfv(GL_LIGHT3, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, difusa);
		glLightfv(GL_LIGHT3, GL_SPECULAR, especular);
		glEnable(GL_LIGHT3);
	} else
		glDisable(GL_LIGHT3);
}

void LuzFocoRojo(bool mostrar) {
	if (mostrar) {
		GLfloat posicion[] = { -1.0f, 0.0f, 0.0f, 0.0f };
		GLfloat ambiente[] = { 0.2f, 0.0f, 0.0f, 1.0f };
		GLfloat difusa[] = { 0.4f, 0.0f, 0.1f, 1.0f };
		GLfloat especular[] = { 1.0f, 0.0f, 0.2f, 1.0f };
		glLightfv(GL_LIGHT4, GL_POSITION, posicion);
		glLightfv(GL_LIGHT4, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, difusa);
		glLightfv(GL_LIGHT4, GL_SPECULAR, especular);
		glEnable(GL_LIGHT4);
	} else
		glDisable(GL_LIGHT4);
}

/**
 * Inicializa las luces de la escena
 */
void iniciaLuces(void) {
	GLfloat lmodel_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };

	//Habilita la iluminación.
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	//Cargar todas las luces
	muestraLucesFijas(false);
	muestraLucesMoviles(true);
}

void muestraLucesFijas(bool mostrar) {
	Luz0(mostrar);
	Luz1(mostrar);
	Luz2(mostrar);
}

void muestraLucesMoviles(bool mostrar) {
	LuzFocoAzul(mostrar);
	LuzFocoRojo(mostrar);
}
