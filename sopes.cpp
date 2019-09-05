#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main()
{
    char* buffer;
    char linearray[250];
    int lineposition;
    double filesize;
    string linedata;
    string a;

    //obtain the file
    FILE *inputfile;
    inputfile = fopen("archivo1.txt", "r");

    //find the filesize
    fseek(inputfile, 0, SEEK_END);
    filesize = ftell(inputfile);
    rewind(inputfile);

    //load the file into memory
    buffer = (char*) malloc (sizeof(char)*filesize);      //allocate mem
    fread (buffer,filesize,1,inputfile);         //read the file to the memory
    fclose(inputfile);

    //Check to see if file is correct in Memory
    cout.write(buffer,filesize);

    free(buffer);
}