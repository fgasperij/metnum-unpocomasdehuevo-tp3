#include "Disparo.h"
#include "CMP.h"
#include "zeros.h"
#include "display.h"
#include "io.h"


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
	return instanteActual > (int) trayectoria.size()-1;
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

	// Cantidad de puntos medidos hasta el instante actual.
	unsigned int cantPuntosActuales = trayectoriaActual.size();

	// En el primer instante devuelvo lo mismo.
    //if(cantPuntosActuales == 1){return trayectoria[0].y;}

    unsigned int grados = 3;    // Uso polinomios de hasta grado 2.

    // Las aproximaciones para los distintos polinomios.
	vector<aproximacion> aproximaciones(grados+1);

	vector<double> xs = obtenerXs(trayectoriaActual);
    vector<double> ys = obtenerYs(trayectoriaActual);

    // Me quedo con la ultima seria de mediciones crecientes.
    vector<double> aux = xs;
    reverse(aux.begin(), aux.end());
    vector<double> xsp;
    for(unsigned int i = 0; i < aux.size() ; i++){
        if(i+1 < aux.size() && aux[i] <= aux[i+1] ){
            xsp.push_back(aux[i]);
        }
        else if(i+1 == aux.size()){xsp.push_back(aux[i]);}
        else{break;}
    }
    reverse(xsp.begin(), xsp.end());

    // Con grado 0, la aproximacion es constante. Muy poco util. Aunque cuando hay un solo punto a considerar quizas sea lo mejor.
    aproximaciones[0] = ys[ys.size()-1];
    // El resto de las aproximaciones hasta polinomios de hasta grado grados. El grado maximo tambien queda definido
    // por la cantidad de puntos actuales.
	for (unsigned int i = 1; i <= grados && i < cantPuntosActuales && i < xsp.size(); i++) {

        // Esta cosa fea es para que solo considere los ultimos puntos, invierto, me quedo con los primeros y vuelvo a invertir.
        vector<double> xss = xs;
        reverse(xss.begin(), xss.end());
        xss.resize(i+1);
        reverse(xss.begin(), xss.end());

		vector<double> coeficientesMinimizadoresXs = minimizarConGrado(xss, i, instanteActual);

        vector<double> yss = ys;
        reverse(yss.begin(), yss.end());
        yss.resize(i+1);
        reverse(yss.begin(), yss.end());

		vector<double> coeficientesMinimizadoresYs = minimizarConGrado(yss, i, instanteActual);

		coeficientesMinimizadoresXs[0] -= X_DEL_ARCO;

		// BISECCION | NEWTON
		// Si boost devuelve error, omito el valor.
		try{
            double tiempoGol = calcularRaiz(coeficientesMinimizadoresXs, BISECCION);
            aproximaciones[i] = aproximacion (true,eval(coeficientesMinimizadoresYs, tiempoGol));
		}
		catch(...){
            aproximaciones[i] = aproximacion(false, 0);
		}
	}

//	double aproximacionFinal = decidirEnBaseATodasLasAproximaciones(aproximaciones);

// Por el momento me quedo con la ultima aproximacion valida. Deberia de ser la mas precisa.
    double aproximacionFinal = 0;
	for(unsigned int i = 0; i < aproximaciones.size(); i++){
        if(aproximaciones[i].valida){
            aproximacionFinal = aproximaciones[i].valor;
        }
	}


	return aproximacionFinal;

}
