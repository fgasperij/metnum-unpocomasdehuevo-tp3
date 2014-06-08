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


// Numero de iteraciones para el metodo de la potencia.
#define PITER 300

template<class T>
struct Autos{
	Matriz<T> autovectores;
	Matriz<T> autovalores;
};

template<class T>
T calcularNorma(Matriz<T>& v){
	int cantFilas = v.cantFilas(); int cantColumnas = v.cantColumnas();
	T acum = 0;
	if(cantFilas == 1){
		for(int i = 0; i < cantColumnas; i++){
			acum += v[0][i]*v[0][i];
		}
	}
	else if(cantColumnas == 1){
		for(int i = 0; i < cantFilas; i++){
			acum += v[i][0]*v[i][0];
		}
	}
	else{
		cerr << "calcularNorma no admite matrices no vectoriales " << endl;
	}
	return sqrt(acum);
}


template<class T>
void metoPotencia(Matriz<T>& A, Matriz<T>& autovectores, Matriz<T>& autovalores, int numero){
	int cantFilas = A.cantFilas(); int cantColumnas = A.cantColumnas();
	Matriz<T> v (cantFilas, 1, 1); // = ???? RANDOM?
	T n;
	for(int i = 0; i < PITER; i++){
		v = A*v;
		n = calcularNorma(v);
		v*(1/n);
	}

	for(int i = 0; i < cantFilas; i++){
		autovectores[i][numero] = v[i][0];
	}

	Matriz<T> vt = v;
	vt.transponer();
	T landa = (vt*A*v)[0][0];
	landa = landa * (1/((vt*v)[0][0]));
	autovalores[0][numero] = landa;
}



template<class T>
Matriz<T> dameColumna(Matriz<T>& A, int numero){
	int cantFilas = A.cantFilas(); int cantColumnas = A.cantColumnas();
	Matriz<T> columna (cantFilas, 1);
	for(int i = 0; i < cantFilas; i++){
		columna[i][0] = A[i][numero];
	}
	return columna;
}

template<class T>
void deflacionar(Matriz<T>& A, Matriz<T>& autovectores, Matriz<T>& autovalores, int numero){
	int cantFilas = A.cantFilas(); int cantColumnas = A.cantColumnas();
	Matriz<T> v = dameColumna(autovectores, numero);
	Matriz<T> vt = v;
	vt.transponer();
	Matriz<T> prod = v*vt;
	prod*(-autovalores[0][numero]);
	A + (prod);
}

template<class T>
Autos<T> calcularAutos(Matriz<T>& A, int componentes){
	int cantFilas = A.cantFilas(); int cantColumnas = A.cantColumnas();

	Autos<T> autos;
	autos.autovectores = Matriz<T> (cantFilas, componentes);
	autos.autovalores = Matriz<T> (1, componentes);
	for(int i = 0; i < componentes; i++){
		metoPotencia(A, autos.autovectores, autos.autovalores, i);
		deflacionar(A, autos.autovectores, autos.autovalores, i);
	}
	return autos;
}

// Calculo de raices de un polinomio calculando los autovalores de su matriz companiera.
// Los autovalores se calculan con metodo de la potencia y deflacion. Si el grado del polinimio es
// alto, el arrastre de error tambien.
// Este metodo requiere que el polinimio tenga raices distintas y reales.
// Coeficientes: Los de menor grado vienen primero.
template<class T>
vector<T> calcRaicesPoli(vector<T>& coeficientes){
	int tamanio = coeficientes.size();
	// Calculo la matriz companiera.
	Matriz<T> companiera (tamanio);
	for(int i = 1; i < tamanio; i++){
		companiera[i][i-1] = 1;	// Son los unos de la diagonal debajo de la diagonal principal
		companiera[i][tamanio-1] = coeficientes[i]/coeficientes[tamanio];
		// Los coeficientes del polinomio van en la ultima columna,
		// como debe ser monico divido por el coeficiente principal.
	}
	vector<T> raices (tamanio);
	// Calculo autovalores.
	Autos<T> autos = calcularAutos(companiera, tamanio);
	// Los copio a un vector.
	for(int i = 0; i < tamanio; i++){
		raices[i] = (autos.autovalores)[0][i];
	}
	return raices;
}

#endif
