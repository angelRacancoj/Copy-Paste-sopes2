/*
LINKS:
http://www.cplusplus.com/reference/string/string/find/
http://www.cplusplus.com/reference/vector/vector/data/
http://www.cplusplus.com/forum/beginner/14792/
https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c#14266139

*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include<vector>
using namespace std;

struct fileMemory{
	string filePath;
	streampos sizeF;
  	char * memblockF;
};

vector <string> getFilesPath(string textoEntrada);
string getPath(string textoEntrada, string delimiter);
string getFileName(string textoEntrada);
fileMemory getFile(string inputFile);
void writeFile(fileMemory fOut, string destinyPath);

int main (int argc, char *argv[]) {
	string pathOut;
	string delimiterFile = ".archivo";
	string delimiterDir = ".directorio";
	string inputFile(argv[1]);
	vector <fileMemory> fileIn;
	vector <string> paths = getFilesPath(inputFile);

	cout<<"List size: "<< paths.size() <<endl;

	for (int i = 0; i < paths.size(); ++i){

		if (paths[i].find(delimiterFile) != string::npos) {
			fileIn.push_back(getFile(getPath(paths[i],delimiterFile)));

		} else if (paths[i].find(delimiterDir) != string::npos) {
			cout<<"In: "<<paths[i]<<", Path: "<<getPath(paths[i],delimiterDir)<<endl;
		} else {
			cout<<"Error en: "<<paths[i]<<endl;
			return 0;
		}
		//cout<<"In: "<<paths[i]<<", Path: "<<getPath(paths[i],delimiterFile)<<endl;
	}

	//ask for final destiny
	cout << "Ingrese la ruta destino: ";
    cin >> pathOut;

    for (int i = 0; i < fileIn.size(); ++i){
    	writeFile(fileIn[i],pathOut);
    }

    cout << "Tarea completada :)"<<endl;
	return 0;
}

vector <string> getFilesPath(string textoEntrada){
	vector <string> paths;

	string delimiter=",";

	size_t pos = 0;
	string token;
	while ((pos = textoEntrada.find(delimiter)) != string::npos) {
	    token = textoEntrada.substr(0, pos);
//	    cout << token << endl;
	    paths.push_back(token);

	    textoEntrada.erase(0, pos + delimiter.length());
	}
//	cout << textoEntrada << endl;
	paths.push_back(textoEntrada);

	return paths; 
}

string getPath(string textoEntrada, string delimiter){

	string pathFile;
	size_t pos = 0;
	string token;
	while ((pos = textoEntrada.find(delimiter)) != string::npos) {
	    token = textoEntrada.substr(0, pos);
	    pathFile = token;

	    textoEntrada.erase(0, pos + delimiter.length());
	}
	cout << "Path: "<<pathFile << endl;
	return pathFile; 
}

string getFileName(string textoEntrada){

	string delimiter="/";

	size_t pos = 0;
	string token;
	while ((pos = textoEntrada.find(delimiter)) != string::npos) {
	    token = textoEntrada.substr(0, pos);
//	    cout << token << endl;
	    textoEntrada.erase(0, pos + delimiter.length());
	}
//	cout << textoEntrada << endl;
	return textoEntrada; 
}

fileMemory getFile(string inputFile){
	streampos size;
	char * memblock;
    fileMemory fileInMemory;

	ifstream file (inputFile, ios::in|ios::binary|ios::ate);
	if (file.is_open()) {
	    size = file.tellg();
	    memblock = new char [size];
	    file.seekg (0, ios::beg);
	    file.read (memblock, size);
	    file.close();
	    fileInMemory.filePath = getFileName(inputFile);
	    fileInMemory.sizeF = size;
	    fileInMemory.memblockF = memblock;
	}
	return fileInMemory;
}

void writeFile(fileMemory fOut, string destinyPath){
	string pathOut = destinyPath + fOut.filePath;
	cout << "Path destino: "<< pathOut <<endl;

    ofstream fileout(pathOut, ios::out | ios::binary);
    fileout.write(fOut.memblockF, fOut.sizeF);  
    fileout.close();

    delete[] fOut.memblockF;
}