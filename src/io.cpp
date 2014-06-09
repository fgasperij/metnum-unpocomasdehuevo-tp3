#include "io.h"



void setearPrecision(ostream& os, int prec)
{
	os.setf(ios::fixed, ios::floatfield);
	os.precision(prec);
}

// Cuento los caracteres hasta el primer espacio ESPACIO, y restauro el stream.
int contarCaracteres(ifstream& ifs)
{
	ifs.ignore(std::numeric_limits<std::streamsize>::max(), ESPACIO);
	int res = ifs.gcount();
	for(int i = 0; i < res; i++){ifs.unget();}

	return res;
}

// Ignoro cantidad veces hasta el caracter c.
void ignorarHastaCaracter(ifstream& ifs, int cantidad, char c){
	for(int i = 0; i < cantidad; i++){
		ifs.ignore(std::numeric_limits<std::streamsize>::max(), c);
	}
}

// Ignoro cantidad lineas.
void ignorarLineas(ifstream& ifs, int cantidad)
{
	ignorarHastaCaracter(ifs, cantidad, ENTER);
}

// Copio hasta el caracter c en el buffer.
void obtenerHastaCaracter(ifstream& ifs, char * buffer, char c)
{
	ifs.get(buffer, std::numeric_limits<std::streamsize>::max(), c);
}

int contarLineas(const char* file){
    ifstream file_s; file_s.open(file);
    int cant_lineas = 0;
    while(file_s.good()){
        ignorarLineas(file_s);
        cant_lineas++;
    }
    file_s.close();
    return cant_lineas-1;
}


//Lee los datos basios del archivo. La primer linea.
void leerDatosBasicos(const char* file, Data& data)
{
    int cant_lineas = contarLineas(file);
	ifstream file_s; file_s.open(file);
	file_s >> data.pos_arq >> data.lim_inf >> data.lim_sup >> data.mu;
	data.trayectoria = vector<Posicion> (0);
	file_s.get();	//Saco el Enter.
	cant_lineas--;
	for(int i=0; i < cant_lineas; i++){
		Posicion temp;
		file_s >> temp.x >> temp.y;
		(data.trayectoria).push_back(temp);
	}

	file_s.close();
}

void escribirTiempo(const char*  file, string st){
	ofstream file_s; file_s.open(file, fstream::app);
	file_s << st;
	file_s << endl;
	file_s.close();
}
