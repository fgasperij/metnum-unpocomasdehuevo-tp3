#ifndef DISPARO_H
#define DISPARO_H

#include "defines.h"
#include "CMP.h"
#include <iostream>

/**
 * Simula el disparo de una pelota. El disparo es modelado como una secuencia
 * de posiciones de cuyo orden queda implícita la discretización del tiempo
 * realizada.
 */

class Disparo{
	public:
		/**
		 * Recibe la trayectoria completa del disparo.
		 */
		Disparo(vector<Posicion> trayectoria) 
		: trayectoria(trayectoria), instanteActual(0), flag_test(false), CMPdisparo(CMP()) {}
		/**
		 * Aumenta el instanteActual en 1, el disparo avanza una unidad de
		 * tiempo.
		 */
		void tic();
		/**
		 * Resetea instanteActual en 0. El disparo vuelve a su posición inicial.
		 */
		void reset();
		/**
		 * Devuelve un estimado de el lugar por el que pasará la pelota la línea
		 * de meta basado en la trayectoria de la misma hasta el instante actual
		 * inclusive.
		 * @return devuelve sólo el valor correspondiente a la coordenada 'y' ya
		 * que se asume que 'x' es igual a la línea de meta
		 */
		double estimarPorDondePasa();
		/**
		 * Devuelve la trayectoria del disparo hasta el instanteActual.
		 */
		vector<Posicion> trayectoria();
		/**
		 * Devuelve true si no le queda más trayectoria por recorrer.		 
		 */
		bool detenido();		

		void setearFlagTest(bool);

	private:
		/**
		 * Trayectoria completa del disparo.
		 */
		vector<Posicion> trayectoria;
		/**
		 * Momento acual de la simulación. El instante actual 0 se corresponde
		 * con la primer posición de la trayectoria, es decir, donde comenzó
		 * el disparo.
		 */
		int instanteActual;
		bool flag_test;

};

#endif
