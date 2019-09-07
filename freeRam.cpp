/*
Links:
http://man7.org/linux/man-pages/man2/sysinfo.2.html
https://stackoverflow.com/questions/349889/how-do-you-determine-the-amount-of-linux-system-ram-in-c
*/

#include <unistd.h>
#include <iostream>
 #include <sys/sysinfo.h>
//#define MINREQ      0xFFF   // arbitrary minimum
using namespace std;

struct sysinfo info;

int main(){
    if (sysinfo(&info) != 0){
        return false;
    }

    long result = info.freeram / 1048576;
    long ram = info.totalram / 1048576;
    long swap = info.totalswap / 1048576;
    long freeswap = info.freeswap / 1048576;
    cout << "Free ram: "<< (ram - result) <<"Mb, Total ram: "<< ram <<"Mb"<< endl;
    cout << "Free swap: "<< freeswap <<"Mb, Total swap: "<< swap <<"Mb"<< endl;
    return 0;
}