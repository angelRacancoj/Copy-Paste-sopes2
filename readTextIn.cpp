#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include<vector>
using namespace std;

vector <string> getFiles(string textoEntrada);

int main (int argc, char *argv[]) {
	string inputFile(argv[1]);
	vector <string> paths = getFiles(inputFile);

	cout<<"List size: "<< paths.size() <<endl;

	for (int i = 0; i < paths.size(); ++i){
		cout<<"Path: "<<paths[i]<<endl;
	}

	return 0;
}

vector <string> getFiles(string textoEntrada){
	vector <string> paths;

	string delimiter=",";

	size_t pos = 0;
	string token;
	while ((pos = textoEntrada.find(delimiter)) != string::npos) {
	    token = textoEntrada.substr(0, pos);
	    cout << token << endl;
	    paths.push_back(token);

	    textoEntrada.erase(0, pos + delimiter.length());
	}
	cout << textoEntrada << endl;
	paths.push_back(textoEntrada);

	return paths; 
}

