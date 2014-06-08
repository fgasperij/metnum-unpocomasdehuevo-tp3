#include "m_aux.h"

// Crea vector tal que vec[i] = i;
vector<int> crearPosiciones(int cant_filas){
	vector<int> p = vector<int> (cant_filas);
	for(int i = 0; i < cant_filas; i++){
		p[i] = i;
	}
	return p;
}
