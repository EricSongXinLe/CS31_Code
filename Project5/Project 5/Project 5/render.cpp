#include <iostream>
#include <fstream>
using namespace std;
const int MAX = 100;
/* ---------------------PHASE ONE START*/
bool writeFile(string dir){
    ofstream outfile(dir);
    if ( ! outfile ){
        cerr << "Error: Cannot write out file!" << endl;
        return false; //failed to write file
    }
    else{
        outfile << "This will be written to the file" << endl;
        outfile << "2 + 2 = " << 2+2 << endl; //writes file
        return true;
    }
}
void greet(ostream& outf)    // outf is a name of our choosing
    {
        outf << "Hello" << endl;
    }

int countLines(istream& inf)   // inf is a name of our choosing
    {
        int lineCount = 0;
        string line;
        while (getline(inf, line))
            lineCount++;
        return lineCount;
    }

bool readFile(string dir){
    ifstream infile(dir);
    if(! infile){
        cerr << "Error: Cannot read in file!" << endl;
        return false;
    }
    else{
        char line[MAX];
        infile.getline(line, MAX);
        return true;
    }
}
int main() {
    ifstream infile("/Users/eric/Desktop/UCLA/2023-24/Q1/COM SCI 31/Code/Project5/results.txt");
    if ( ! infile )
    {
        cerr << "Error: Cannot open data.txt!" << endl;
        return 1;
    }
    int fileLines = countLines(infile);  // reads from the file data.txt
    cout << "data.txt has " << fileLines << " lines." << endl;
    cout << "Type lines, then ctrl-Z (Windows) or ctrl-D (macOS/Linux):" << endl;
    int keyboardLines = countLines(cin); // reads from keyboard
    cout << "You typed " << keyboardLines << " lines." << endl;
    return 0;
}
/* ---------------------PHASE ONE END*/
