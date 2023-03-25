/********************************************************************
 *                                                                  *
 * APELLIDOS: Gómez Alcañiz                                         *
 * NOMBRE: Óscar                                                    *
 * TITULACION: Grado en Ingeniería Informática                      *
 * PROFESOR DE PRACTICAS: Arturo Beltrán                            *
 *                                                                  *
 * DESCRIPCION DE EVENTOS:                                          *
 * tecla l -> activa/desactiva las luces estáticas                  *
 * tecla L -> activa/desactiva las luces dinámicas                  *
 * teclas a/s -> cambiar textura de las bolas                       *
 * flechas (UP, DOWN, LEFT, RIGHT) -> mover bola                    *
 * tecla ESC -> salir del programa                                  *
 *                                                                  *
 * DESCRIPCION DE LAS CARACTERISTICAS MAS IMPORTANTES DEL PROYECTO  *
 * - Se ha incorporado una función que genera                       *
 *   un toroide texturizado                                         *
 * - Las texturas usadas alcanzan los 1024x1024 píxeles             *
 *   de tamaño                                                      *
 * - Se han usado listas de visualización para cada conjunto        *
 *   independiente de elementos (fondo, bola)                       *
 * - Se ha activado el modo GL_BLEND para usar transparencias       *
 * - Se han usado vectores booleanos y un par de funciones extra    *
 *   para las teclas para poder detectar pulsaciones contínuas      *
 * - Se han usado structs para guardar estados de los objetos       *
 *                                                                  *
 ********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "matematicas.h"
#include "luces.h"
#include "texturas.h"
#include "modelado.h"
#include "revolucion.h"

/**
 * Handler del ratón
 */
void botonRatonPulsado(int boton, int estado, int x, int y) {
	if (boton == GLUT_LEFT_BUTTON) {
		if (estado == GLUT_DOWN) {
			botonIzquierdoPulsado = BOTON_PULSADO;
			pInicio = pFin = actualizaPunto3D(x - (w / 2), (h / 2) - y, 0.0f);
		} else if (estado == GLUT_UP) {
			botonIzquierdoPulsado = BOTON_NO_PULSADO;
			asigna(matrizActual, producto);
		}
	} else if (boton == GLUT_RIGHT_BUTTON) {
		if (estado == GLUT_DOWN) {
			botonDerechoPulsado = BOTON_PULSADO;
			pInicio = actualizaPunto3D(x, y, 0.0f);
		} else if (estado == GLUT_UP) {
			botonDerechoPulsado = BOTON_NO_PULSADO;
			asigna(matrizActual, producto);
		}
	} else if (boton == GLUT_MIDDLE_BUTTON) {
		if (estado == GLUT_DOWN) {
			botonMedioPulsado = BOTON_PULSADO;
			pInicio = actualizaPunto3D(x, y, 0.0f);
		} else if (estado == GLUT_UP) {
			botonMedioPulsado = BOTON_NO_PULSADO;
			asigna(matrizActual, producto);
		}
	}
}

/**
 * Comprobar dónde está el ratón
 */
int dentroVentana(int x, int y) {
	int dentro = DENTRO;

	if (x < 0 || y < 0 || x > w || y > h)
		dentro = FUERA;

	return (dentro);
}

/**
 * Handler movimiento del ratón
 */
void ratonMovido(int x, int y) {
	if (botonIzquierdoPulsado == BOTON_PULSADO && dentroVentana(x, y)) {
		pFin = actualizaPunto3D(x - (w / 2), (h / 2) - y, 0.0f);
		if (distintos(pInicio, pFin) == DISTINTOS) {
			calculaMatrizModeloVista(pFin, pInicio, matriz, R2);
			multiplicaMatrices(matriz, matrizActual, producto);
			glutPostRedisplay();
		}
	} else if (botonDerechoPulsado == BOTON_PULSADO && dentroVentana(x, y)) {
		pFin = actualizaPunto3D(x, y, 0.0f);
		dx += (float) (pFin.x - pInicio.x) / 200.0f;
		dy += (float) (pInicio.y - pFin.y) / 200.0f;
		pInicio = pFin;
		glutPostRedisplay();
	} else if (botonMedioPulsado == BOTON_PULSADO && dentroVentana(x, y)) {
		pFin = actualizaPunto3D(x, y, 0.0f);
		dz -= (float) (pInicio.y - pFin.y) / 200.0f;
		pInicio = pFin;
		glutPostRedisplay();
	}
}

