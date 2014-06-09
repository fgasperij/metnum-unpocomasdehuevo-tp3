/***
 * Métodos Numéricos - 1°Cuatr 2014
 * TP3 - Un poco más de huevo
 * ***/

#include <iostream>
#include <fstream>
#include "defines.h"
#include "util.h"
#include "Disparo.h"
#include "io.h"
#include "Arquero.h"
#include "signal.h"
int errores = 0;
int main(int argc, char **argv)
{

	// MANEJAR SI EL PROGRAMA FUE LLAMADO DE MANERA INCORRECTA
    if(argc != 3){cerr << "Cantidad de parametros incorrecta " ;return 0;}
	char * file_in = argv[1];
	char * file_out = argv[2];
	/*** Para evitar que se cambie el color al salir con Ctrl+C u otros ***/
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	msg_header();

	Data data;
	leerDatosBasicos(file_in, data);

	Disparo disparo = Disparo(data.trayectoria);
	Arquero higuita = Arquero("Higuita", data.lim_inf, data.lim_sup, data.mu, data.pos_arq);

	// Movimientos del arquero.
	while(!disparo.detenido()){
		disparo.tic();
		higuita.atajar(disparo.estimarPorDondePasa());
	}

	// Resultado
    escribirVector(file_out, higuita.devolverMovimientos());

	msg_footer();
    //cout << "Err " << disparo.devErrores() << endl;
	return 0;
}
