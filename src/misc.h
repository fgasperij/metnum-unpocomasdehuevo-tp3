#ifndef MISC_H
#define MISC_H

#include <cmath>
#include <tuple>
#include "boost/math/tools/roots.hpp"
//#include "boost/tuple/tuple.hpp"
#include <boost/bind.hpp>
#include "Matriz.h"
#include "defines.h"

using namespace std;
using namespace boost::math::tools;

template<class T>
vector<T> matrizAVector(Matriz<T>& A){
    int cantFilas = A.cantFilas();
    int cantColumnas = A.cantColumnas();
    int tamanio = cantFilas*cantColumnas;
    vector<T> res (tamanio);
    int pos = 0;
    for(int i = 0; i < cantFilas; i++){
        for(int j = 0; j < cantColumnas; j++){
            res[pos] = A[i][j];
            pos++;
        }
    }
    return res;
}

struct TerminationCondition {
	bool operator()(double min, double max) {
		return fabs(max-min) <= EPS;
	}
};

vector<double> obtenerXs(vector<Posicion> trayectoria);
vector<double> obtenerYs(vector<Posicion> trayectoria);

double calcularRaiz(vector<double> coeficientes, int metodo = BISECCION);
double eval(vector<double> &coefs, double x);
tuple<double,double> evalNewton(vector<double> &coefs, double x);

template<class T>
bool esCero(T& val){
   return ((-CERO < val) && (val < CERO));
}

//Busca la posicion de maximo valor a partir de la posicion i.
// Se debe especificar el sentido, SUP es hacia arriba, INF es hacia abajo.
template<class T>
int maxPos(Matriz<T>& A, int i, int tipo){
    if(tipo ==  INF){
        T max_val = abs(A[i][i]);
        int max_pos = i;
        for(int h = i+1; h < A.cantFilas(); h++){
            if (A[h][i] > max_val){
                max_val = abs(A[h][i]);
                max_pos = h;
            }
        }
        return max_pos;
    }
    else{
        T max_val = abs(A[i][i]);
        int max_pos = i;
        for(int h = i-1; h+1 > 0; h--){
            if (A[h][i] > max_val){
                max_val = abs(A[h][i]);
                max_pos = h;
            }
        }
        return max_pos;
    }
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

#endif
