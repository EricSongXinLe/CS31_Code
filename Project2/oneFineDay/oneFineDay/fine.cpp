#include <iostream>
using namespace std;

int main() {
    string propIdentification;
    string location;
    double overstateAmount = 0;
    double fine = 0;
    double lowFineRate = 0.153;
    double highFineRate = 0.18;
    double secondaryFineRate;
    int deciPrecision = 3;
    
    cout << "Identification: ";
    getline(cin,propIdentification);
    if (propIdentification == ""){
        cout << "---" << endl;
        cout << "You must enter a property identification." << endl;
        return 1;
    }
    
    
    cout <<"Overstated amount (in millions): ";
    cin >> overstateAmount;
    cin.ignore(10000, '\n');
    if (overstateAmount<=0){
        cout << "---" << endl;
        cout<<"The overstated amount must be positive."<<endl;
        return 1;
    }

    
    cout <<"Location: ";
    getline(cin,location);
    if (location == ""){
        cout << "---" << endl;
        cout << "You must enter a location." << endl;
        return 1;
    }
    

    if (location == "florida" || location == "new york"){
        secondaryFineRate = highFineRate;
    }
    else{
        secondaryFineRate = lowFineRate;
    }
    
    if (overstateAmount <= 60){
        fine = overstateAmount*0.1111;
    }
    else if (overstateAmount <=150){
        fine = 60*0.1111+(overstateAmount-60)*secondaryFineRate;
    }
    else{
        fine = 60*0.1111+90*secondaryFineRate+(overstateAmount-150)*0.21;
    }
    cout<<"---"<<endl;
    cout.setf(ios::fixed);
    cout.precision(deciPrecision);
    cout<<"The fine for "<<propIdentification<<" is $"<<fine<<" million."<<endl;
    return 0;
}
