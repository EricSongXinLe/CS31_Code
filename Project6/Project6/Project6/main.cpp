#include <iostream>
using namespace std;

int* nochange(int* p)
{
    return p;
}

int* getPtrToArray(int& m)
{
    int anArray[100];
    for (int j = 0; j < 100; j++)
        anArray[j] = 100-j;
    m = 100;
    return nochange(anArray);
}

void f()
{
    int junk[100];
    for (int k = 0; k < 100; k++)
        junk[k] = 123400000 + k;
    junk[50]++;
}

void removeS(char* msg){
    char* ptr;
    while(*msg != 0){
        if(*msg == 'S' || *msg == 's'){
            ptr = msg;
            while(*ptr != 0){
                *ptr = *(ptr+1);
                ptr++;
            }
        }
        else{
            msg++;
        }
    }
}
int main()
{
    char msg[50] = "She'll blossom like a massless princess.";
    removeS(msg);
    cout << msg;  // prints   he'll bloom like a male prince.
}