/**
 * Detector de tecla ESC
 */
void iniciaRaton(void) {
	// Eventos de pulsacion de botones de ratón
	glutMouseFunc(botonRatonPulsado);
	// Eventos de movimiento del ratón
	glutMotionFunc(ratonMovido);
}

void Key(unsigned char tecla, int x, int y) {
	switch (tecla) {
	case 27:
		keyStates[27] = true;
		break;
	case 'l':
		keyStates['l'] = true;
		if (lightsOn)
			lightsOn = false;
		else
			lightsOn = true;
		printf("lightsOn: %s\n", lightsOn ? "true" : "false");
		break;
	case 'L':
		keyStates['L'] = true;
		if (spotLightsOn)
			spotLightsOn = false;
		else
			spotLightsOn = true;
		printf("spotLightsOn: %s\n", spotLightsOn ? "true" : "false");
		break;
	case 'a':
		keyStates['a'] = true;
		if (numTextura > 0)
			numTextura--;
		printf("numTextura: %d\n", numTextura);
		glDeleteLists(satelites.dl, 1);
		satelites.dl = glGenLists(1);
		glNewList(satelites.dl, GL_COMPILE_AND_EXECUTE);
		modeladoSatelites();
		glEndList();
		glCallList(satelites.dl);
		break;
	case 's':
		keyStates['s'] = true;
		if (numTextura < MAX_TEX - 1)
			numTextura++;
		printf("numTextura: %d\n", numTextura);
		glDeleteLists(satelites.dl, 1);
		satelites.dl = glGenLists(1);
		glNewList(satelites.dl, GL_COMPILE_AND_EXECUTE);
		modeladoSatelites();
		glEndList();
		glCallList(satelites.dl);
		break;
	}
}

/**
 * Detector de teclas especiales
 */
void SpecialKey(int tecla, int x, int y) {
	switch (tecla) {
	case GLUT_KEY_LEFT:
		keySpecialStates[GLUT_KEY_LEFT] = true;
		break;
	case GLUT_KEY_RIGHT:
		keySpecialStates[GLUT_KEY_RIGHT] = true;
		break;
	case GLUT_KEY_UP:
		keySpecialStates[GLUT_KEY_UP] = true;
		break;
	case GLUT_KEY_DOWN:
		keySpecialStates[GLUT_KEY_DOWN] = true;
		break;
	}
}

/**
 * Detector de teclas liberadas (UP)
 */
void KeyUp(unsigned char tecla, int x, int y) {
	switch (tecla) {
	case 27:
		keyStates[27] = false;
		break;
	case 'l':
		keyStates['l'] = false;
		break;
	case 'L':
		keyStates['L'] = false;
		break;
	case 'a':
		keyStates['a'] = false;
		break;
	case 's':
		keyStates['s'] = false;
		break;
	}
}

/**
 * Detector de teclas especiales (UP)
 */
void SpecialKeyUp(int tecla, int x, int y) {
	switch (tecla) {
	case GLUT_KEY_LEFT:
		keySpecialStates[GLUT_KEY_LEFT] = false;
		break;
	case GLUT_KEY_RIGHT:
		keySpecialStates[GLUT_KEY_RIGHT] = false;
		break;
	case GLUT_KEY_UP:
		keySpecialStates[GLUT_KEY_UP] = false;
		break;
	case GLUT_KEY_DOWN:
		keySpecialStates[GLUT_KEY_DOWN] = false;
		break;
	}
}

/**
 * Asocia las funciones a los eventos del teclado
 */
void inicializaTeclado(void) {
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
}

/**
 * Comprueba las teclas pulsadas y obra en consecuencia
 */
