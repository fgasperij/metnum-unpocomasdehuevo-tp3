#include "Juego.h"

int dameTiempo(){return this->timestamp;}

Posicion damePosicion(int tiempo){
	if(!(this->flag_test) && tiempo < timestamp+1){	// O timestamp, no estoy seguro
		cerr << "No se puede conocer el futuro " << endl;
		return 0;
	}
	else{
		return  (this->data->movimientos)[tiempo];
	}
}

void avanzarJuego(){(this->timestamp)++;}

void setearFlagTest(bool status){this->flag_test = status;}

bool terminoJuego(){
	return (this->timestamp == CANT_MOVIMIENTOS-1);	// O CANT_MOVIMIENTOS, no estoy seguro
}

double dameDesplMax(){return this->data->mu;}

double dameLimInf(){return this->data->lim_inf;}

double dameLimSup(){return this->data->lim_sup;}

double damePosInicial(){return this->data->pos_arq;}

