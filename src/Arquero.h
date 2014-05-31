#ifndef JUEGO_H
#define JUEGO_H

#include "defines.h"
#include "Juego.h"

class Juego{
	public:
		Arquero();
		Juego(char* n; Juego* j) : nombre(n), juego(j), posicion(j->damePosInicial()) {}
		void mover(double);

	private:
		Juego* juego;
		char* nombre;
		double posicion;

};

#endif