void KeyOperations(void) {
	if (keyStates[27]) {
		finaliza();
	}

	if (keySpecialStates[GLUT_KEY_LEFT] && bola.vx > -0.5f) {
		bola.vx -= 0.025f;
		printf("LEFT: ");
	}

	if (keySpecialStates[GLUT_KEY_RIGHT] && bola.vx < 0.5f) {
		bola.vx += 0.025f;
		printf("RIGHT: ");
	}

	if (keySpecialStates[GLUT_KEY_UP] && bola.vy < 0.5f) {
		bola.vy += 0.025f;
		printf("UP: ");
	}

	if (keySpecialStates[GLUT_KEY_DOWN] && bola.vy > -0.5f) {
		bola.vy -= 0.025f;
		printf("DOWN: ");
	}

	if (!keySpecialStates[GLUT_KEY_LEFT] && !keySpecialStates[GLUT_KEY_RIGHT]) {
		if (abs(bola.vx) > 0.001f)
			bola.vx *= 0.85f;
		else
			bola.vx = 0.0f;
	}

	if (!keySpecialStates[GLUT_KEY_DOWN] && !keySpecialStates[GLUT_KEY_UP]) {
		if (abs(bola.vy) > 0.001f)
			bola.vy *= 0.85f;
		else
			bola.vy = 0.0f;
	}

	// printf("Bola %.2f, %.2f, %.2f, %.2f\n", bola.va, bola.vx, bola.vy, bola.vz);
	glutPostRedisplay();
}

/**
 * Crea la ventana
 */
void inicializaVentana(int argc, char **argv) {
	// inicializar GLUT y crear ventana
	glutInit(&argc, argv);

	// Activar Z-Buffer y transparencia
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(700, 700);
	glutInitWindowPosition(200, 30);
	glutCreateWindow(argv[0]);

	// inicializar callbacks de display y redibujo
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
}

/**
 * Especifica las caracteristicas de la vista...
 */
void inicializaVista(void) {

	// Usar la Matriz de Proyección
	glMatrixMode(GL_PROJECTION);

	// Resetear la Matriz
	glLoadIdentity();

	dz = -5.0f;

	// fovy, aspecto, cerca, lejos
	// Seteamos la perspectiva correcta.
	gluPerspective(45.0f, (GLdouble) w / h, 0.1, 200.0);
	// glOrtho(-5, 5, -5, 5, -10, 10);

	// Volvemos a la Matriz ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Ponemos el modo de polígonos a rellenos para vistas tanto frontales como traseras
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Ponemos las caras frontales las que se dibujan en sentido anti-horario
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Habilita las normales
	glEnable(GL_NORMALIZE);

	// Activar test de profundidad y descartar caras ocultas
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Activa la transparencia y el modo de fusión
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Ponemos el modo de shading a suavizado
	glShadeModel(GL_SMOOTH);
}

/**
 * Borra la ventana y dibuja de nuevo
 */
void display(void) {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Borrar Buffer de profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Transformaciones derivadas de las operaciones del ratón.
	glPushMatrix();
	glTranslatef(dx, dy, dz);
	glMultMatrixf(producto);

	// Redibujar las luces;
	glPushMatrix();
	glRotatef(lightAngle, 0.0f, 1.0f, 0.0f);
	if (spotLightsOn)
		muestraLucesMoviles(true);
	else
		muestraLucesMoviles(false);
	glPopMatrix();

	if (lightsOn)
		muestraLucesFijas(true);
	else
		muestraLucesFijas(false);

	// Dibujamos la bola en su sitio
	glPushMatrix();
	glTranslatef(bola.x, bola.y, bola.z);
	glRotatef(bola.a, bola.ax, bola.ay, bola.az);
	glCallList(bola.dl);
	glPopMatrix();

	// Dibujar satélites
	glPushMatrix();
	glTranslatef(bola.x, bola.y, bola.z);
	glRotatef(satelites.phi, 0, 0, 1);
	glRotatef(satelites.theta, 0, 1, 0);
	glCallList(satelites.dl);
	glPopMatrix();

	// Llamada a la lista de dibujo del escenario.
	glPushMatrix();
	glRotatef(circuito.phi, 0, 0, 1);
	glRotatef(circuito.theta, 0, 1, 0);
	glCallList(bg.dl);
	glPopMatrix();

	// llamada a la lista de dibujo del circuito.
	glPushMatrix();
	glRotatef(circuito.phi, 0, 0, 1);
	glTranslatef(-20.0f, 0.0f, 0.0f);
	glRotatef(circuito.theta, 0, 1, 0);
	glTranslatef(20.0f, 0.0f, 0.0f);

	glCallList(circuito.dl);
	glPopMatrix();

	glPopMatrix(); // acaban las transformaciones del ratón

	// Intercambiar buffers.
	glutSwapBuffers();
}

