#include <math.h>
#include "matematicas.h"

/******************************************************************************/
/* Devuelve el vector de posici�n de un punto                                 */
/* Parametros --> Punto3D p: el punto a partir del que se construye el vector */
/* Salida ------> El vector                                                   */
/******************************************************************************/
Vector3D vectorPosicion(Punto3D p) {
	Vector3D res;

	res.a = p.x;
	res.b = p.y;
	res.c = p.z;

	return (res);
}

/******************************************************************************/
/* Calcula un vector desde un punto inicial a uno final                       */
/* Parametros --> Punto3D p: el punto inicial                                 */
/*                Punto3D q: el punto final                                   */
/* Salida ------> El vector entre los puntos                                  */
/******************************************************************************/
Vector3D vector(Punto3D p, Punto3D q) {
	Vector3D res;

	res.a = q.x - p.x;
	res.b = q.y - p.y;
	res.c = q.z - p.z;
	return (res);
}

/******************************************************************************/
/* Actualiza las coordenadas de un punto                                      */
/* Parametros --> float x: la nueva coordenada x del punto                    */
/*                float y: idem para la y                                     */
/*                float z: idem para la z                                     */
/* Salida ------> El nuevo punto actualizado                                  */
/******************************************************************************/
Punto3D actualizaPunto3D(float x, float y, float z) {
	Punto3D p;

	p.x = x;
	p.y = y;
	p.z = z;

	return (p);
}

/******************************************************************************/
/* Actualiza las componentes de un vector                                     */
/* Parametros --> float a: la nueva componente a del punto                    */
/*                float b: idem para la b                                     */
/*                float c: idem para la c                                     */
/* Salida ------> El nuevo vector actualizado                                 */
/******************************************************************************/
Vector3D actualizaVector3D(float a, float b, float c) {
	Vector3D v;

	v.a = a;
	v.b = b;
	v.c = c;

	return (v);
}

/******************************************************************************/
/* Producto escalar de dos vectores                                           */
/* Parametros --> Vector3D v: uno de los vectores                             */
/*                Vector3D w: el otro vector                                  */
/* Salida ------> El valor del producto escalar                               */
/******************************************************************************/
float productoEscalar(Vector3D v, Vector3D w) {
	float resultado = 0.0f;

	resultado = (v.a * w.a) + (v.b * w.b) + (v.c * w.c);

	return (resultado);
}

/******************************************************************************/
/* Producto vectorial de dos vectores                                         */
/* Parametros --> Vector3D v: uno de los vectores                             */
/*                Vector3D w: el otro vector                                  */
/* Salida ------> El vector resultante                                        */
/******************************************************************************/
Vector3D productoVectorial(Vector3D v, Vector3D w) {
	float longitud;
	Vector3D res;

	res.a = v.b * w.c - (v.c * w.b);
	res.b = v.c * w.a - (v.a * w.c);
	res.c = v.a * w.b - (v.b * w.a);
	longitud = (float) sqrt(
			(res.a * res.a) + (res.b * res.b) + (res.c * res.c));
	if (longitud != 0) {
		res.a /= longitud;
		res.b /= longitud;
		res.c /= longitud;
	}

	return (res);
}

/******************************************************************************/
/* Normaliza un vector                                                        */
/* Parametros --> Vector3D v: el vector que se va a normalizar                */
/* Salida ------> El vector normalizado                                       */
/******************************************************************************/
Vector3D normaliza(Vector3D v) {
	float longitud = (float) sqrt(productoEscalar(v, v));

	if (longitud != 0) {
		v.a /= longitud;
		v.b /= longitud;
		v.c /= longitud;
	}

	return (v);
}

/******************************************************************************/
/* Comprueba si dos puntos son distintos                                      */
/* Parametros --> Punto3D p: uno de los puntos                                */
/*                Punto3D q: el otro                                          */
/* Salida ------> DISTINTOS o IGUALES                                         */
/******************************************************************************/
int distintos(Punto3D p, Punto3D q) {
	int distintos = IGUALES;

	if (p.x != q.x || p.y != q.y || p.z != q.z)
		distintos = DISTINTOS;

	return distintos;
}

/******************************************************************************/
/* Calcula la matriz modelo-vista a partir de dos puntos de agarre y el       */
/* radio de la esfera virtual                                                 */
/* Parametros --> Punto3D pInicio: punto inicial de agarre.                   */
/*                Punto3D pFin: punto final de agarre.                        */
/*                matriz[]: la matriz que se calcula                          */
/*                float R2: el cuadrado del radio de la esfera virtual        */
/* Salida ------> Ninguna                                                     */
/******************************************************************************/
void calculaMatrizModeloVista(Punto3D pInicio, Punto3D pFin, float matriz[],
		float R2) {
	float z = (float) sqrt(
			R2 - ((pInicio.x * pInicio.x) + (pInicio.y * pInicio.y)));
	Vector3D vInicio = actualizaVector3D(pInicio.x, pInicio.y, z);
	Vector3D vFin, normal;
	float coseno;
	float angulo;

	vInicio = normaliza(vInicio);
	z = (float) sqrt(R2 - ((pFin.x * pFin.x) + (pFin.y * pFin.y)));
	vFin = actualizaVector3D(pFin.x, pFin.y, z);
	vFin = normaliza(vFin);
	normal = productoVectorial(vFin, vInicio);
	normal = normaliza(normal);
	coseno = productoEscalar(vInicio, vFin);
	if (coseno > 1.0f)
		coseno = 1.0f;
	else if (coseno < -1.0f)
		coseno = -1.0f;
	angulo = (float) acos(coseno);
	angulo *= 5.0f;
	coseno = (float) cos(angulo);
	matrizRotacion(normal.a, normal.b, normal.c, coseno, matriz);
}

