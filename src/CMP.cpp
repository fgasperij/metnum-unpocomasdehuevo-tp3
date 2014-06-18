#include "CMP.h"
#include <math.h>
#include <assert.h>
#include "Matriz.h"
#include "misc.h"

/**
 * @param mediciones mediciones[i] = x(i) ==> el valor de x en el instante i
 * @param grado el grado del polinomio con el que queremos hacer CMP
 *
 * @return result[i] = a_i los coeficientes del polinomio
 */
vector<double> minimizarConGrado(vector<double>& mediciones, int grado, int tiempo) {
	//assert(grado < (int) (mediciones.size())); // no usamos el polinomio interpolador

	int cantidadMediciones = mediciones.size();
	Matriz<double> A(cantidadMediciones, grado+1);
	for(int i = 0; i < cantidadMediciones; ++i) {
		for (int j = 0; j < grado+1; ++j){
			// la última columna tiene 1s porque es t_i^0
			if (j == grado) {
				A[i][j] = 1;
			} else {
				// los t_i son discretos entonces son 0,1,2,3,..,cantidadMediciones
				A[i][j] = pow(tiempo-i, grado-j);
			}
		}
	}


	Matriz<double> bMatriz (cantidadMediciones, 1);



	for(int i = 0; i < cantidadMediciones; ++i) {
		bMatriz[i][0] = mediciones[i];
	}

	//A, ATranspuesta, C = ATranspuesta*A y proyeccionBSobreA = ATranspuesta*b
	Matriz<double> ATranspuesta = A;

	ATranspuesta.transponer();
	Matriz<double> C = ATranspuesta*A;
	Matriz<double> proyeccionBSobreAMatrix = ATranspuesta*bMatriz;
	vector<double> proyeccionBSobreA = matrizAVector(proyeccionBSobreAMatrix);

	gaussInf(C, proyeccionBSobreA);

	vector<double> coeficientesPivoteados (proyeccionBSobreA.size());
	backSubst(C, proyeccionBSobreA, coeficientesPivoteados);

	vector<double> coeficientes = C.despivotear(coeficientesPivoteados);
	reverse(coeficientes.begin(), coeficientes.end());

	return coeficientes;

}


