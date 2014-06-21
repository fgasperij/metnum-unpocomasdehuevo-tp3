#include "Arquero.h"
#include <algorithm>

void Arquero::atajar(double posicionAprox){
    double desplazamiento = 0;


    estimaciones.push_back(posicionAprox);
    double posicionEntrada = posicionAprox;

    if (posicionEntrada < posicionActual){
        if(posicionActual - amplitudMovimiento <= limiteInferior+7){movimientos.push_back(desplazamiento); return;}
        desplazamiento = max(posicionEntrada - posicionActual, -amplitudMovimiento);
    }
    if(posicionActual < posicionEntrada){
        if(posicionActual + amplitudMovimiento >= limiteSuperior-7){movimientos.push_back(desplazamiento); return;}
        desplazamiento = min(posicionEntrada - posicionActual, amplitudMovimiento);
    }
    posicionActual += desplazamiento;
    movimientos.push_back(desplazamiento);
}

vector<int> Arquero::devolverMovimientos(){
    vector<int> results;
    for(unsigned int i = 0; i < movimientos.size(); i++){
        results.push_back(movimientos[i]);
    }
    return results;
}

