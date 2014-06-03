#include <vector>
#include <iostream>
#include <sstream>      // std::stringbuf
#include <string>       // std::string

using namespace std;

int main(int argc, char **argv[]){

	string s("hola como estas");
	stringbuf buffer(s);

	istream is(&buffer);

	while(is.good()) {
		cout << "Character extracted: " << is.get() << "*END*" << endl;
	}



	return 0;

}