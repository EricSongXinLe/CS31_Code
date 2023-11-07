#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
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
    if(n<=0){ //invalid array length
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
    if(n<0 || n < pos+1){ //invalid array length
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
    for(int i=0;i<n/2;i++){
        tmp = a[i];
        a[i] = a[pointer];
        a[pointer] = tmp;
        pointer--; //Traverse back
    }
    return n;
}

int locateDifference(const string a1[], int n1, const string a2[], int n2){
    if(n1<0 || n2<0){ //invalid array length
        return -1;
    }
    int minOfN = min(n1,n2); //only loops the shorter length of the array
    for (int i =0; i<minOfN;i++){
        if(a1[i] != a2[i]){
            return i;
        }
    }
    return minOfN;
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
    if(n1<0 || n2<0){ //invalid array length
        return -1;
    }
    else if(n2 == 0){
        return 0; //a sequence of 0 elements to be a subsequence of any sequence at pos 0
    }
    int j = 0;
    for(int i=0; i<n1;i++){ //loops through the whole a1 array
        if(a1[i] == a2[j]){ //matching start
            j++;
        }
        else{ //no more overlap
            if(j==n2){ //all elements in a2 have been looped, complete match
                return i-n2;
            }
            else{ //incomplete match
                j=0; //resets j index
                if(a1[i] == a2[j]){ //matching start
                    j++;
                }
            }
        }
    }
    return -1;
}
int locateAny(const string a1[], int n1, const string a2[], int n2){
    if(n1<0 || n2<0){ //invalid array length
        return -1;
    }
    for(int i=0;i<n1;i++){
        for(int j=0;j<n2;j++){ //for each element in a1, iterate a2 to find any matching elements.
            if(a1[i] == a2[j]){
                return i;
            }
        }
    }
    return -1;
}

int divide(string a[], int n, string divider){
    if(n<0){ //invalid array length
        return -1;
    }
    string tmp;
    for(int i=0;i<n;i++){
        //
    }
}

int main(int argc, const char * argv[]) {
    const int ARI = 6;
    string stuff[ARI] = { "CS", "31", "Test", "", "Cases", "." };
    return 0;
}
