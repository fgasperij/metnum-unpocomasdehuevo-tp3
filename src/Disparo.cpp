#include "Disparo.h"
#include "CMP.h"
#include "zeros.h"

void Disparo::tic(){instanteActual++;}

void Disparo::reset(){instanteActual = 0;}

void Disparo::setearFlagTest(bool value){flag_test = value;}

vector<Posicion> Disparo::devolverTrayectoria() {
	vector<Posicion> trayectoriaActual;

	for(int i = 0; i < instanteActual; i++) {
		trayectoriaActual.push_back(trayectoria[i]);
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

	// En el primer instante devuelvo lo mismo.
    if(grados == 0){return trayectoria[0].y;}

	vector<aproximacion> aproximaciones(grados);

	vector<double> xs = obtenerXs(trayectoriaActual);
    vector<double> ys = obtenerYs(trayectoriaActual); // double x vector<double>



    // Con grado 0, la aproximacion es constante.
    aproximaciones[0] = xs[xs.size()-1];
	for (int i = 1; i < grados; i++) {

		vector<double> coeficientesMinimizadoresXs = minimizarConGrado(xs, i); // double x vector<double>


		vector<double> coeficientesMinimizadoresYs = minimizarConGrado(ys, i); // double x vector<double>

		coeficientesMinimizadoresXs[0] -= X_DEL_ARCO;
		// BISECCION | NEWTON
		try{
            double tiempoGol = calcularRaiz(coeficientesMinimizadoresXs, BISECCION);
            aproximaciones[i] = aproximacion (eval(coeficientesMinimizadoresYs, tiempoGol));
		}
		catch(...){
            aproximaciones[i] = aproximacion(false, 0);
		}
	}

//	double aproximacionFinal = decidirEnBaseATodasLasAproximaciones(aproximaciones);

// Por el momento me quedo con la ultima aproximacion valida.
    double aproximacionFinal = 0;
	for(unsigned int i = 0; i < aproximaciones.size(); i++){
        if(aproximaciones[i].valida){
            aproximacionFinal = aproximaciones[i].valor;
        }
	}


	return aproximacionFinal;

}
