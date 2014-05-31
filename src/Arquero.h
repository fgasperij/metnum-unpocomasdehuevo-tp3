#ifndef ARQUERO_H
#define ARQUERO_H

#include "defines.h"
#include "Juego.h"
#include <string>

class Arquero{
	public:
		Arquero();
		Arquero(string n, Juego* j) : nombre(n), juego(j), posicion(j->damePosInicial()) {}
		void mover(Posicion);

	private:
        string nombre;
		Juego* juego;
		double posicion;

};

#endif
