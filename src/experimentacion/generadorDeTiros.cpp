#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>

/**
 * MODO DE USO
 *
 * ./generar grado cantMediciones cantInstancias ruido
 */

/**
 * Formato del archivo de salida
 * 
 * posiciónArq posPoste1 posPoste2 cotaDesplazamiento
 * x0 y0
 * x1 y1
 * ...
 * xn yn
 *
 * dimensiones de la cancha: 1100 x 600.
 */

using namespace std;

#define POSICION_PRIMER_PALO 315
#define POSICION_SEGUNDO_PALO 385
#define COTA_DESPLAZAMIENTO 4
#define ANCHO_CANCHA 600
#define LARGO_CANCHA 1100
#define X_LINEA_META 125

struct punto {
	punto() : x(0), y(0) {};
	punto(int x, int y) : x(x), y(y) {};
	int x;
	int y;
};

int lagrange(vector<punto> puntosLagrange, int xActual);
int generarXRandDentroDeLaCancha();
int generarYRandDentroDeLaCancha();
int generarYRandDentroDelArco(int anchoArco);
vector<punto> generarTrayectoria(int anchoArco, int grado, int cantidadDeMediciones, int ruido);

int main(int argc, char const *argv[])
{
	/**
	 * @param grado grado del polinomio con el que se generará la curva de la
	 *        trayectoria
	 * @param cantidadDeMediciones
	 * @param cantidadDeInstancias 
	 * @param ruido % de ruido para las instancias
	 */
	
	if (argc != 5) {cout << "Cantidad de parámetros invalida." << endl; return 1;}

	int grado = atoi(argv[1]);
	int cantidadDeMediciones = atoi(argv[2]);
	int cantidadDeInstancias = atoi(argv[3]);
	int ruido = atoi(argv[4]);

	if (cantidadDeMediciones < grado+1) {
		cout << "La cantidad de mediciones es demasiado chica para el grado que eligió." << endl;
		return 1;
	}

	int anchoArco = POSICION_SEGUNDO_PALO - POSICION_PRIMER_PALO;
	for (int i = 0; i < cantidadDeInstancias; ++i)
	{
		srand(i);
		int posicionArquero = generarYRandDentroDelArco(anchoArco);
		vector<punto> trayectoria = generarTrayectoria(anchoArco, grado, cantidadDeMediciones, ruido);

		stringstream fileName;
		fileName << "tiro" << i << "conGrado" << grado << "conRuido" << ruido << ".tiro";
		string tmp = fileName.str();
		ofstream tiroFile (tmp.c_str());
		tiroFile << posicionArquero << " " << POSICION_PRIMER_PALO << " " << POSICION_SEGUNDO_PALO << " " << COTA_DESPLAZAMIENTO << endl;
		for(unsigned i = 0; i < trayectoria.size(); ++i) {
			tiroFile << trayectoria[i].x << " " << trayectoria[i].y << endl;
		}

		tiroFile.close();
	}	

	return 0;
}

vector<punto> generarTrayectoria(int anchoArco, int grado, int cantidadDeMediciones, int ruido) {	
	int yGol = generarYRandDentroDelArco(anchoArco);

	vector<punto> puntosLagrange;
	puntosLagrange.push_back(punto(X_LINEA_META, yGol));
	int xRand, yRand;
	for(unsigned i = 0; i < grado; ++i) {
		xRand = generarXRandDentroDeLaCancha();
		yRand = generarYRandDentroDeLaCancha();

		puntosLagrange.push_back(punto(xRand, yRand));
	}

	vector<punto> trayectoria;
	// (cantidadDeMediciones - 1) por que yGol ya lo tengo
	int xInicial = generarXRandDentroDeLaCancha();
	int delta = (xInicial - X_LINEA_META)/(cantidadDeMediciones-1);
	int xActual;

	// cout << "PUNTOS LAGRANGE"<< endl;
	// for(unsigned i = 0; i < puntosLagrange.size(); ++i) {
	// 	cout << "X: " << puntosLagrange[i].x << " Y: " << puntosLagrange[i].y << endl;
	// }
	
	for(unsigned i = 0; i < cantidadDeMediciones-1; ++i) {
		xActual = xInicial - i*delta - (rand() % delta);
		// cout << "xActual " << xActual << endl;
		int valor = lagrange(puntosLagrange, xActual);
		if (ruido > 0) {
			// introduzco ruido			
			int amplitudRuido = (ruido*valor)/100;
			if (amplitudRuido > 0) {
				srand(i+200);
				int ruidoFinal = rand() % (amplitudRuido);
				if ((i+2)%2 == 0) {
					valor += ruidoFinal;
				} else {
					valor -= ruidoFinal;
				}
			}			
		} 		
		trayectoria.push_back(punto(xActual, valor));
	}

	trayectoria.push_back(punto(X_LINEA_META, yGol));

	return trayectoria;
}


int lagrange(vector<punto> puntosLagrange, int xActual) {
	double sum = 0;
	double mult;
	int cantidadDePuntos = puntosLagrange.size();
	for(int i = 0; i < cantidadDePuntos; i++) {
		mult = 1;
	    for(int j = 0;j < cantidadDePuntos; j++) {
	        if(j != i) {
	        	mult *= ((double)(xActual-puntosLagrange[j].x)/(double)(puntosLagrange[i].x-puntosLagrange[j].x));
	        }
	    }	    
	    sum += mult*puntosLagrange[i].y;
	}
	return (int) sum % 600;
}

int generarXRandDentroDeLaCancha() {
	return (rand() % LARGO_CANCHA) + X_LINEA_META;
}

int generarYRandDentroDeLaCancha() {
	return (rand() % ANCHO_CANCHA);
}

int generarYRandDentroDelArco(int anchoArco) {
	return (rand() % anchoArco) + POSICION_PRIMER_PALO;
}