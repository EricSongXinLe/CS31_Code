#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;
const int MAX = 180;
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
/* ---------------------PHASE ONE END*/
/* ---------------------PHASE TWO START*/
bool getNextToken(istream& inf, char token[]){
    char c;
    int tokenIndex= 0;
    while ( inf.get(c) ){ //not at the end of file
        if(isspace(c)){ //end of word
            token[tokenIndex] = '\0'; //Reached the end of word
            return true;
        }
        else{
            token[tokenIndex] = c; //writes char to token
            tokenIndex++;
        }
    }
    token[tokenIndex] = '\0'; //reached EOF. Write \0 to cstring
    return false; //can't get next char! reached EoF!
}
void processToken(int& counter, int lineLength, ostream& outf, char token[]){
    if(lineLength >= counter + strlen(token)+1){
        if(counter != 0){
            if(token[0] != '\0'){
                outf<<' ';
                counter++;
            }
        }
        outf<<token;
        counter+=strlen(token);
    }
    else{
        outf<<'\n';
        counter = 0;
        if(counter != 0){
            outf<<' ';
            counter++;
        }
        outf<<token;
        counter += strlen(token);
    }
}
int render(int lineLength, istream& inf, ostream& outf){
    if(lineLength < 1){
        return 2;
    }
    else{
        int counter = 0;
        char token[MAX];
        while(getNextToken(inf,token)){
            processToken(counter, lineLength,outf,token);
        }
        processToken(counter, lineLength,outf,token);
        return 0;
    }
}

int main() {
    ifstream infile("input.txt");
    ofstream outfile("result.txt");
    return render(40,infile,outfile);
}
