#include <iostream>
#include <string>
using namespace std;

int locate(const string a[], int n, string target){
    if(n<0){
        return -1;
    }
    for(int i=0; i<n;i++){
        if (a[i] == target){
            return i;
        }
    }
    return -1;
}
int main(int argc, const char * argv[]) {
    string people[5] = { "donald", "vivek", "tim", "asa", "nikki" };
    int i = locate(people, 5, "nikki");
    cerr <<i<<endl;
    return 0;
}
