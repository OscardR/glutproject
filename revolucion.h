#ifndef REVOLUCION_H
#define REVOLUCION_H

#define BOTON_PULSADO 1
#define BOTON_NO_PULSADO 0

#define DENTRO 1
#define FUERA 0

// estructura que envuelve datos de objetos que rotan
typedef struct {
	float phi; // ángulo de posición en sección
	float theta; // ángulo de posición en recorrido
	float v_p; // velocidad phi
	float v_t; // velocidad theta
	int dl; // DisplayList
} ROTABLE;
ROTABLE circuito;
ROTABLE bg;
ROTABLE satelites;

// estructura para la bola
typedef struct {
	float vx, vy, vz;
	float x, y, z;
	float ax, ay, az;
	float va;
	float a;
	int dl; // DisplayList
} BOLA;
BOLA bola;

// ángulo de las luces móviles
float lightAngle = 0.0f;
bool spotLightsOn = true;
bool lightsOn = false;

int botonIzquierdoPulsado = BOTON_NO_PULSADO;
int botonDerechoPulsado = BOTON_NO_PULSADO;
int botonMedioPulsado = BOTON_NO_PULSADO;
int auxiliarPulsada;

// vectores para los estados de las teclas
bool keyStates[256];
bool keySpecialStates[256];

// variables para el manejo de la cámara
Punto3D pInicio, pFin;
float alfa = 0.0f;
float beta = 0.0f;
float dx, dy, dz;
float w, h;
float Z; // La profundidad de las esquinas de la ventana
float R2; // El radio al cuadrado
float matriz[16]; // La matriz de rotacion
float matrizActual[16] = { 1.0f, 0.0f, 0.0f, 0.0f, //Ojo que las matrices se definen por columnas
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

float producto[16] = { 1.0f, 0.0f, 0.0f, 0.0f, //Ojo que las matrices se definen por columnas
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

void display(void);
void Key(unsigned char, int, int);
void KeyUp(unsigned char, int, int);
void KeySpecial(int key, int x, int y);
void KeySpecialUp(int key, int x, int y);
void KeyOperations(void);

void iniciaRaton(void);
void inicializaTeclado(void);
void inicializaVista(void);
void inicializaVentana(int argc, char **argv);
void iniciaLuces(void);
void inicializaIluminacion(void);
void iniciaDisplayLists(void);
void reshape(int width, int height);

void botonRatonPulsado(int boton, int estado, int x, int y);
void ratonMovido(int x, int y);
int dentroVentana(int x, int y);

void finaliza(void);
#endif
