#include "Arquero.h"

void Arquero::atajar(double posicionEntrada){
	if ( posicionEntrada > (posicionActual+amplitudMovimiento) )
	{
		posicionActual+=amplitudMovimiento;
	}elseif (posicionEntrada < (posicionActual-amplitudMovimiento) )
	{
		posicionActual-=amplitudMovimiento;
	}
}
