#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <sstream>
#include <streambuf>
#include <cassert>
using namespace std;
const int MAX = 180;
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

void outputToken(int lineLength, int& prevTokenType, int& tokenType, int& countEmptyParagraph,bool& doubleSpace, int& counter, ostream& outf, char token[]){
    if(token[0] == '@' && token[1] == 'P' && token[2] == '@' && strlen(token)==3){ //IF and ONLY IF token is 3 chars long, and only consists of @P@
        if (counter == 0){ //if the first token is a @P@, no new paragraph should be produced.
            return;
        }
        else if(countEmptyParagraph == 0 && prevTokenType != 2){ //no empty paragraphs have been produced.
            outf<<'\n'<<'\n'; //Output a blank new line and start off a new line
            countEmptyParagraph++;
        }
        else if(countEmptyParagraph == 0 && prevTokenType == 2){ //Basically "@P@-a-@P@" situation
            outf<<token; //Just output the token, don't output empty paragraphs
            counter+=strlen(token);
            prevTokenType = 1; //this token is recognized as a regular word.
        }
        else if(countEmptyParagraph!=0 and (!(token[0] == '@' && token[1] == 'P' && token[2] == '@' && strlen(token)==3))){
            counter = 0; //
            countEmptyParagraph = 0;//reset empty paragraph, jump to next token.
            doubleSpace = false; //this prevents when running the outputToken the next time, additional spaces are produced.
            return; //By returning, this breaks of the void outputToken function, to avoid to token '@''P''@' from being written to file.
        }
        counter = 0;
        doubleSpace = false; //this prevents when running the outputToken the next time, additional spaces are produced.
        return; //By returning, this breaks of the void outputToken function, to avoid to token '@''P''@' from being written to file.
    }
    if((doubleSpace == true and counter != 0) and (not (token[0] == '\0'))){ //Do not output ' ' if ' 'will be first character
        if(counter+2+strlen(token)>lineLength){ //We can't fit the 2 spaces & char, must  start a new line
            outf<<'\n'; //go to next line
            counter=0;
            doubleSpace = false;
        }
        else{ //this line can fit 2 spaces and a token
            outf<<' '; //ADDITIONAL SPACE.
            counter++; //increment counter by 1 since one ADDITIONAL Space is produced.
            doubleSpace = false;
        }
    }
    else if(doubleSpace == true and counter == 0){
        doubleSpace = false; //prev Double space resets.
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
    if(prevTokenType==1 and token[0]!='\0' and counter != 0){ //if token is a regular word, and is not an empty token
        space = 1; //should include a space before next token
    }
    else{//if token has '-', or is empty token
        space = 0;//should NOT include a space before next token
    }
    if(lineLength >= counter + strlen(token)+space){ //This line hasn't finished yet, and can fit additional token & optional space.
        outputToken(lineLength, prevTokenType, tokenType, countEmptyParagraph, doubleSpace, counter, outf, token);
    }
    else if (lineLength < strlen(token)){
        //special case where word
        if(! (prevTokenType==-1)){ // Type -1 means this is the first token every written, therefore do not need to output a new line.
            outf<<'\n';
        }
        returnOne = true;
        size_t charsToBeWritten = strlen(token); //how many characters will need to be written
        int charsWritten = 0; //already written chars
        while(charsToBeWritten > lineLength){ //While the chars to be written will fit more than one line
            for(int i =charsWritten; i<charsWritten+lineLength;i++){ //write the chars to the whole  line
                outf<<token[i];
            }
            charsToBeWritten-=lineLength; //Change charstobewritten and charsWritten accordingly, to prepare for the next loop
            charsWritten+=lineLength;
            outf<<'\n'; //Go to next line
        }
        counter = 0;
        for(int i = charsWritten; i<strlen(token);i++){ //The chars can be fitted into one line.
            outf<<token[i];
            counter++; //increment counter accordingly so other normal characters can be fitted into this line.
        }
        prevTokenType = 1; //Type 1 means a space is needed.
    }
    else{
        if(not(token[0] == '@' && token[1] == 'P' && token[2] == '@' && strlen(token)==3)){ //IF THE token already makes a new line
            outf<<'\n'; //new line is needed.
            counter = 0; //reset counter.
        }
        outputToken(lineLength, prevTokenType, tokenType, countEmptyParagraph, doubleSpace, counter, outf, token);
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
        if(token[0] == '@' && token[1] == 'P' && token[2] == '@' && strlen(token)==3){ //if the last token is "@P@", just return new line and end program. The very last output paragraph must not be followed by an empty line.
            outf<<'\n';
            if(returnOne == true) //flag is true
                return 1;
            return 0;
        }
        processToken(returnOne, prevTokenType, tokenType, countEmptyParagraph, doubleSpace, counter, lineLength,outf,token);
        if((!(counter == 0))){
            outf<<'\n'; //last token must be followed by a \n char.
            //Line above handles the situation getNextToken returns false(reached last token of file) but there is still ONE MORE token that is to be processed.
        }
        if(returnOne == true) //flag is true
            return 1;
        return 0;
    }
}
void testRender(int lineLength, const char input[], const char expectedOutput[], int expectedReturnValue)
{
    istringstream iss(input);
    ostringstream oss;
    ostringstream dummy;
    streambuf* origCout = cout.rdbuf(dummy.rdbuf());
    int retval = render(lineLength, iss, oss);
    cout.rdbuf(origCout);
    if ( ! dummy.str().empty())
        cerr << "WROTE TO COUT INSTEAD OF THIRD PARAMETER FOR: " << input << endl;
    else if (retval != expectedReturnValue)
        cerr << "WRONG RETURN VALUE FOR: " << input << endl;
    else if (retval == 2)
    {
        if ( ! oss.str().empty())
            cerr << "WROTE OUTPUT WHEN LINELENGTH IS " << lineLength << endl;
    }
    else if (oss.str() != expectedOutput)
        cerr << "WRONG RESULT FOR: " << input << endl;
}
int main() {
    ifstream infile("input3.txt");
    ofstream outfile("result.txt");
    testRender(7, "This\n\t\tis a\ntest\n", "This is\na test\n", 0);
    testRender(8, "  This is a test  \n", "This is\na test\n", 0);
    testRender(6, "Testing it\n", "Testin\ng it\n", 1);
    testRender(-5, "irrelevant", "irrelevant", 2);
    return render(10,infile,outfile);
}
