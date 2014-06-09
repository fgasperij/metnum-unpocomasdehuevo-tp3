#ifndef ARQUERO_H
#define ARQUERO_H

#include "defines.h"
#include <string>

/**
 * Modela al arquero.
 */
class Arquero{
	public:
		Arquero();
		Arquero(string n, double inf, double sup, double mu, double posicionInicial)
		: nombre(n), limiteInferior(inf), limiteSuperior(sup), amplitudMovimiento(mu), posicionActual(posicionInicial) {}
		/**
		 * Realiza un movimiento dentro de los límites impuestos por
		 * amplitudMovimiento para poder acercarse lo más posible a la posición
		 * ideal para atajar el disparo.
		 * @param Posicion lugar por el que pasa la pelota
		 */
		void atajar(double posicion);
		vector<int> devolverMovimientos();

	private:
		/**
		 * Secuencia de movimientos que ha realizado el arquero por las
		 * sucesivas llamadas a atajar().
		 */
		vector<double> movimientos;
		vector<double> estimaciones;
        string nombre;
		double limiteInferior;
		double limiteSuperior;
		double amplitudMovimiento;
		double posicionActual;

};

#endif
