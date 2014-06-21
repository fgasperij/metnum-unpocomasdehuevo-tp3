#include "Disparo.h"
#include "CMP.h"
#include "misc.h"
#include "zeros.h"
#include "display.h"
#include "io.h"
#include "global.h"



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


double Disparo::aproximarConCMP(){
    // Parametros: Los cargo desde la configuracion global.
    unsigned int grados = (unsigned int) conf.max_grado;
    int cant_mediciones = conf.cant_mediciones;

	vector<Posicion> trayectoriaActual = devolverTrayectoria();

	vector<double> xs = obtenerXs(trayectoriaActual);
    vector<double> ys = obtenerYs(trayectoriaActual);

    // Me quedo con la ultima serie de mediciones decrecientes.
    vector<double> aux = xs;
    reverse(aux.begin(), aux.end());
    unsigned int cantCrecientes = contarPrimCrecientes(aux);

    // Las aproximaciones para los distintos polinomios.
	vector<aproximacion> aproximaciones(0);

    // Con grado 0, la aproximacion es constante. Muy poco util. Aunque cuando hay un solo punto a considerar quizas sea lo mejor.
    aproximaciones.push_back( aproximacion(ys[ys.size()-1]));


    // Agarro los ultimos puntos de las mediciones.
    int puntosAConsiderar = min(cant_mediciones, (int) cantCrecientes);
    vector<double> xss = ultimos(xs, puntosAConsiderar);
    vector<double> yss = ultimos(ys, puntosAConsiderar);


    // Si hay un solo punto no calculo ningun polinomio.
    if(puntosAConsiderar < 2){grados = conf.max_grado;}
    // El grado esta acotado por los puntos a considerar.
    grados = min(puntosAConsiderar, (int) grados);

	for (unsigned int i = 1; i < grados; i++) {

		vector<double> coeficientesMinimizadoresXs = minimizarConGrado(xss, i, instanteActual);

		vector<double> coeficientesMinimizadoresYs = minimizarConGrado(yss, i, instanteActual);

		coeficientesMinimizadoresXs[0] -= X_DEL_ARCO;

		// BISECCION | NEWTON
		// Si boost devuelve error, pruebo valores hasta hallar el valor..
		try{
            double tiempoGol = calcularRaiz(coeficientesMinimizadoresXs, BISECCION);
            aproximaciones.push_back( aproximacion(true, eval(coeficientesMinimizadoresYs, tiempoGol)));
		}
		catch(...){
//		    double pred_y = probarValores(coeficientesMinimizadoresXs, coeficientesMinimizadoresYs, instanteActual);
//		    if(pred_y > 0){aproximaciones.push_back(aproximacion(true, pred_y));}
            aproximaciones.push_back(aproximacion(false, 0));
		}
	}

// Por el momento me quedo con la ultima aproximacion valida. Deberia de ser la mas precisa.
    double aproximacionFinal = 0;
    if(aproximaciones.size() == 1){return aproximaciones[0].valor;}
	for(unsigned int i = 1; i < aproximaciones.size(); i++){
        if(aproximaciones[i].valida){
            aproximacionFinal = aproximaciones[i].valor;
        }
	}
	return aproximacionFinal;
}

double Disparo::estimarPorDondePasa() {
    return aproximarConCMP();
}

/** TODO:
 Guardar rastro de los valores reales y las aproximaciones y comparar el error, para asi poder
 determinar que polinomio aproxima mejor a la funcion. Esto va a permitir deducir si la trayectoria
 de la pelota es lineal, cuadratica, cubica o lo que sea.
 Parcialmente hecho con "estimaciones", falta ver que polinomio aproxima mejor.
*/


