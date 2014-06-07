#ifndef MISC_H
#define MISC_H

#include <cmath>

#include "Matriz.h"
#include "defines.h"

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
Autos<T> calcularAuto(Matriz<T>& A, int componentes){
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
		tamanio[i] = autos.autovalores[0][i];
	}
	return raices;
}

#endif
