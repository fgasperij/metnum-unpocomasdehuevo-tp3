#ifndef CMP_H
#define CMP_H

#include "defines.h"
#include <iostream>

vector<double> minimizarConGrado(vetor<double> xs, int grado);


// RESOLVER EL SISTEMA
template<class T>
void gaussInf(Matriz<T>& A, vector<T>& b);

template<class T>
void backSubst(Matriz<T>& A, vector<T>& b, vector<T>& res);