#include "Disparo.h"
#include "CMP.h"
#include "misc.h"

void Disparo::tic(){instanteActual++;}

void Disparo::reset(){instanteActual = 0;}

void Disparo::setearFlagTest(bool value){flag_test = value;}

/** CORREGIR ESTO */
vector<Posicion> Disparo::devolverTrayectoria() {
	vector<Posicion> trayectoriaActual (instanteActual);
	for(int i = 0; i <= instanteActual; i++) {
		vector.push_back(trayectoria[i]);
	}

	return trayectoriaActual;
}

bool Disparo::detenido() {
	return instanteActual > (int) trayectoria.size();
}

double Disparo::estimarPorDondePasa() {
	vector<Posicion> trayectoriaActual = devolverTrayectoria();

	/**
	 * Sólo aproximamos desde grado 0 hasta el grado anterior al que nos provee
	 * un polinomio interpolador porque las mediciones tienen errores.
	 *
	 * Ejemplo:
	 * 		Tengo 3 mediciones (x1, y1) (x2, y2) (x3, y3)
	 *   	trayectoriaActual.size() = 3 ---> trayectoriaActual.size()-1 = 2
	 *    	Aproximo con grado 0 y 1. Grado 2 ya me daría un interpolador.
	 */
	int grados = trayectoriaActual.size()-1;
	vector<aproximacion> aproximaciones(grados);

	for (int i = 0; i < grados; i++) {
		vector<double> xs = obtenerXs(trayectoriaActual);
		double coeficientesMinimizadoresXs = minimizarConGrado(xs, i);

		double ys = obtenerYs(trayectoriaActual);
		double coeficientesMinimizadoresYs = minimizarConGrado(ys, i);

		coeficientesMinimizadoresXs[0] -= X_DEL_ARCO;
		// BISECCION | NEWTON
		double tiempoGol = calcularRaiz(coeficientesMinimizadoresXs, BISECCION);

		aproximaciones[i] = eval(coeficientesMinimizadoresYs, tiempoGol);
	}

/** ATENCION: DESCOMENTAR ESTO */
//	double aproximacionFinal = decidirEnBaseATodasLasAproximaciones(aproximaciones);

//	return aproximacionFinal;
    return 0;
}
