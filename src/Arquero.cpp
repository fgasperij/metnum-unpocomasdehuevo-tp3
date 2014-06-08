#include "Arquero.h"

void Arquero::atajar(double posicionEntrada){
	if ( posicionEntrada > (posicionActual+amplitudMovimiento) )
	{
		posicionActual+=amplitudMovimiento;
		if (posicionActual>limiteSuperior)
			posicionActual=limiteSuperior;
	}else if (posicionEntrada < (posicionActual-amplitudMovimiento) )
	{
		posicionActual-=amplitudMovimiento;
		if (posicionActual<limiteInferior)
			posicionActual=limiteInferior;
	}
}
