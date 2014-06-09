#include "Arquero.h"
#include <algorithm>

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
		
	movimientos.push_back(desplazamiento);
}


// Funcion atajar. Tener en cuenta:
// Los limites del arco.
// El radio de atajada es 7. No irse hasta el limite, sino hasta limite - radio.
// El desplazamiento: Si la pelota esta lejos y el desplazamiento es mayor al radio de atajada
// se puede quedar en limite del arco - desplazamiento.
// Todavia mas, se puede calcular la velocidad de la pelota, y colocarse a limite del arco - desplazamiento*t
// donde t es la cantidad de tiempo que falta para que llegue el arco.
//
//void Arquero::atajar(double posicionAprox){
//    double desplazamiento = 0;

//    // Calculo un promedio ponderado de las aproximaciones con la siguiente formula:
//    // El ultimo tiro cuesta tiene peso 1/2, el segundo 1/4, el i 1/2^i, para i = 1 hasta cantidad de aproximaciones.
//    estimaciones.push_back(posicionAprox);
//    vector<double> ponderaciones;
//    double pond_inicial = 1/(pow(2,estimaciones.size()));
//    for(unsigned int i = 0; i < estimaciones.size(); i++){
//        ponderaciones.push_back(2*pond_inicial);
//    }
//    //double posicionEntrada = calcularPromedio(estimaciones);
//    double posicionEntrada = posicionAprox;

//    if (posicionEntrada < posicionActual){
//        if(posicionActual - amplitudMovimiento <= limiteInferior+7){movimientos.push_back(desplazamiento); return;}
//        desplazamiento = max(posicionEntrada - posicionActual, -amplitudMovimiento);
//    }
//    if(posicionActual < posicionEntrada){
//        if(posicionActual + amplitudMovimiento >= limiteSuperior-7){movimientos.push_back(desplazamiento); return;}
//        desplazamiento = min(posicionEntrada - posicionActual, amplitudMovimiento);
//    }
//    posicionActual += desplazamiento;
//    movimientos.push_back(desplazamiento);
//}

vector<int> Arquero::devolverMovimientos(){
    vector<int> results;
    for(unsigned int i = 0; i < movimientos.size(); i++){
        results.push_back(movimientos[i]);
    }
    return results;
}


