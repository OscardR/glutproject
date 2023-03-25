#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "matematicas.h"
#include "material.h"
#include "texturas.h"
#include "modelado.h"

GLuint numTextura;

/**
 * Devuelve el punto 3D asociado a unos determinados datos.
 * R1: radio del primer anillo.
 * y1: altura del primer anillo.
 * P: el número total de tramos en el anillo.
 * N: el tramo actual.
 */
Punto3D vertice(float R1, float y1, int P, int N) {

	Punto3D p;

	p.x = dameX(R1, P, N);
	p.y = y1;
	p.z = dameZ(R1, P, N);

	return (p);
}

/**
 * Devuelve la normal de un vértice sobre una superficie de revolución.
 * R1: radio del primer anillo.
 * R2: radio del segundo anillo.
 * y1: altura del primer anillo.
 * y2: altura del segundo anillo.
 * P: el número total de tramos en el anillo.
 * N: el tramo actual.
 */
Vector3D normal(float R1, float R2, float y1, float y2, int P, int N) {
	Punto3D p, q, r;
	Vector3D v, w, normal;

	p = vertice(R1, y1, P, N);
	if (R1 == 0.0f && R2 == 0.0f) {
		normal.a = normal.c = 0.0f;
		normal.b = 1.0f;
		return (normal);
	}
	if (R1 == 0.0f) {
		q = vertice(R2, y2, P, (N + 1) % P);
	} else {
		q = vertice(R1, y1, P, (N + 1) % P);
	}
	r = vertice(R2, y2, P, N);
	v = vector(p, q);
	w = vector(p, r);
	normal = productoVectorial(w, v);

	return (normal);
}

/**
 *  Dibuja una tira de cuadriláteros.
 *  R1, R2, R3: radios de tres anillos consecutivos.
 *  y1, y2, y3: altura de cada uno de los anillos.
 *  P: número de puntos sobre cada anillo.
 */
void tira(float R1, float R2, float R3, float y1, float y2, float y3, int P) {
	int i;
	Punto3D p;
	Vector3D n;

	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= P; i++) {
		// tira R1/R2
		n = normal(R1, R2, y1, y2, P, i);
		glNormal3f(n.a, n.b, n.c);
		glTexCoord2f((float) i / P, y1 + 0.5);
		p = vertice(R1, y1, P, i);
		glVertex3f(p.x, p.y, p.z);
		// tira R2/R3
		n = normal(R2, R3, y2, y3, P, i);
		glNormal3f(n.a, n.b, n.c);
		glTexCoord2f((float) i / P, y2 + 0.5);
		p = vertice(R2, y2, P, i);
		glVertex3f(p.x, p.y, p.z);
	}
	glEnd();
}

/**
 * Algoritmo de dibujo para una forma sólida de revolución.
 * H: la altura de la figura.
 * N: el número de anillos
 * P: número de divisiones en cada anillo.
 * f(float y): puntero a la función que nos devuelve el valor de radio en función de y.
 */
void formaSolida(float H, int N, int P, float (*f)(float y)) {
	int i;
	float y1, y2, y3, r1, r2, r3;

	tapa(f(-H / 2), -H / 2, N, 0);
	for (i = 0; i < N - 1; i++) {
		y1 = i * H / (N - 1) - (H / 2);
		r1 = f(y1);
		y2 = (i + 1) * H / (N - 1) - (H / 2);
		r2 = f(y2);
		if (i + 2 < N) {
			y3 = (i + 2) * H / (N - 1) - (H / 2);
			r3 = f(y3);
		} else {
			r3 = r2;
			y3 = y2;
		}
		tira(r1, r2, r3, y1, y2, y3, P);
	}
	tapa(f(H / 2), H / 2, N, 1);
}

/**
 * Algoritmo de dibujo para una forma hueca de revolución.
 * La cámara puede situarse dentro.
 * H: la altura de la figura.
 * N: el número de anillos
 * P: número de divisiones en cada anillo.
 * f(float y): puntero a la función que nos devuelve el valor de radio en función de y.
 */
