#include <iostream>
#include <fstream>
#include <string>
using namespace std;

long getFile(string inputFile){
    long size;

    ifstream file (inputFile, ios::in|ios::binary|ios::ate);
    if (file.is_open()) {
        size = file.tellg();
        file.close();
    }
    return size;
}

int main(){   
    long ans = getFile("th.jpeg");
    if (ans > 1)
       cout<<"size of file is "<<(ans)<< "bytes \n"<< endl;
    return 0;
}