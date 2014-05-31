#include "Juego.h"

int Juego::dameTiempo(){return this->timestamp;}

Posicion Juego::damePosicion(int tiempo){
	if(!(this->flag_test) && timestamp < tiempo+1){   // Verificar el timestamp < tiempo+1
		cerr << "No se puede conocer el futuro " << endl;
        Posicion trucha; trucha.pos_x = -1; trucha.pos_y = -1;
		return trucha;
	}
	else{
		return  (this->data->movimientos)[tiempo];
	}
}

void Juego::avanzarJuego(){(this->timestamp)++;}

void Juego::setearFlagTest(bool status){this->flag_test = status;}

bool Juego::terminoJuego(){
	return (this->timestamp == CANT_MOVIMIENTOS);	// o CANT_MOVIMIENTOS-1, no estoy seguro
}

double Juego::dameDesplMax(){return this->data->mu;}

double Juego::dameLimInf(){return this->data->lim_inf;}

double Juego::dameLimSup(){return this->data->lim_sup;}

double Juego::damePosInicial(){return this->data->pos_arq;}

