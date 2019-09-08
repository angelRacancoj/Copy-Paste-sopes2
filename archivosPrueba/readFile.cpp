/*
Link:
http://www.codebind.com/cpp-tutorial/cpp-program-list-files-directory-windows-linux/
*/

#include <dirent.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <memory> 
#include <sys/stat.h> 
#include <sys/types.h>
using namespace std;

vector<string> GetDirectoryFiles(string dir) {
  vector<string> files;
  shared_ptr<DIR> directory_ptr(opendir(dir.c_str()), [](DIR* dir){ dir && closedir(dir); });
  struct dirent *dirent_ptr;
  if (!directory_ptr) {
    cout << "Error opening : " << strerror(errno) << dir << endl;
    return files;
  }
 
  while ((dirent_ptr = readdir(directory_ptr.get())) != nullptr) {
    files.push_back(string(dirent_ptr->d_name));
  }
  return files;
}

int main() {
  string directory_path ="Screenshots/";
  vector<string> files = GetDirectoryFiles(directory_path);
  
  for (int i = 0; i < files.size(); ++i)
  {
    cout<<"File: "<<files[i]<<endl;
  }

  string directoryPathAux = "holaMundo";
  if (mkdir(directoryPathAux.c_str(),0777) == 0){
    cout<<"Directorio creado"<<endl;
  }

  return 0;
}