#include "global.h"
// Parametros de configuraciones gloables
config conf;

void cargarConfPorDefecto(){
    conf.cant_mediciones = MAX_GRADO;
    conf.max_grado = CANT_MEDICIONES;
}
