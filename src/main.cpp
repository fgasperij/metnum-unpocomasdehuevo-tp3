
/***
 * Métodos Numéricos - 1°Cuatr 2014
 * TP2 - Tu cara me suena...
 * ***/

#include <iostream>
#include <fstream>
#include "defines.h"
#include "util.h"
#include "io.h"
#include "misc.h"
#include "Matriz.h"
#include "Juego.h"
#include "Arquero.h"
#include "signal.h"

int main(int argc, char **argv)
{

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

	Juego juego = Juego (&data);
	Arquero higuita = Arquero("Higuita", &juego);

	while(!juego.terminoJuego()){
		double aprox = aproximarTrayectoria(&juego);
		higuita.mover(aprox);
		//higuita.escorpion()
		juego.avanzarJuego();
	}


	msg_footer();

	return 0;
}
