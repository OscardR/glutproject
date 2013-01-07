#include <stdlib.h>

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "material.h"

void Cobre(float s) {
	float ambiente[] = { 0.33f, 0.26f, 0.23f, 1.0f };
	float difusa[] = { 0.50f, 0.11f, 0.00f, 1.0f };
	float especular[] = { 0.95f, 0.73f, 0.10f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT, GL_SHININESS, s);
}

void Cromo(float s) {
	float ambiente[] = { 0.1f, 0.1f, 0.1f, 1 };
	float difusa[] = { 0.2f, 0.25f, 0.25f, 1 };
	float especular[] = { 0.85f, 0.86f, 0.9f, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT, GL_SHININESS, s);
}

void Plata(float s) {
	float mat_ambient[] = { 0.25f, 0.35f, 0.35f, 1.0f };
	float mat_diffuse[] = { 0.45f, 0.45f, 0.46f, 1.0f };
	float mat_specular[] = { 0.95f, 0.98f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, s);
}

void Cristal(float s) {
	float cristal_amb[] = { 0.5f, 0.5f, 0.5f, 0.8f };
	float cristal_dif[] = { 0.75f, 0.75f, 0.75f, 0.8f };
	float cristal_spe[] = { 1.0f, 1.0f, 1.0f, 0.8f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cristal_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cristal_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cristal_spe);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, s);
}