/**
 * Dibuja los polígonos con relleno negro.
 */
void dibujarRelleno(GLuint escenario) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glCallList(escenario);
}

/**
 * Dibuja las aristas.
 */
void dibujarAristas(GLuint escenario) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_POLYGON_OFFSET_FILL);
	glColor3f(0.25f, 0.75f, 1.0f);
	glCallList(escenario);
}

/**
 * Posible cambio del tamaño de la ventana
 */
void reshape(int width, int height) {

	// Seteamos el visor para que ocupe la ventana entera
	glViewport(0, 0, width, height);

	w = width;
	h = height;
	if (w > h)
		Z = w;
	else
		Z = h;
	R2 = (w * w + h * h + Z * Z) / 4;
	inicializaVista();
}

/**
 * Distribuye el juego
 */
void iniciaDisplayLists(void) {

	bg.phi = bg.theta = bg.v_p = bg.v_t = 0.0f;

	bg.dl = glGenLists(1);
	if (bg.dl != 0) {
		glNewList(bg.dl, GL_COMPILE);
		modeladoEscenario();
		glEndList();
	}

	bola.vx = bola.vy = bola.vz = 0.0f;
	bola.ax = bola.ay = bola.az = 1.0f;
	bola.a = bola.x = bola.y = bola.z = 0.0f;
	bola.va = 5.0f;

	bola.dl = glGenLists(1);
	if (bola.dl != 0) {
		glNewList(bola.dl, GL_COMPILE);
		modeladoBolaPinchos();
		glEndList();
	}

	circuito.phi = circuito.theta = 0;
	circuito.v_p = circuito.v_t = -1.0f;

	circuito.dl = glGenLists(1);
	if (circuito.dl != 0) {
		glNewList(circuito.dl, GL_COMPILE);
		modeladoCircuito();
		glEndList();
	}

	satelites.phi = satelites.theta = 0;
	satelites.v_p = satelites.v_t = 2.0f;

	satelites.dl = glGenLists(1);
	if (satelites.dl != 0) {
		glNewList(satelites.dl, GL_COMPILE);
		modeladoSatelites();
		glEndList();
	}
}

void update(int i) {
	// lo primero, actualizar las variables en función del teclado
	KeyOperations();

	// actualizar los valores
	bola.a += bola.va;
	bola.x += bola.vx;
	bola.y += bola.vy;
	bola.z += bola.vz;

	circuito.theta += circuito.v_t;
	circuito.phi += circuito.v_p;

	satelites.theta += satelites.v_t;
	satelites.phi += satelites.v_p;

	// actualizar angulo de luces
	lightAngle += 8.0f;
	if (lightAngle >= 360)
		lightAngle = 0;

	// rellamada
	glutTimerFunc(20, update, 0);
}

/**
 * Inicia el programa.
 */
int main(int argc, char** argv) {
	// textura inicial de los satélites
	numTextura = 8;

	// inicializar glut y ventana
	inicializaVentana(argc, argv);
	printf("Ventana OK\n");

	// registrar callbacks
	inicializaTeclado();
	printf("Teclado OK\n");
	iniciaRaton();
	printf("Ratón OK\n");

	inicializaVista();
	printf("Vista OK\n");
	iniciaLuces();
	printf("Luces OK\n");
	inicializaTexturas();
	printf("Texturas OK\n");
	iniciaDisplayLists();
	printf("DisplayList OK\n");

	// Setea la función de update para el procesado de teclado
	glutTimerFunc(20, update, 0);
	printf("TimerFunc OK\n");

	// entrar en el ciclo de proceso de eventos de GLUT
	printf("Entrando en MainLoop...\n");
	glutMainLoop();
	return (1);
}

/**
 * Código para liberar memoria antes de salir del programa
 */
void finaliza(void) {
	finalizaTexturas();
	exit(0);
}