/******************************************************************************/
/* Calcula la matriz de rotacion en torno a un eje cualquiera                 */
/* Parametros --> float rx, ry, rz: el eje de rotacion                        */
/*                float coseno: el coseno de rotacion                         */
/*                float matriz[]: la matriz donde se devuelve la rotacion     */
/* Salida ------> Ninguna                                                     */
/******************************************************************************/
void matrizRotacion(float rx, float ry, float rz, float coseno, float matriz[]) {
	float seno = (float) sqrt(1.0f - (coseno * coseno));
	float vers = 1.0f - coseno;

	matriz[0] = (rx * rx * vers) + coseno;
	matriz[1] = (rx * ry * vers) + (rz * seno);
	matriz[2] = (rx * rz * vers) - (ry * seno);
	matriz[4] = (rx * ry * vers) - (rz * seno);
	matriz[5] = (ry * ry * vers) + (coseno);
	matriz[6] = (ry * rz * vers) + (rx * seno);
	matriz[8] = (rx * rz * vers) + (ry * seno);
	matriz[9] = (ry * rz * vers) - (rx * seno);
	matriz[10] = (rz * rz * vers) + (coseno);
	matriz[3] = matriz[7] = matriz[11] = 0.0f;
	matriz[12] = matriz[13] = 0.0f;
	matriz[14] = 0.0f;
	matriz[15] = 1.0f;
}

/******************************************************************************/
/* Multiplica dos matrices de tama�o 4x4                                      */
/* Parametros --> float m1[]: una de las matrices.                            */
/*                float m2[]: la otra.                                        */
/*                floar resultado[]=m1[]*m2[].                                */
/******************************************************************************/
void multiplicaMatrices(float m1[], float m2[], float resultado[]) {
	float longitud;

	resultado[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2]
			+ m1[12] * m2[3];
	resultado[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6]
			+ m1[12] * m2[7];
	resultado[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10]
			+ m1[12] * m2[11];
	resultado[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14]
			+ m1[12] * m2[15];
	resultado[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2]
			+ m1[13] * m2[3];
	resultado[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6]
			+ m1[13] * m2[7];
	resultado[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10]
			+ m1[13] * m2[11];
	resultado[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14]
			+ m1[13] * m2[15];
	resultado[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2]
			+ m1[14] * m2[3];
	resultado[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6]
			+ m1[14] * m2[7];
	resultado[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10]
			+ m1[14] * m2[11];
	resultado[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14]
			+ m1[14] * m2[15];
	resultado[3] = 0.0f;
	resultado[7] = 0.0f;
	resultado[11] = 0.0f;
	resultado[15] = 1.0f;

	longitud = (float) sqrt(
			resultado[0] * resultado[0] + resultado[1] * resultado[1]
					+ resultado[2] * resultado[2]);
	resultado[0] /= longitud;
	resultado[1] /= longitud;
	resultado[2] /= longitud;

	longitud = (float) sqrt(
			resultado[4] * resultado[4] + resultado[5] * resultado[5]
					+ resultado[6] * resultado[6]);
	resultado[4] /= longitud;
	resultado[5] /= longitud;
	resultado[6] /= longitud;

	longitud = (float) sqrt(
			resultado[8] * resultado[8] + resultado[9] * resultado[9]
					+ resultado[10] * resultado[10]);
	resultado[8] /= longitud;
	resultado[9] /= longitud;
	resultado[10] /= longitud;
}

/******************************************************************************/
/* Copia una matriz sobre otra.                                               */
/* Parametros --> float m1[]: matriz destino.                                 */
/*                float m2[]: matriz origen.                                  */
/* Salida ------> Ninguna.                                                    */
/******************************************************************************/
void asigna(float m1[], float m2[]) {
	int i;

	for (i = 0; i < 16; i++)
		m1[i] = m2[i];
}

/******************************************************************************/
/* Multiplica una matriz por un vector.                                       */
/* Parametros --> float producto[]: la matriz que multiplica                  */
/*                float Vector3D v: el vector que es multiplicado             */
/* Salida ------> Vector3D: el resultado de la multiplicacion                 */
/******************************************************************************/
Vector3D multiplicaMatrizVector(float producto[], Vector3D v) {
	Vector3D resultado;

	resultado.a = producto[0] * v.a + producto[4] * v.b + producto[8] * v.c;
	resultado.b = producto[1] * v.a + producto[5] * v.b + producto[9] * v.c;
	resultado.c = producto[2] * v.a + producto[6] * v.b + producto[10] * v.c;

	return (resultado);
}
