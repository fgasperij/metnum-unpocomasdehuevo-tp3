/***
 * Métodos Numéricos - 1°Cuatr 2014
 * TP3 - Un poco más de huevo
 * ***/

#include <iostream>
#include <fstream>
#include "defines.h"
#include "util.h"
#include "io.h"
#include "misc.h"
#include "Disparo.h"
#include "Arquero.h"
#include "signal.h"

int main(int argc, char **argv)
{

	// MANEJAR SI EL PROGRAMA FUE LLAMADO DE MANERA INCORRECTA

	char * file_in = argv[1];
	/*** Para evitar que se cambie el color al salir con Ctrl+C u otros ***/
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	msg_header();

	Data data;
	leerDatosBasicos(file_in, data);
    data.show_info();

	Disparo disparo = Disparo(data.trayectoria);
	Arquero higuita = Arquero("Higuita", data.lim_inf, data.lim_sup, data.mu, data.pos_arq);

	while(!disparo.detenido()){
		disparo.tic();
		higuita.atajar(disparo.estimarPorDondePasa());
	}

	// ESCRIBIR EN EL OUT arquero.movimientos()

	msg_footer();

	return 0;
}
