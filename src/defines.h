#ifndef DEFINES_H_
#define DEFINES_H_

/*** DEFINICIONES BASICAS ***/

#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> Pos;

/** Para medir tiempo de ejecución **/
#define TIMER(var) clock_gettime(CLOCK_REALTIME, &var);

/** Para colorear la consola **/
#define ENDCOLOR "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define LIGHTRED "\033[1m\033[31m"
#define GREEN "\033[32m"
#define LIGHTGREEN "\033[1m\033[32m"
#define BLUE "\033[34m"
#define LIGHTBLUE "\033[1m\033[34m"
#define YELLOW "\033[1m\033[33m"
#define MAGENTA "\033[35m"
#define LIGHTMAGENTA "\033[1m\033[35m"
#define CYAN "\033[1m\033[36m"
#define GREY "\033[37m"
#define BROWNBACK "\033[43m" // fondo marron - letra blanca

struct Posicion{
	double pos_x;
	double pos_y;
};


/** Parámetros de las imágenes de un mismo conjunto de entrenamiento **/
struct Data{
	double mu;	// Desplazamiento maximo
	double pos_arq;	// Posicion arquero y
	// Limites del arco
	double lim_inf;
	double lim_sup;

	// Movimientos de la pelota
	vector<Posicion> movimientos;

    void show_info(){
		cout<<YELLOW;
		cout << "\n -- Info de los datos de entrada --";
		cout << "\n MU:\t"<< mu;
		cout << "\n POSICION DEL ARQUERO:\t" << pos_arq;
		cout << "\n LIMITE INFERIOR:\t" << lim_inf;
		cout << "\n LIMITE SUPERIOR:\t" << lim_sup;
		cout << "\n MOVIMIENTOS:\t" << endl;
        for(unsigned int i=0; i < movimientos.size(); i++){
            cout << movimientos[i].pos_x << " " << movimientos[i].pos_y;
            if(i != movimientos.size()){cout << endl;}
        }
		cout<<ENDCOLOR;
	}
};


// Precicion decimal para la salida
#define PRECISION 6

/*** Definiciones para io.h ***/

#define VERT 0
#define HORIZ 1

// Caracteres
#define ENTER '\n'
#define ESPACIO ' '


/*** Definiciones para misc.h y main ***/

#define FILA 0
#define COLUMNA 1

/*** Cantidad de posiciones de la pelota ***/
#define CANT_MOVIMIENTOS 24



#endif
