#include "Disparo.h"
#include "CMP.h"

void Disparo::tic(){instanteActual++;}

void Disparo::reset(){instanteActual = 0;}

void Disparo::setearFlagTest(bool value){flag_test = value;}

vector<Posicion> Disparo::trayectoria() {
	vector<Posicion> trayectoriaActual (instanteActual);
	for(int i = 0; i =< instanteActual; i++) {
		vector.push_back(trayectoria[i]);
	}

	return trayectoriaActual;
}

bool Disparo::detenido() {
	return instanteActual > trayectoria.size();
}

double Disparo::estimarPorDondePasa() {
	vector<Posicion> trayectoriaActual = trayectoria();
	
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
	double aproximaciones[grados]; 

	for (int i = 0; i < grados; i++) {
		vector<double> xs = obtenerXs(trayectoriaActual);	
		double coeficientesMinimizadoresXs = minimizarConGrado(xs, i);

		double ys = obtenerYs(trayectoriaActual);	
		double coeficientesMinimizadoresYs = minimizarConGrado(ys, i);
		
		Polinomio polinomioMinimizadorX (coeficientesMinimizadoresXs);
		Polinomio polinomioMinimizadorY (coeficientesMinimizadoresXs);

		double tiempoGol = boostGetRoot(polinomioMinimizadorX - X_DEL_ARCO);

		aproximaciones[i] = polinomioMinimizadorY.evaluar(tiempoGol);
	}
	
	double aproximacionFinal = decidirEnBaseATodasLasAproximaciones(aproximaciones);

	return aproximacionFinal;
}
