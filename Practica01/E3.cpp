#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  string filename("E1.1.cpp");
  vector<string> words;
  string word;

  ifstream input_file(filename);
  if (!input_file.is_open()) {
    cerr << "No se pudo abrir el archivo ' " << filename << "'" << endl;
    return EXIT_FAILURE;
  }

  while (input_file >> word) {
    words.push_back(word);
  }

  for (const auto &i : words) {
    if(isalpha(i[0])){
      cout<<"palabra = "<<i<<endl;
    }
    else if(isdigit(i[0])){
      cout<<"numero = "<<i<<endl;
    }
    else{
      cout<<"simbolo = "<<i<<endl;
    }
    
  }
  input_file.close();
  
  return 0;
}