void formaHueca(float H, int N, int P, float (*f)(float y)) {
	int i;
	float y1, y2, y3, r1, r2, r3;

	tapa(f(-H / 2), H / 2, N, 0);
	for (i = 0; i < N - 1; i++) {
		y1 = i * H / (N - 1) - (H / 2);
		r1 = f(y1);
		y2 = (i + 1) * H / (N - 1) - (H / 2);
		r2 = f(y2);
		if (i + 2 < N) {
			y3 = (i + 2) * H / (N - 1) - (H / 2);
			r3 = f(y3);
		} else {
			r3 = r2;
			y3 = y2;
		}
		tira(-r1, -r2, -r3, -y1, -y2, -y3, P);
	}
	tapa(f(H / 2), -H / 2, N, 1);
}

/**
 * Devuelve el valor de x del punto que gira.
 * R: el radio de giro.
 * N: el número total de tramos en el anillo.
 * n: el tramo actual.
 */
float dameX(float R, int N, int n) {
	float x = (float) R * cos(n * (2 * M_PI) / N);
	return x;
}

/**
 * Devuelve el valor de z del punto que gira.
 * R: el radio de giro.
 * N: el número total de tramos en el anillo.
 * n: el tramo actual.
 */
float dameZ(float R, int N, int n) {
	float z = (float) R * sin(n * (2 * M_PI) / N);
	return z;
}

/**
 * Dibuja un anillo.
 * R: el radio del anillo.
 * y: la altura a la que se dibuja el anillo.
 * N: el número de tramos del anillo.
 */
void anillo(float R, float y, int N) {
	int i;
	float x, z;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i < N; i++) {
		x = dameX(R, N, i);
		z = dameZ(R, N, i);
		glVertex3f(x, y, z);
	}
	glEnd();
}

/**
 * Dibuja una tapa.
 * R: el radio del anillo.
 * y: la altura a la que se dibuja la tapa.
 * N: el número de tramos de la tapa.
 */
void tapa(float R, float y, int N, int flip) {
	int i;
	float x, z;

	glPushMatrix();
	glTranslatef(0.0f, y, 0.0f);
	if (flip == true) {
		glRotatef(180, 1.0f, 0.0f, 0.0f);
	}
	glBegin(GL_POLYGON);
	for (i = 0; i < N; i++) {
		x = dameX(R, N, i);
		z = dameZ(R, N, i);
		glVertex3f(x, 0, z);
		glNormal3f(0.0f, 1.0f, 0.0f);
	}
	glEnd();
	glPopMatrix();
}

/**
 * Devuelve un valor de radio en función de la altura
 * que se le pasa como parámetro para dibujar un cono.
 * y: el valor de la altura.
 */
float fCono(float y) {
	return ((y - 0.5f) / 2);
}

/**
 * Dibuja un cono.
 * N: el número de anillos y tramos en cada anillo
 */
void conoAlambre(int N) {
	formaAlambre(1.0f, N, fCono);
}

/**
 * Dibuja un cono sólido.
 * N: el número de anillos.
 * P: número de divisiones en cada anillo.
 */
void conoSolido(int N, int P) {
	formaSolida(1.0f, N, P, fCono);
}

/**
 * Devuelve un valor de radio en función de la altura
 * que se le pasa como parámetro para dibujar un cilindro.
 * y: el valor de la altura.
 */
float fCilindro(float y) {
	return (0.5);
}

/**
 * Dibuja un cilindro.
 * N: el número de anillos y tramos en cada anillo
 */
void cilindroAlambre(int N) {
	formaAlambre(1.0f, N, fCilindro);
}

/**
 * Dibuja un cilindro sólido.
 * N: el número de anillos y tramos en cada anillo
 * P: número de divisiones en cada anillo.
 */
void cilindroSolido(int N, int P) {
	formaSolida(1.0f, N, P, fCilindro);
}

/**
 * Dibuja un cilindro hueco.
 * N: el número de anillos y tramos en cada anillo
 * P: número de divisiones en cada anillo.
 */
void cilindroHueco(int N, int P) {
	formaHueca(1.0f, N, P, fCilindro);
}

/**
 * Devuelve un valor de radio en función de la altura
 * que se le pasa como parámetro para dibujar una esfera.
 * y: el valor de la altura.
 */
float fEsfera(float y) {
	return ((float) sqrt(fabs(0.25 - (y * y))));
}

/**
 * Dibuja una esfera.
 * N: el número de anillos y tramos en cada anillo
 */
void esferaAlambre(int N) {
	formaAlambre(1.0f, N, fEsfera);
}

