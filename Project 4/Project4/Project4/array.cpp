#include <iostream>
#include <string>
using namespace std;
int reduplicate(string a[], int n){
    if(n<0){ //invalid array length
        return -1;
    }
    for(int i=0; i<n;i++){
        a[i].append(a[i]); //appends itself into element.
    }
    return n;
}
int locate(const string a[], int n, string target){
    if(n<0){ //invalid array length
        return -1;
    }
    for(int i=0; i<n;i++){
        if (a[i] == target){ //found target
            return i; //return index
        }
    }
    return -1;
}
int main(int argc, const char * argv[]) {
    string stuff[6] = { "mahi", "bon", "cous", "", "tar", "mur" };
    int i = reduplicate(stuff, 6);
    for (int i =0; i<6;i++){
        cerr<<stuff[i]<<endl;
    }
    cerr <<i<<endl;
    return 0;
}
