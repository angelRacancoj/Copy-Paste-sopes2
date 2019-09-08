/*
Links source:
http://www.cplusplus.com/doc/tutorial/files/
https://databasefaq.com/index.php/answer/39431/c-11-ram-file-format-recognizing-file-formats-from-binary-c-
http://www.cplusplus.com/doc/tutorial/files/
*/

// reading an entire binary file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

std::ifstream::pos_type filesize(const char* filename);

int main (int argc, char *argv[]) {
  streampos size;
  char * memblock;
  string pathOut;
  string pathConcat;
  string inputFile(argv[1]);


  ifstream file (inputFile, ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    memblock = new char [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();

    cout << "the entire file content is in memory"<<endl;
    cout << "Ingrese la ruta destino: ";
    cin >> pathOut;

    pathConcat = pathOut + inputFile;

    cout << "Path destino: "<< pathConcat <<endl;

    ofstream fileout(pathConcat, ios::out | ios::binary);
    fileout.write(memblock, size);  
    fileout.close();

    delete[] memblock;
  }
  else cout << "Unable to open file"<<endl;
  return 0;
}

std::ifstream::pos_type filesize(const char* filename) {
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}