#ifndef ZEROS_H
#define ZEROS_H

#include "boost/math/tools/roots.hpp"
#include <cmath>
#include <tuple>
#include "defines.h"

using namespace boost::math::tools;

struct TerminationCondition {
	bool operator()(double min, double max) {
		return fabs(max-min) <= EPS;
	}
};

vector<double> obtenerXs(vector<Posicion>& trayectoria);
vector<double> obtenerYs(vector<Posicion>& trayectoria);

double calcularRaiz(vector<double>& coeficientes, int metodo = BISECCION);
double eval(vector<double> &coefs, double x);
tuple<double,double> evalNewton(vector<double> &coefs, double x);

#endif
