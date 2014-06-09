#include "Arquero.h"
#include <algorithm>

int Arquero::atajar(double posicionEntrada){
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
		
	return desplazamiento;
	// o bien: movimientos.push_back(desplazamiento);
}

// Funcion atajar. Tener en cuenta:
// Los limites del arco.
// El radio de atajada es 7. No irse hasta el limite, sino hasta limite - radio.
// El desplazamiento: Si la pelota esta lejos y el desplazamiento es mayor al radio de atajada
// se puede quedar en limite del arco - desplazamiento.
// Todavia mas, se puede calcular la velocidad de la pelota, y colocarse a limite del arco - desplazamiento*t
// donde t es la cantidad de tiempo que falta para que llegue el arco.
//
//int Arquero::atajar(double posicionEntrada){
//    double desplazamiento = 0;
//    if (posicionEntrada < posicionActual){
//        if(posicionActual - amplitudMovimiento <= limiteInferior+7){return 0;}
//        desplazamiento = max(posicionEntrada - posicionActual, -amplitudMovimiento);
//        posicionActual += desplazamiento;
//        return desplazamiento;
//    }
//    if(posicionActual < posicionEntrada){
//        if(posicionActual + amplitudMovimiento >= limiteSuperior-7){return 0;}
//        desplazamiento = min(posicionEntrada - posicionActual, amplitudMovimiento);
//        posicionActual += desplazamiento;
//        return desplazamiento;
//    }
//    return 0;
//}