/**
 * Dibuja una esfera sólida.
 * N: el número de anillos.
 * P: número de divisiones en cada anillo.
 */
void esferaSolida(int N, int P) {
	formaSolida(1.0f, N, P, fEsfera);
}

/**
 * Dibuja una esfera hueca.
 * N: el número de anillos.
 * P: número de divisiones en cada anillo.
 */
void esferaHueca(int N, int P) {
	formaHueca(1.0f, N, P, fEsfera);
}

/**
 * Devuelve un valor de radio en función de la altura
 * que se le pasa como parámetro para dibujar un jarrón.
 * y: el valor de la altura.
 */
float fJarron(float y) {
	float z = 4 * y * y;
	return ((float) (z * z - z + 0.4f));
}

/**
 * Dibuja un jarrón sólido.
 * N: el número de anillos y tramos en cada anillo
 */
void jarronSolido(int N, int P) {
	formaSolida(1.0f, N, P, fJarron);
}

/**
 * Algoritmo de dibujo para una figura de revolución.
 * H: la altura de la figura.
 * N: el número de anillos y divisiones en cada anillo.
 * f(float y): puntero a la función que nos devuelve el valor de radio en función de y.
 */
void formaAlambre(float H, int N, float (*f)(float y)) {
	int i;
	float y, r;

	for (i = 0; i < N; i++) { // Para cada nivel de altura
		y = i * H / (N - 1) - (H / 2);
		r = f(y);            // obtenemos el radio
		anillo(r, y, N);     // y dibujamos un anillo
	}
}

/**
 * para hacer un toroide
 * N: número de anillos
 * P: número de secciones por anillo
 */
void toroideSolido(float R, float r, int N, int P) {

	// Longitud de una circunferencia:
	double TWOPI = 2 * M_PI;

	// Tantas tiras como anillos:
	for (int i = 0; i < N; i++) {

		// Se construirá a base de quad strips, anillo por anillo
		glBegin(GL_QUAD_STRIP);

		// Secciones de un anillo
		for (int j = 0; j <= P; j++) {

			// Cada anillo tiene dos partes
			for (int k = 1; k >= 0; k--) {

				// Cálculo de coordenadas dentro del toroide
				double s = (i + k) % N + 0.5;
				double t = j % P;

				// Cálculo de coordenadas para la textura
				float u = (i + k) / (float) N;
				float v = t / (float) P;
				glTexCoord2f(u, v);

				// Cálculo de coordenadas para los vértices
				// http://en.wikipedia.org/wiki/Torus#Geometry
				double x = (R + r * cos(s * TWOPI / N)) * cos(t * TWOPI / P);
				double y = (R + r * cos(s * TWOPI / N)) * sin(t * TWOPI / P);
				double z = r * sin(s * TWOPI / N);

				// Creación del vértice
				glVertex3d(2 * x, 2 * y, 2 * z);
			}
		}
		glEnd(); // Fin de la malla
	}
}

/**
 * Para hacer cubos
 * W: anchura
 * H: altura
 * n: factor de escala
 */
