#ifndef MISC_H
#define MISC_H

#include <cmath>
#include "Matriz.h"
#include "defines.h"


template<class T>
bool esCero(T& val){
   return ((-CERO < val) && (val < CERO));
}

template<class T>
unsigned int contarPrimCrecientes(vector<T>& vec){
    unsigned int cantCrecientes = 0;
    for(unsigned int i = 0; i < vec.size() ; i++){
        if(i+1 < vec.size() && vec[i] <= vec[i+1] ){
            cantCrecientes++;
        }
        else if(i+1 == vec.size()){cantCrecientes++;}
        else{break;}
    }
    return cantCrecientes;
}

template<class T>
vector<T> ultimos(const vector<T>& vec,int cant = 0){
    vector<T> aux = vec;
    reverse(aux.begin(), aux.end());
    aux.resize(cant);
    return aux;
}


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


// Promedio ponderado dede un vector, si tiene tamanio 0 o los cantidad de ponderaciones es distinta a la cantidad de elementos, o la suma
// de las ponderaciones es 0, devuelve 0.
template<class T>
T calcularPromedio(const vector<T>& vec, const vector<T>& ponderaciones){
    if(ponderaciones.size() != vec.size()){cerr << "calcularPromedioPonderado: Tamaños no coincidentes";return 0;}
    unsigned int tamanio = vec.size();
    if(tamanio == 0){return 0;}
    T acum = 0;
    T pesos = 0;
    for(unsigned int i = 0; i < tamanio; i++){
        acum += vec[i]*ponderaciones[i];
        pesos += ponderaciones[i];
    }
    if(pesos == 0){return 0;}
    return acum/pesos;
}

#endif
