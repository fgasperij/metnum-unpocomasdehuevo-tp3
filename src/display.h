#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include "Matriz.h"
#include "defines.h"
#include "io.h"

//Funciones para ver vectores y matrices por pantalla.



template<class T>
void mostrarFila(Matriz<T> A, int i){
	escribirFilaS(cout, A, i);
}

template<class T>
void mostrarColumna(Matriz<T> A, int i){
	escribirColumnaS(cout, A, i);
}

template<class T>
void mostrarMatriz( Matriz<T>& A){
	escribirMatrizS(cout, A);
}

template<class T>
void mostrarVector( vector<T>& v){
	escribirVectorS(cout, v);
}



#endif
