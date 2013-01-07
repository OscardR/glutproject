#ifndef MATEMATICAS_H
#define MATEMATICAS_H

#define IGUALES 0
#define DISTINTOS 1

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

typedef struct {
	float x, y, z;
} Punto3D;

typedef struct {
	float a, b, c;
} Vector3D;

Vector3D productoVectorial(Vector3D v, Vector3D w);
Vector3D vector(Punto3D p, Punto3D q);
Vector3D vectorPosicion(Punto3D p);
float productoEscalar(Vector3D v, Vector3D w);
Punto3D actualizaPunto3D(float x, float y, float z);
Vector3D actualizaVector3D(float a, float b, float c);
void calculaMatrizModeloVista(Punto3D pInicio, Punto3D pFin, float matriz[],
		float R2);
void multiplicaMatrices(float m1[], float m2[], float resultado[]);
int distintos(Punto3D p, Punto3D q);
void asigna(float m1[], float m2[]);
Vector3D multiplicaMatrizVector(float producto[], Vector3D v);
void matrizRotacion(float rx, float ry, float rz, float angulo, float matriz[]);
Vector3D normaliza(Vector3D v);

#endif
