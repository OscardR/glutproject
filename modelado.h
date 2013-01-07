#ifndef MODELADO_H
#define MODELADO_H

#define	M	50

GLuint numTextura;

// Helpers
float dameX(float R, int N, int n);
float dameZ(float R, int N, int n);
void anillo(float R, float y, int N);
void tira(float R1, float R2, float R3, float y1, float y2, float y3, int P);
void tapa(float R, float y, int N, int flip);
Punto3D vertice(float R1, float y1, int P, int N);
Vector3D normal(float R1, float R2, float y1, float y2, int P, int N);

// Primitivas y helpers
float fCono(float y);
void conoAlambre(int N);

float fCilindro(float y);
void cilindroAlambre(int N);

float fEsfera(float y);
void esferaAlambre(int N);

float fJarron(float y);

// Funciones de dibujo
void formaAlambre(float H, int N, float (*f)(float y));
void formaSolida(float H, int N, int P, float (*f)(float y));

// Sólidos
void conoSolido(int N, int P);
void cilindroSolido(int N, int P);
void esferaSolida(int N, int P);
void jarronSolido(int N, int P);
void cuboSolido(float W, float H, float n);
void bolaPinchosSolida(int n_puas, float factor);
void toroideSolido(float R, float r, int N, int P);

// Objetos de modelado
void modeladoEscenario(void);
void modeladoCircuito(void);
void modeladoSatelites(void);
void modeladoBolaPinchos(void);

#endif
