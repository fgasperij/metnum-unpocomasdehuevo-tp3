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

	vector<double> xs = obtenerXs(trayectoriaActual);
    vector<double> ys = obtenerYs(trayectoriaActual);

    // Me quedo con la ultima seria de mediciones decrecientes.
    vector<double> aux = xs;
    reverse(aux.begin(), aux.end());
    unsigned int cantCrecientes = 0;
    for(unsigned int i = 0; i < aux.size() ; i++){
        if(i+1 < aux.size() && aux[i] <= aux[i+1] ){
            cantCrecientes++;
        }
        else if(i+1 == aux.size()){cantCrecientes++;}
        else{break;}
    }

    // Las aproximaciones para los distintos polinomios.
	vector<aproximacion> aproximaciones(0);

    // Con grado 0, la aproximacion es constante. Muy poco util. Aunque cuando hay un solo punto a considerar quizas sea lo mejor.
    aproximaciones.push_back( aproximacion(ys[ys.size()-1]));

    // El resto de las aproximaciones hasta polinomios de hasta grado grados. El grado maximo tambien queda definido
    // por la cantidad de puntos actuales.

    // Esta cosa fea es para que solo considere los ultimos CANT_MEDICIONES puntos positivos, invierto, me quedo con los primeros y vuelvo a invertir.
    int puntosAConsiderar = min(CANT_MEDICIONES, min((int) trayectoriaActual.size(), (int) cantCrecientes));
    vector<double> xss = xs;
    reverse(xss.begin(), xss.end());
    xss.resize(puntosAConsiderar);
    reverse(xss.begin(), xss.end());
    vector<double> yss = ys;
    reverse(yss.begin(), yss.end());
    yss.resize(puntosAConsiderar);
    reverse(yss.begin(), yss.end());
    // Aproximo con polinomios de hasta grado i. El grado debe ser menor a puntosAConsiderar para no interpolar.
    unsigned int grados = min(MAX_GRADO, puntosAConsiderar-1);
	for (unsigned int i = 1; i < grados; i++) {

		vector<double> coeficientesMinimizadoresXs = minimizarConGrado(xss, i, instanteActual);

		vector<double> coeficientesMinimizadoresYs = minimizarConGrado(yss, i, instanteActual);

		coeficientesMinimizadoresXs[0] -= X_DEL_ARCO;

		// BISECCION | NEWTON
		// Si boost devuelve error, omito el valor.
		try{
            double tiempoGol = calcularRaiz(coeficientesMinimizadoresXs, BISECCION);
            aproximaciones.push_back( aproximacion(true, eval(coeficientesMinimizadoresYs, tiempoGol)));
		}
		catch(...){
            aproximaciones.push_back(aproximacion(false, 0));
		}
	}

	// Estimaciones dadas popr los polinomios.
    vector<double> estimacionPorPolinomio (0);
	for(unsigned int i = 0;i < aproximaciones.size(); i++){
        	estimacionPorPolinomio.push_back(aproximaciones[i].valor);
	}
	estimaciones.push_back(estimacionPorPolinomio);


//	decidirEnBaseATodasLasAproximaciones(aproximaciones);

// Por el momento me quedo con la ultima aproximacion valida. Deberia de ser la mas precisa.
    double aproximacionFinal = 0;
    if(aproximaciones.size() == 1){return aproximaciones[0].valor;}
    double cantAproxs = 0;
	for(unsigned int i = 1; i < aproximaciones.size(); i++){
        if(aproximaciones[i].valida){
            aproximacionFinal = aproximaciones[i].valor;
            cantAproxs++;
        }
	}


	return aproximacionFinal/1;

}

/** TODO:
 Guardar rastro de los valores reales y las aproximaciones y comparar el error, para asi poder
 determinar que polinomio aproxima mejor a la funcion. Esto va a permitir deducir si la trayectoria
 de la pelota es lineal, cuadratica, cubica o lo que sea.
 Parcialmente hecho con "estimaciones", falta ver que polinomio aproxima mejor.
*/

int Disparo::devErrores(){return errores;}
