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
        if(a[i]>a[maxIndex]){
            maxIndex = i; //updates index
        }
    }
    return maxIndex; //What should I do if empty array is passed? return 0 or -1?
}

int circleLeft(string a[], int n, int pos){
    if(n<=0 || n < pos+1 || pos < 0){ //invalid array length
        return -1;
    }
    
    string tmp = a[pos]; //copy the position of item that will be eliminated
    for(int i=pos;i<n-1;i++){ //start with item that will be eliminated.
        a[i] = a[i+1]; //Move each item forward
    }
    a[n-1]=tmp; //put eliminated item into the last index of the arr.
    return pos;
}

int enumerateRuns(const string a[], int n){
    if(n<0){ //invalid array length
        return -1;
    }
    int count = 1;
    for(int i=0;i<n;i++){
        if(i+1<n && a[i] != a[i+1]){
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
    int pointer = n-1; //points to the other side of the array
    for(int i=0;i<n/2;i++){
        tmp = a[i];
        a[i] = a[pointer];
        a[pointer] = tmp; //swap the two numbers
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
    if(n1<0 || n2<0 || n2 > n1){ //invalid array length
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
                return i-n2+1;
            }
            else{ //incomplete match
                j=0; //resets j index
                if(a1[i] == a2[j]){ //matching start
                    j++;
                }
            }
        }
        if(j==n2){ //all elements in a2 AND a1 have been looped, complete match
            return i-n2+1;
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
    //bubble sort the array
    for(int i=0;i<n-1;i++){
        for(int j=0; j<n-i-1;j++){
            if(a[j]>a[j+1]){ //if current element is greater than next element
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp; //swap two elements
            }
        }
    }
    for(int i=0;i<n;i++){
        if( a[i] >= divider){ //found first element that is greater than or equal to divder
            return i;
        }
    }
    return n;
}

int main() {
    string h[7] = { "nikki", "ron", "asa", "vivek", "", "chris", "donald" };
    assert(locate(h, 7, "chris") == 5);
    assert(locate(h, 7, "asa") == 2);
    assert(locate(h, 2, "asa") == -1);
    assert(locationOfMax(h, 7) == 3);

    string g[4] = { "nikki", "ron", "chris", "tim" };
    assert(locateDifference(h, 4, g, 4) == 2);
    assert(circleLeft(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "ron");

    string c[4] = { "ma", "can", "tu", "do" };
    assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");

    string e[4] = { "asa", "vivek", "", "chris" };
    assert(subsequence(h, 7, e, 4) == 2);

    string d[5] = { "ron", "ron", "ron", "chris", "chris" };
    assert(enumerateRuns(d, 5) == 2);

    string f[3] = { "vivek", "asa", "tim" };
    assert(locateAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "tim" && f[2] == "vivek");

    assert(divide(h, 7, "donald") == 3);

    cout << "All tests succeeded" << endl;
}
