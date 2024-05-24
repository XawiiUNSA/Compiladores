#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	
	fstream archivo("E1.cpp");
	char caracter;
	
	while (archivo.get(caracter)) {
		cout << caracter;
	}
	
	archivo.close();
	
}



