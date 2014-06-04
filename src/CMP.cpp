#include "CMP.h"
#include "Matriz.h"
#include <math.h>

vector<double> minimizarConGrado(vector<double> xs, int grado) {
	int cantidadMediciones = xs.size();
	Matriz<double> A(cantidadMediciones, grado+1);
	for(int i = 0; i < cantidadMediciones; ++i) 
	{
		for (int j = 0; i < grado+1; ++i)
		{
			A[i][j] = pow(i+1, grado-j);
		}
	}

	Matriz<double> b(cantidadMediciones, 1);
	for(int i = 0; i < cantidadMediciones; ++i) 
	{
		b[i][1] = xs[i];
	}



}