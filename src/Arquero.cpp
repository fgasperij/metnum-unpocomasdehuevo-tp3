#include "Arquero.h"

void Arquero::atajar(double posicionEntrada){
	double posicionPrevia = posicionActual;
	double desplazamiento=0;
	// Si la pelota no está al alcance del arquero
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
	}else 
	{
		// Si la pelota está al alcance del arquero, podríamos acercarnos al punto de entrada
	}
	// Calculo cuál fue el desplazamiento
	if (posicionActual>posicionPrevia)
		desplazamiento=posicionActual-posicionPrevia;
	else if (posicionActual<posicionPrevia)
		desplazamiento=-(posicionPrevia-posicionActual);
		
	//return desplazamiento;
	// o bien: movimientos(push_back,desplazamiento);
}
