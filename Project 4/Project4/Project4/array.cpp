#include <iostream>
#include <string>
#include <cmath>
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

int locationOfMax(const string a[], int n){
    if(n<0){ //invalid array length
        return -1;
    }
    int maxIndex = 0; //default max index is 0
    for(int i=0; i<n;i++){
        if(a[i]>=a[maxIndex]){
            maxIndex = i; //updates index
        }
    }
    return maxIndex; //What should I do if empty array is passed? return 0 or -1?
}

int circleLeft(string a[], int n, int pos){
    if(n<0){ //invalid array length
        return -1;
    }
    
    string tmp = a[pos]; //copy the position of item that will be eliminated
    for(int i=pos;i<n;i++){ //start with item that will be eliminated.
        a[i] = a[i+1]; //Move each item forward
    }
    a[n-1]=tmp; //put eliminated item into the last index of the arr.
    return pos;
}

int enumerateRuns(const string a[], int n){
    if(n<0){ //invalid array length
        return -1;
    }
    int count = 0;
    for(int i=0;i<n;i++){
        if(a[i] != a[i+1]){
            count++;
        }
    }
    return count;
}
int flip(string a[], int n){
    if(n<0){ //invalid array length
        return -1;
    }
    string tmp;
    int pointer = n-1;
    for(int i=0;i<n;i++){
        tmp = a[i];
        a[i] = a[pointer];
        a[pointer] = tmp;
        pointer--;
    }
    return n;
}

int locateDifference(const string a1[], int n1, const string a2[], int n2){
    if(n1<0 || n2<0){ //invalid array length
        return -1;
    }
    int minOfN = min(n1,n2);
    for (int i =0; i<minOfN;i++){
        if(a1[i] != a2[i]){
            return i;
        }
    }
    return minOfN;
}

int main(int argc, const char * argv[]) {
    string folks[6] = { "donald", "tim", "", "chris", "nikki", "donald" };
    string group[5] = { "donald", "tim", "donald", "", "chris" };
    int r = locateDifference(folks, 6, group, 5);  //  returns 2
    int s = locateDifference(folks, 2, group, 1);  //  returns 1
    cerr<<r<<endl<<s<<endl;
    return 0;
}
