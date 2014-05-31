#ifndef JUEGO_H
#define JUEGO_H

#include "defines.h"

class Juego{
	public:
		Juego();
		Juego(Data* dat) : data(dat), timestamp(0), flag_test(false) {}
		int dameTiempo();
		Posicion damePosicion(int);
		// TODO: Estas dos funciones se pueden convertir en iterador de juego.
		void avanzarJuego();
		bool terminoJuego();
		void setearFlagTest(bool);
		double dameDesplMax();
		double dameLimInf();
		double dameLimSup();
		double damePosInicial();

	private:
		Data* data;
		int timestamp;
		bool flag_test;

};

#endif
