#include "zeros.h"
#include "boost/tuple/tuple.hpp"
#include <boost/bind.hpp>

#define ITER 50

vector<double> obtenerXs(vector<Posicion>& trayectoria){
	vector<double> res;
	for(unsigned i = 0; i < trayectoria.size(); ++i) {
		res.push_back(trayectoria[i].x);
	}

	return res;
}

vector<double> obtenerYs(vector<Posicion>& trayectoria){
	vector<double> res;
	for(unsigned i = 0; i < trayectoria.size(); ++i) {
		res.push_back(trayectoria[i].y);
	}

	return res;
}

double calcularRaiz(vector<double>& coeficientes, int metodo) {
	if (metodo == BISECCION) {
		double a = 0;
		double b = a + INTERVALO_BISECCION;
		pair<double,double> res = bisect(bind(eval, coeficientes, _1), a, b, TerminationCondition());
		return (res.first + res.second)/2;
	}

	if (metodo == NEWTON) {
		double min = coeficientes.size()-1, max = min + INTERVALO_BISECCION;
		double x0 = (min+max)/2;
		int digits = 10;
		return newton_raphson_iterate(bind(evalNewton, coeficientes, _1), x0, min, max, digits);
	}

	return 0;
}

double calcularRaizLagrange(vector<double>& mediciones, int instanteActual) {
    double a = 0;
    double b = a + INTERVALO_BISECCION;
    pair<double,double> res = bisect(bind(evalLagrange, mediciones, instanteActual, _1), a, b, TerminationCondition());
    return (res.first + res.second)/2;
}

double eval(vector<double> &coefs, double x) {
	double res = coefs[0];
	for(unsigned i = 0; i < coefs.size(); ++i) {
		res += coefs[i]*pow(x, (int) i);
	}
	return res;
}

double LNK(double x, int k, int start, int end){
    double res = 1;
    for(int i = start; i < end; i++){
        if(i != k){
            res = res*(x - (double) i)/((double) k-i);
        }
    }
    return res;
}

double evalLagrange(vector<double> & mediciones, int instanteActual, double x) {
    double res = 0;
    unsigned int n = mediciones.size();
    unsigned int start = (unsigned int) instanteActual - n;
	for(unsigned int i = 0; i < n; ++i) {
		res += mediciones[i]*LNK(x, i+start, start, instanteActual);
	}
    res -= X_DEL_ARCO;
	return res;
}

tuple<double,double> evalNewton(vector<double> &coefs, double x) {
	tuple<double,double> ret;

	double resPol = coefs[0];
	for(unsigned int i = 1; i < coefs.size(); ++i) {
		resPol += coefs[i]*pow(x,(int) i);
	}
	get<0>(ret) = resPol;

	double resDer = coefs[1];
	for(unsigned i = 2; i < coefs.size(); ++i) {
		resDer += i*coefs[i]*pow(x, (int) i-1);
	}
	get<1>(ret) = resDer;

	return ret;
}

// Va calculando raices, probando con valores de t siguientes hasta ITER. Si no encuentra devuelve un valor negativo.
double probarValores(vector<double>& coeficientes_x, vector<double>& coeficientes_y, int instanteActual){
    for(int i = instanteActual; i < ITER + instanteActual; i++){
        int pred_x = eval(coeficientes_x, i);
        if(pred_x < X_DEL_ARCO){
            return eval(coeficientes_y, i);
        }
    }
    // Si
    return -1;
}

// Va calculando raices, probando con valores de t siguientes hasta ITER. Si no encuentra devuelve un valor negativo.
double probarValoresLagrange(vector<double>& mediciones_x, vector<double>& mediciones_y, int instanteActual){
    for(int i = instanteActual; i < ITER + instanteActual; i++){
        int pred_x = evalLagrange(mediciones_x, instanteActual, i);
        if(pred_x < X_DEL_ARCO){
            return evalLagrange(mediciones_y, instanteActual, i);
        }
    }
    // Si
    return -1;
}
