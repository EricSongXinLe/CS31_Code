//
//  main.cpp
//  oneFineDay
//
//  Created by Eric on 2023/10/11.
//

#include <iostream>
using namespace std;

int main() {
    string propIdentification;
    bool passedVerification;
    long overstateAmount;
    string location;
    
    passedVerification = false;
    while( not passedVerification){
        cout << "Identification: ";
        getline(cin,propIdentification);
        if (propIdentification == ""){
            cout << "You must enter a property identification." << endl;
            passedVerification = false;
        }
        else{
            passedVerification = true;
        }
    }
    
    passedVerification = false;
    while (not passedVerification){
        cout <<"Overstated amount (in millions): ";
        cin >> overstateAmount;
        if (overstateAmount<=0){
            cout<<"The overstated amount must be positive."<<endl;
            passedVerification = false;
        }
        else{
            passedVerification = true;
        }
    }
    
    passedVerification = false;
    while (not(passedVerification)){
        cout <<"Location: ";
        getline(cin,location);
        if (location == ""){
            cout << "You must enter a location." << endl;
            passedVerification = false;
        }
        else{
            passedVerification = true;
        }
    }
    
    return 0;
}
