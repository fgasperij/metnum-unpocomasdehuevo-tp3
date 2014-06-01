#ifndef ARQUERO_H
#define ARQUERO_H

#include "defines.h"
#include <string>

class Arquero{
	public:
		Arquero();
		Arquero(string n, double inf, double sup, double posicionInicial) 
		: nombre(n), limiteInferior(inf), limiteSuperior(sup), posicionActual(posicionInicial) {}
		void atajar(Posicion);

	private:
		vector<double> movimientos;
        string nombre;
		double limiteInferior;
		double limiteSuperior;
		double posicionActual;

};

#endif
