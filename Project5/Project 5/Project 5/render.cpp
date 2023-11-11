#include <iostream>
#include <fstream>
using namespace std;
/* ---------------------PHASE ONE START*/
int main() {
    ofstream outfile("/Users/eric/Desktop/UCLA/2023-24/Q1/COM SCI 31/Code/Project5/results.txt");
    if ( ! outfile ){
        cerr << "Error: Cannot create results.txt!" << endl;
        
    }
    else{
        outfile << "This will be written to the file" << endl;
        outfile << "2 + 2 = " << 2+2 << endl;
    }
    return 0;
}
/* ---------------------PHASE ONE END*/
