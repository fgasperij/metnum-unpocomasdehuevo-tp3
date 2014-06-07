#include "CMP.h"
#include "Matriz.h"
#include <math.h>
#include <assert.h>

/**
 * @param mediciones mediciones[i] = x(i) ==> el valor de x en el instante i
 * @param grado el grado del polinomio con el que queremos hacer CMP
 *
 * @return result[i] = a_i los coeficientes del polinomio
 */
vector<double> minimizarConGrado(vector<double> mediciones, int grado) {
	assert(grado < mediciones.size()-2); // no usamos el polinomio interpolador

	int cantidadMediciones = mediciones.size();	
	Matriz<double> A(cantidadMediciones, grado+1);
	for(int i = 0; i < cantidadMediciones; ++i) {
		for (int j = 0; j < grado+1; ++j){
			// la última columna tiene 1s porque es t_i^0
			if (j == grado) {
				A[i][j] = 1;
			} else {
				// los t_i son discretos entonces son 0,1,2,3,..,cantidadMediciones
				A[i][j] = pow(i, grado-j);
			}
		}
	}

	vector<double> b;
	for(int i = 0; i < cantidadMediciones; ++i) {
		b.push_back(mediciones[i]);
	}

	//A, ATranspuesta, C = ATranspuesta*A y proyeccionBSobreA = ATranspuesta*b
	Matriz<double> ATranspuesta = A;
	ATranspuesta.transponer();
	Matriz<double> C = ATranspuesta*A;
	vector<double> proyeccionBSobreA = ATranspuesta*b;

	gaussInf(A, proyeccionBSobreA);
	vector<double> coeficientesPivoteados (proyeccionBSobreA.size());
	backSubst(A, b, coeficientes);

	vector<double> coeficientes = A.despivotear(coeficientesPivoteados);

	return coeficientes;

}

/**
 * Triangulacion de la parte inferior. Siempre utiliza pivoteo parcial.
 */
template<class T>
void gaussInf(Matriz<T>& A, vector<T>& b){
	// Voy iterando la matriz fila por fila.
	int cant_filas = A.cantFilas();
	int cant_columnas = A.cantColumnas();
	for(int i = 0; i < cant_filas-1; i++){
		// Uso de pivoteo parcial para reducir el error.
        int max_pos = maxPos(A, i, INF);
        A.intercambiar(max_pos, i);
        swap(b[max_pos], b[i]);
		if(esCero(A[i][i])){cerr << "Gauss: la matriz no se puede triangular" << endl;  return;}
		// Aplico gauss fila por fila a partir de la fila siguiente a la fila pivot.
		for(int j = i+1; j < cant_filas; j++){
			T m = A[j][i]/A[i][i];
			// Si ya hay un cero, no hago nada.
			if(!esCero(m)){
                for(int k = i; k < cant_columnas; k++){
                    // Aplico gauss en toda la fila. Con k = i se cancelan los valores.
                    A[j][k] = A[j][k]- m*A[i][k];
                }
                // Actualizo b.
                b[j] = b[j] - m*b[i];
                // Mando un cero porque no confio en los double.
                A[j][i] = 0;
			}
		}
	}
}

template<class T>
void backSubst(Matriz<T>& A, vector<T>& b, vector<T>& res){
    int tamanio = A.cantFilas();
    vector<T> aux = vector<T> (tamanio);    

    if(res.size() != (unsigned int) tamanio){cerr << "backSubst: Tamaño no coincidente" << endl; return;}
    
    for(int i = tamanio-1; i+1 > 0; i--){
        T acum = 0;
        for(int j = tamanio-1; j > i ; j--){
            acum += res[j]*A[i][j];
        }
        res[i] = (b[i] - acum)/A[i][i];
    }    
}