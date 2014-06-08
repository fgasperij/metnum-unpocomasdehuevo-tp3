#include "Arquero.h"

void Arquero::atajar(double posicionEntrada){
	if ( posicionEntrada > (posicionActual+mu) )
	{
		posicionActual+=mu;
	}elseif (posicionEntrada < (posicionActual-mu) )
	{
		posicionActual-=mu;
	}
}
