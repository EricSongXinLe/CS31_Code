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

void outputToken(bool& doubleSpace, int& counter, ostream& outf, char token[]){
    
    if(token[0] == '@' && token[1] == 'P' && token[2] == '@'){
        outf<<'\n'<<'\n'; //Output a blank new line and start off a new line
        counter = 0;
        doubleSpace = false; //this prevents when running the outputToken the next time, additional spaces are produced.
        return; //By returning, this breaks of the void outputToken function, to avoid to token '@''P''@' from being written to file.
    }
    if(doubleSpace == true){
        outf<<' '; //ADDITIONAL SPACE.
        counter++; //increment counter by 1 since one ADDITIONAL Space is produced.
        doubleSpace = false;
    }
    if(counter != 0){
        if(token[0] != '\0'){
            outf<<' '; //usual space after word.
            counter++;
        }
    }
    if(token[strlen(token)-1] == '.' || token[strlen(token)-1] == '?' || token[strlen(token)-1] == '!' || token[strlen(token)-1] == ':'){ //'For .?!: at the last char of a token, a additional space is needed.
        doubleSpace = true; //set doubleSpace to be true, so one space will be printed before outputting the next token.
    }
    outf<<token;
    counter+=strlen(token);
}

void processToken(bool& doubleSpace, int& counter, int lineLength, ostream& outf, char token[]){
    if(lineLength >= counter + strlen(token)+1){ //This line hasn't finished yet, and can fit additional token & one space.
        outputToken(doubleSpace, counter, outf, token);
    }
    else{
        outf<<'\n';
        counter = 0;
        outputToken(doubleSpace, counter, outf, token);
    }
}

int render(int lineLength, istream& inf, ostream& outf){
    bool doubleSpace = false;
    if(lineLength < 1){
        return 2;
    }
    else{
        int counter = 0;
        char token[MAX];
        while(getNextToken(inf,token)){
            processToken(doubleSpace, counter, lineLength,outf,token);
        }
        processToken(doubleSpace, counter, lineLength,outf,token);
        return 0;
    }
}

int main() {
    ifstream infile("input.txt");
    ofstream outfile("result.txt");
    return render(40,infile,outfile);
}