void cuboSolido(float W, float H, float n) {
	glPushMatrix();
	// BOTTOM
	glBegin(GL_QUADS);
	{
		glNormal3f(-0.1f, 1, -0.1f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-W / 2, -H / 2 * n, -W / 2);
		glNormal3f(0.1f, 1, -0.1f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(W / 2, -H / 2 * n, -W / 2);
		glNormal3f(0.1f, 1, 0.1f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(W / 2, -H / 2 * n, W / 2);
		glNormal3f(-0.1f, 1, 0.1f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-W / 2, -H / 2 * n, W / 2);
	}
	glEnd();
	// LEFT
	glBegin(GL_QUADS);
	{
		glNormal3f(1, -0.1f, 0.1f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-W / 2 * n, -H / 2, W / 2);
		glNormal3f(1, -0.1f, -0.1f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-W / 2 * n, H / 2, W / 2);
		glNormal3f(1, 0.1f, -0.1f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(-W / 2 * n, H / 2, -W / 2);
		glNormal3f(1, 0.1f, 0.1f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-W / 2 * n, -H / 2, -W / 2);
	}
	glEnd();
	// BACK
	glBegin(GL_QUADS);
	{
		glNormal3f(-0.1f, -0.1f, 1.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-W / 2, -H / 2, -W / 2 * n);
		glNormal3f(0.1f, -0.1f, 1.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-W / 2, H / 2, -W / 2 * n);
		glNormal3f(0.1f, 0.1f, 1.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(W / 2, H / 2, -W / 2 * n);
		glNormal3f(-0.1f, 0.1f, 1.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(W / 2, -H / 2, -W / 2 * n);
	}
	glEnd();
	// TOP
	glBegin(GL_QUADS);
	{
		glNormal3f(-0.1f, -1.0f, -0.1f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-W / 2, H / 2 * n, -W / 2);
		glNormal3f(-0.1f, -1.0f, 0.1f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-W / 2, H / 2 * n, W / 2);
		glNormal3f(0.1f, -1.0f, 0.1f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(W / 2, H / 2 * n, W / 2);
		glNormal3f(0.1f, -1.0f, -0.1f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(W / 2, H / 2 * n, -W / 2);
	}
	glEnd();
	// RIGHT
	glBegin(GL_QUADS);
	{
		glNormal3f(-1.0f, -0.1f, -0.1f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(W / 2 * n, -H / 2, -W / 2);
		glNormal3f(-1.0f, 0.1f, -0.1f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(W / 2 * n, H / 2, -W / 2);
		glNormal3f(-1.0f, 0.1f, 0.1f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(W / 2 * n, H / 2, W / 2);
		glNormal3f(-1.0f, -0.1f, 0.1f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(W / 2 * n, -H / 2, W / 2);
	}
	glEnd();
	// FRONT
	glBegin(GL_QUADS);
	{
		glNormal3f(0.1f, -0.1f, -1.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(W / 2, -H / 2, W / 2 * n);
		glNormal3f(0.1f, 0.1f, -1.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(W / 2, H / 2, W / 2 * n);
		glNormal3f(-0.1f, 0.1f, -1.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-W / 2, H / 2, W / 2 * n);
		glNormal3f(-0.1f, -0.1f, -1.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-W / 2, -H / 2, W / 2 * n);
	}
	glEnd();
	glPopMatrix();
}

/**
 * Construye una bola de pinchos
 * n_puas: El número de pinchos.
 * factor: el factor de escala
 */
void bolaPinchosSolida(int n_puas, float factor) {

	float inc_alpha = 360.0f / n_puas;
	float radio = cos(inc_alpha / 360 * 3.141592);

	Cromo(100.0f);
	glPushMatrix();
	glScalef(0.2f * n_puas * factor, 0.2f * n_puas * factor,
			0.2f * n_puas * factor);
	esferaSolida(M, M);
	glPopMatrix();

	Plata(100.0f);
	for (int j = 0; j < n_puas; j++) {
		glPushMatrix();

		glRotatef(j * inc_alpha, 0, 1.0f, 0);
		for (int i = 0; i < (n_puas - 1) / 2 + 2; i++) {
			glPushMatrix();
			glRotatef(i * inc_alpha, 0, 0, 1.0f);
			glTranslatef(0, radio * factor, 0);
			glScalef(3.0f * factor / n_puas, 3.0f * factor / n_puas,
					3.0f * factor / n_puas);
			conoSolido(M, M);
			glPopMatrix();
		}
		glPopMatrix();
	}
}

// Una bola de pinchos de tamaño estándar
void modeladoBolaPinchos(void) {
	bolaPinchosSolida(6, 0.7f);
}

// La esfera que está al fondo
void modeladoEscenario(void) {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, dameTextura(8));
	glPushMatrix();
	glScalef(100, 100, 100);
	esferaHueca(M, M);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

// Los objetos satélites;
void modeladoSatelites(void) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, dameTextura(numTextura));
	glPushMatrix();
	Plata(20.0f);
	glScalef(0.25f, 0.25f, 0.25f);
	glTranslatef(4.0f, 0.0f, 0.0f);
	esferaSolida(M, M);
	Cristal(100.0f);
	glTranslatef(-8.0f, 0.0f, 0.0f);
	esferaSolida(M, M);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

// El toroide por el que se circulará
void modeladoCircuito(void) {
	// Desactivar la ocultación de caras para la transparencia, y volver a activar luces.
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, dameTextura(27));
	Cristal(100.0f);
	glPushMatrix();
	glTranslatef(-20.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	toroideSolido(10.0f, 2.0f, M, M);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
