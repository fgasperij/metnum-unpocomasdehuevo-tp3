#include "util.h"
#include <algorithm>
#include <string>
#include "signal.h"
#include "global.h"
#include "pugixml.hpp"

/*** Mensajes pantalla ***/

void my_handler(int s){
           std::cout<<ENDCOLOR<<std::endl << std::flush;
           // Para evitar warning unused variable.
           int evitarWarning = s;
           evitarWarning++;
           exit(0);

}

void msg_header()
{
	std::cout<<std::endl<<MAGENTA<<"\n *** METODOS NUMERICOS - 1°C 2014 - TP2 *** \n"<<ENDCOLOR;
}

void msg_footer()
{
	std::cout<<"\n"<<MAGENTA<<"\n *** -.- *** \n"<<ENDCOLOR<<std::endl;
}

void msg_parseo_falla(std::string msg)
{
	std::cout<<"\n"<<MAGENTA<<"\n "<<msg<<"\n Para ver modo de uso: ./tp h "<<ENDCOLOR<<std::endl;
	msg_footer();
}

void msg_modo_uso()
{
	std::cout<<MAGENTA;
	std::cout << "\n MODO DE USO:"<< std::endl;
	std::cout << "\n ./tp2 <archivo entrada> <archivo salida> <m>" << std::endl;
	std::cout << "\n\t<archivo entrada> corresponde al archivo con los training sets y las caras para reconocer" << std::endl;
	std::cout << "\n\t<archivo salida> corresponde al archivo con los resultados del reconocimiento" << std::endl;
	std::cout << "\n\t<m> = 1 | 0 corresponde a la estrategia utilizada" << std::endl;
	std::cout << "\n\t<ident> = 1 | 0 corresponde a la identificación con promedio o con mínimo. Opcional" << std::endl;
	std::cout<<ENDCOLOR;
}


/*** Aritméticas ***/

int signo(double x)
{
	return ( (x>0) ? 1 : ((x<0) ? -1 : 0) );
}

bool es_par(int n)
{
	return (n%2==0);
}

using namespace pugi;
/*** Carga la configuracion  ***/
void cargarConfiguracion(const char * file_xml){
    xml_document doc;
    if(!doc.load_file(file_xml)){return;};
    xml_node config =  doc.child("config");
    xml_node cant_mediciones = config.child("cant_mediciones");
    xml_node max_grado = config.child("max_grado");
    xml_node lagrange = config.child("lagrange");
    if(cant_mediciones){conf.cant_mediciones = atoi((cant_mediciones.text()).get());}
    if(max_grado){conf.max_grado = atoi((max_grado.text()).get());}
    if(lagrange){
        string use_lagrange = string(lagrange.text().get());
        transform(use_lagrange.begin(), use_lagrange.end(), use_lagrange.begin(), ::tolower);
        if(use_lagrange == "true"){
            conf.lagrange = true;
        }
    }

}
