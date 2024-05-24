#include <iostream>
#include <string>

using namespace std;

int main() {
    string instruccion;
    
    
    cout << "Ingresa una instrucción: ";
    getline(cin, instruccion);

    
    for (char letra : instruccion) {
        cout << letra << endl;
    }

    return 0;
}


