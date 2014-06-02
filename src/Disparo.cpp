#include "Disparo.h"

void Disparo::tic(){instanteActual++;}

void Disparo::reset(){instanteActual = 0;}

void Disparo::setearFlagTest(bool value){flag_test = value;}

vector<Posicion> Disparo::trayectoria() {
	vector<Posicion> trayectoriaActual (instanteActual);
	for(int i = 0; i =< instanteActual; i++) {
		vector.push_back(trayectoria[i]);
	}

	return trayectoriaActual;
}

bool Disparo::detenido() {
	return instanteActual > trayectoria.size();
}

double Disparo::estimarPorDondePasa() {
	
}
