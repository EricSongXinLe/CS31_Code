#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
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
bool getNextToken(int& tokenType, istream& inf, char token[]){
    char c;
    int tokenIndex= 0;
    while ( inf.get(c) ){ //not at the end of file
        if(isspace(c)){ //end of word
            token[tokenIndex] = '\0'; //Reached the end of word
            tokenType = 1;
            return true;
        }
        else if(c == '-'){
            token[tokenIndex] = c; //add the '-' to string
            tokenType = 2; //Type 2 means the token includes '-', which means a space is not needed between the token and the next token
            tokenIndex++;
            token[tokenIndex] = '\0'; //end this token
            return true;
        }
        else{
            token[tokenIndex] = c; //writes char to token
            tokenIndex++;
        }
    }
    token[tokenIndex] = '\0'; //reached EOF. Write \0 to cstring
    tokenType = 0;
    return false; //can't get next char! reached EoF!
}

void outputToken(int& prevTokenType, int& tokenType, int& countEmptyParagraph,bool& doubleSpace, int& counter, ostream& outf, char token[]){
    if(token[0] == '@' && token[1] == 'P' && token[2] == '@' && strlen(token)==3){ //IF and ONLY IF token is 3 chars long, and only consists of @P@
        if(countEmptyParagraph == 0 && prevTokenType != 2){ //no empty paragraphs have been produced.
            outf<<'\n'<<'\n'; //Output a blank new line and start off a new line
            countEmptyParagraph++;
        }
        else if(countEmptyParagraph == 0 && prevTokenType == 2){ //Basically "@P@-a-@P@" situation
            outf<<token; //Just output @P@, don't output
            counter+=strlen(token);
            prevTokenType = 1; //this token is recognized as a regular word.
        }
        else{
            counter = 0; //
            countEmptyParagraph = 0;//reset empty paragraph, jump to next token.
            doubleSpace = false; //this prevents when running the outputToken the next time, additional spaces are produced.
            return; //By returning, this breaks of the void outputToken function, to avoid to token '@''P''@' from being written to file.
        }
        counter = 0;
        doubleSpace = false; //this prevents when running the outputToken the next time, additional spaces are produced.
        return; //By returning, this breaks of the void outputToken function, to avoid to token '@''P''@' from being written to file.
    }
    if(doubleSpace == true and counter != 0){ //Do not output ' ' if ' 'will be first character
        outf<<' '; //ADDITIONAL SPACE.
        counter++; //increment counter by 1 since one ADDITIONAL Space is produced.
        doubleSpace = false;
    }
    if(counter != 0 && prevTokenType == 1){ //Not first word
        if(token[0] != '\0'){
            outf<<' '; //usual space before word.
            counter++;
        }
    }
    if(token[strlen(token)-1] == '.' || token[strlen(token)-1] == '?' || token[strlen(token)-1] == '!' || token[strlen(token)-1] == ':'){ //'For .?!: at the last char of a token, a additional space is needed.
        doubleSpace = true; //set doubleSpace to be true, so one space will be printed before outputting the next token.
    }
    //ABOVE IS ALL Pre-processing before outputting the token
    outf<<token;
    counter+=strlen(token);
    prevTokenType = tokenType;
}

void processToken(bool& returnOne, int& prevTokenType, int& tokenType, int& countEmptyParagraph, bool& doubleSpace, int& counter, int lineLength, ostream& outf, char token[]){
    int space;
    if(prevTokenType==1){ //if token is a regular word
        space = 1; //should include a space before next token
    }
    else{//if token has '-'
        space = 0;//should NOT include a space before next token
    }
    if(lineLength >= counter + strlen(token)+space){ //This line hasn't finished yet, and can fit additional token & optional space.
        outputToken(prevTokenType, tokenType, countEmptyParagraph, doubleSpace, counter, outf, token);
    }
    else if (lineLength < strlen(token)){ //special case where word
        if(! (prevTokenType==-1)){ // Type -1 means this is the first token every written, therefore do not need to output a new line.
            outf<<'\n';
        }
        returnOne = true;
        int charsToBeWritten = strlen(token); //how many characters will need to be written
        int charsWritten = 0; //already written chars
        while(charsToBeWritten > lineLength){ //While the chars to be written will fit more than one line
            for(int i =charsWritten; i<charsWritten+lineLength;i++){ //write the chars to the whole  line
                outf<<token[i];
            }
            charsToBeWritten-=lineLength; //Change charstobewritten and charsWritten accordingly, to prepare for the next loop
            charsWritten+=lineLength;
            outf<<'\n'; //Go to next line
        }
        for(int i = charsWritten; i<strlen(token);i++){ //The chars can be fitted into one line.
            outf<<token[i];
            counter++; //increment counter accordingly so other normal characters can be fitted into this line.
        }
        prevTokenType = 1; //Type 1 means a space is needed.
    }
    else{
        outf<<'\n'; //new line is needed.
        counter = 0; //reset counter.
        outputToken(prevTokenType, tokenType, countEmptyParagraph, doubleSpace, counter, outf, token);
    }
}

int render(int lineLength, istream& inf, ostream& outf){
    int countEmptyParagraph = 0;
    bool doubleSpace = false;
    if(lineLength < 1){
        return 2; //invalid input
    }
    else{
        int counter = 0; //Counts how many chars was already printed
        char token[MAX];
        int tokenType;
        int prevTokenType=-1; //Default value is -1, because there is no previous token
        bool returnOne = false;
        while(getNextToken(tokenType, inf,token)){
            processToken(returnOne, prevTokenType, tokenType, countEmptyParagraph, doubleSpace, counter, lineLength,outf,token);
        }
        processToken(returnOne, prevTokenType, tokenType, countEmptyParagraph, doubleSpace, counter, lineLength,outf,token);
        //Line above handles the situation getNextToken returns false(reached last token of file) but there is still ONE MORE token that is to be processed.
        if(returnOne == true) //flag is true
            return 1;
        return 0;
    }
}

int main() {
    ifstream infile("input.txt");
    ofstream outfile("result.txt");
    return render(4,infile,outfile);
}
