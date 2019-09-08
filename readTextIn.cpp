/*
LINKS:
Memory:
http://www.cplusplus.com/doc/tutorial/files/
https://databasefaq.com/index.php/answer/39431/c-11-ram-file-format-recognizing-file-formats-from-binary-c-
http://www.cplusplus.com/doc/tutorial/files/

Others:
http://www.cplusplus.com/reference/string/string/find/
http://www.cplusplus.com/reference/vector/vector/data/
http://www.cplusplus.com/forum/beginner/14792/
https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c#14266139
https://stackoverflow.com/questions/12510874/how-can-i-check-if-a-directory-exists
https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
http://www.codebind.com/cpp-tutorial/cpp-program-list-files-directory-windows-linux/

Ram:
http://man7.org/linux/man-pages/man2/sysinfo.2.html
https://stackoverflow.com/questions/349889/how-do-you-determine-the-amount-of-linux-system-ram-in-c
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include<vector>
#include <dirent.h>
#include <cstring>
#include <memory> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <sys/sysinfo.h>

using namespace std;

struct sysinfo info;

struct fileMemory{
	string filePath;
	streampos sizeF;
  	char * memblockF;
};

string delimiterFile = ".archivo";
string delimiterDir = ".directorio";

vector <string> getFilesPath(string textoEntrada);
string getPath(string textoEntrada, string delimiter);
string getFileName(string textoEntrada);
string getDirectoryName(string textoEntrada);
fileMemory getFile(string inputFile);
void writeFile(fileMemory fOut, string destinyPath);
bool existFile(string filePath);
bool existDirectory(string filePath);
vector<string> GetDirectoryFiles(string dir);
long getFileSize(string inputFile);
long getFilesSize(vector <string> paths);
long freeRam();

int main (int argc, char *argv[]) {
	string pathOut = "/home/";
	string pathDirectory;
	string inputFile(argv[1]);
	vector <fileMemory> fileIn;
	vector <fileMemory> directoryFiles;
	vector <string> paths = getFilesPath(inputFile);;
	vector <string> directoryPaths;

	cout<<"List size: "<< paths.size() <<endl;

	if (freeRam() > getFilesSize(paths)){
		for (int i = 0; i < paths.size(); ++i){

			if (paths[i].find(delimiterFile) != string::npos) {
				string pathAux = getPath(paths[i],delimiterFile);
				if (existFile(pathAux)){
					fileIn.push_back(getFile(pathAux));
				} else {
					cout << "No existe el archivo: "<<pathAux<<", este archivo no se copiara"<<endl;
				}

			} else if (paths[i].find(delimiterDir) != string::npos) {
				string pathAux = getPath(paths[i],delimiterDir);

				if (existDirectory(pathAux)){
					pathDirectory = getDirectoryName(pathAux);
					directoryPaths = GetDirectoryFiles(pathAux);
					for (int j = 0; j < directoryPaths.size(); ++j){
						cout<<"Path File: "<<directoryPaths[j]<<endl;
						directoryFiles.push_back(getFile((pathAux + directoryPaths[j])));
					}
				} else {
					cout << "No existe el directorio: "<<pathAux<<", no se copiara"<<endl;	
				}
			} else {
				cout<<"Error en: "<<paths[i]<<endl;
				return 0;
			}
		}
		cout << "Carga en memoria completada ;)\n\n";
		//ask for final destiny
		while((pathOut.compare("x") != 0) || (pathOut.compare("X") != 0)){
			cout << "Ingrese la ruta destino(\"X\" para salir): ";
		    cin >> pathOut;
		    string directoryPathAux = pathOut+pathDirectory;
		    if (existDirectory(pathOut)){
		    	for (int i = 0; i < fileIn.size(); ++i){
			    	writeFile(fileIn[i],pathOut);
			    }
			    if (directoryFiles.size() > 0){
			    	if (mkdir(directoryPathAux.c_str(),0777) == 0){
			    		for (int i = 0; i < directoryFiles.size(); ++i){
				    		writeFile(directoryFiles[i],(directoryPathAux+"/"));		
				    	}
			    	} else {
			    		cout<<"Ya existe la carpeta: "<< (pathOut+pathDirectory)<<endl;
			    	}
			    }
			    cout << "Copia completada :)"<<endl;
		    } else {	
			    if ((pathOut.compare("x") == 0) || (pathOut.compare("X") == 0)){
			    	cout << "Tarea completada :)"<<endl;
			    	return 0;
			    } else {
			    	cout<<"La direccion destino: "<< pathOut<<" no existe"<<endl;
			    }
			}

		}
	} else {
		cout << "Memoria insuficiente, intente de nuevo :'(" << endl;
	}
	return 0;
}

vector <string> getFilesPath(string textoEntrada){
	vector <string> paths;

	string delimiter=",";

	size_t pos = 0;
	string token;
	while ((pos = textoEntrada.find(delimiter)) != string::npos) {
	    token = textoEntrada.substr(0, pos);
	    paths.push_back(token);

	    textoEntrada.erase(0, pos + delimiter.length());
	}
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
	cout << "Path origin: "<<pathFile << endl;
	return pathFile; 
}

string getFileName(string textoEntrada){

	string delimiter="/";

	size_t pos = 0;
	string token;
	while ((pos = textoEntrada.find(delimiter)) != string::npos) {
	    token = textoEntrada.substr(0, pos);
	    textoEntrada.erase(0, pos + delimiter.length());
	}
	return textoEntrada; 
}

string getDirectoryName(string textoEntrada){

	string delimiter="/";

	size_t pos = 0;
	string token;
	while ((pos = textoEntrada.find(delimiter)) != string::npos) {
	    token = textoEntrada.substr(0, pos);
	    textoEntrada.erase(0, pos + delimiter.length());
	}
	return (token); 
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

bool existFile(string filePath){
	ifstream file (filePath, ios::in|ios::binary|ios::ate);
	if (file.is_open()){
		file.close();
	  	return true;
	} else {
	  	return false;
	}
}

bool existDirectory(string filePath){
	vector<string> files = GetDirectoryFiles(filePath);
	return (files.size() > 0);
}

vector<string> GetDirectoryFiles(string dir) {
	vector<string> files;
	shared_ptr<DIR> directory_ptr(opendir(dir.c_str()), [](DIR* dir){ dir && closedir(dir); });
	struct dirent *dirent_ptr;
	if (!directory_ptr) {
		cout << "Error opening : " << strerror(errno) << dir << endl;
		return files;
	}

	while ((dirent_ptr = readdir(directory_ptr.get())) != nullptr) {
		string nameAux = string(dirent_ptr->d_name);
		if ((nameAux.compare(".") != 0) && (nameAux.compare("..") != 0)){
			files.push_back(nameAux);
		}
	}
	return files;
}

//Return the size en bytes
long getFileSize(string inputFile){
    long size;

    ifstream file (inputFile, ios::in|ios::binary|ios::ate);
    if (file.is_open()) {
        size = file.tellg();
        file.close();
    }
    return size;
}

long getFilesSize(vector <string> paths){
	long filesSize = 0;
	vector <string> directoryPaths;
	string pathDirectory;
	for (int i = 0; i < paths.size(); ++i){

		if (paths[i].find(delimiterFile) != string::npos) {
			string pathAux = getPath(paths[i],delimiterFile);
			if (existFile(pathAux)){
				filesSize += getFileSize(pathAux);
			} else {
				cout << "No existe el archivo: "<<pathAux<<", no se ha calculado su peso"<<endl;
			}

		} else if (paths[i].find(delimiterDir) != string::npos) {
			string pathAux = getPath(paths[i],delimiterDir);

			if (existDirectory(pathAux)){
				pathDirectory = getDirectoryName(pathAux);
				directoryPaths = GetDirectoryFiles(pathAux);
				for (int j = 0; j < directoryPaths.size(); ++j){
					filesSize += getFileSize(pathAux + directoryPaths[j]);
				}
			} else {
				cout << "No existe el directorio: "<<pathAux<<", no se ha calculado su peso"<<endl;	
			}
		} else {
			cout<<"Error en: "<<paths[i]<<endl;
			return 0;
		}
	}
	cout << "Total files Size: "<< filesSize << " bytes"<< endl;
	return filesSize;
}

long freeRam(){
	if (sysinfo(&info) != 0){
        return false;
    }
    long result =info.totalram - info.freeram;
    cout << "Free ram: "<< result <<" bytes"<< endl;
    return result;
}