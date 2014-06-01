#ifndef DISPARO_H
#define DISPARO_H

#include "defines.h"
#include <iostream>

class Disparo{
	public:		
		Disparo(vector<pos> trayectoria) : trayectoria(trayectoria), instanteActual(0), flag_test(false) {}
		void tic();
		void reset();
		double estimarPorDondePasa();
		void setearFlagTest(bool);

	private:
		vector<pos> trayectoria;
		int instanteActual;
		bool flag_test;

};

#endif
