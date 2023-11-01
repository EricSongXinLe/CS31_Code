#include "grid.h"
#include <cctype>
#include <iostream>
#include <cassert>
using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;
//-------------------START-----OF----PHASE----ONE----------------//
void plotHorizontalLine(int r, int c, int distance, char ch){
    const int GRAPH_ROWS = getRows(); //check the maximum column/row in the graph.
    const int GRAPH_COLS = getCols();
    int currentCol;
    for (int i =0; i<=distance;i++){ //Print distance+1 'ch's.
        currentCol = c+i; //increments the column
        if (currentCol > GRAPH_COLS || r > GRAPH_ROWS){ //exceeds the maximum column/row
            break; //exits the loop
        }
        else{
            setChar(r, currentCol, ch); //prints character
        }
    }
}
void plotVerticalLine(int r, int c, int distance, char ch){
    const int GRAPH_ROWS = getRows();
    const int GRAPH_COLS = getCols();
    int currentRow;
    for (int i =0; i<=distance;i++){ //Print distance+1 'ch's.
        currentRow = r+i; //increments the row
        if (currentRow > GRAPH_ROWS || c > GRAPH_COLS){ //exceeds the maximum column/row
            break;
        }
        else{
            setChar(currentRow, c, ch);
        }
    }
}
void plotRectangle(int r, int c, int height, int width, char ch){
    plotHorizontalLine(r, c, width, ch);
    plotVerticalLine(r, c, height, ch);
    plotHorizontalLine(r+width, c, width, ch); //update the 'row' parameter to draw new line
    plotVerticalLine(r, c+height, height, ch); //update the 'column' parameter to draw new line
}

//-------------------END-----OF----PHASE----ONE----------------//

//-------------------START-----OF----PHASE----TWO----------------//

bool validHorizDistance(int c, int distance){
    //only check COLUMN if direction is HORIZONTAL
    if (c+distance <= 0 || c+distance > getCols()){
        return false;
    }
    return true;
}

bool validVertDistance(int r, int distance){
    //only check ROWS if direction is VERTICAL
    if (r+distance <=0 || r+distance > getRows()){
        return false;
    }
    return true;
}
// r+distance and c+distance calculates the rightmost or leftmost char will be plotted. If the last character is in the plot, the whole line will be in the plot.
// return false; will be executed when ROW or COL exceeds the boundary of the plot. [ONLY 1 to getRows() or getCols() is accepted.]

bool validFgbg(int fgbg){
    if( !(fgbg == FG || fgbg == BG)){ //fgbg input is not valid
        return false;
    }
    return true;
}

bool validChar(char plotChar){
    if( !isprint(plotChar)){
        return false;
    }
    return true;
}


bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg){
    if (dir == HORIZ){ //DRAW HORIZONTAL LINE
        if ( !validHorizDistance(c, distance)){ //INVALID HORIZONTAL DISTANCE
            return false;
        }
        if ( !(validChar(plotChar) && validFgbg(fgbg))){ //Char and Fgbg is NOT BOTH valid
            return false;
        }
        if (distance >=0){
            if (fgbg == FG){
                for (int i =0; i<=distance;i++){ //Print the character at distance +1
                    setChar(r, c+i, plotChar); //For all HORIZ lines, col changes every time it loops.
                }
            }
            else{ //BG
                for (int i =0; i<=distance;i++){ //Print the character at distance +1
                    if(getChar(r, c+i)==' '){
                        setChar(r, c+i, plotChar);
                    }
                }
            }
            return true;
        }
        else{ //DISTANCE <0;
            if (fgbg == FG){
                for (int i =0; i<= (0-distance);i++){ //Print distance+1 'ch's.
                    setChar(r, c-i, plotChar); // c-i because the line is going the other direction.
                }
            }
            else{ //BG
                for (int i =0; i<= (0-distance);i++){ //Print BG
                    if(getChar(r, c-i)==' '){
                        setChar(r, c-i, plotChar);
                    }
                }
            }
            return true;
        }
    }
    else if (dir == VERT){ //DRAW VERTICAL LINE
        if ( !validVertDistance(r, distance)){ //INVALID VERTICAL DISTANCE
            return false;
        }
        if ( !(validChar(plotChar) && validFgbg(fgbg))){ //Char and Fgbg is NOT BOTH valid
            return false;
        }
        if (distance >=0){
            if (fgbg == FG){
                for (int i =0; i<=distance;i++){ //Print distance+1 'ch's.
                    setChar(r+i, c, plotChar);
                }
            }
            else{ //BG
                for (int i =0; i<=distance;i++){ //Print BG
                    if(getChar(r+i, c)==' '){
                        setChar(r+i, c, plotChar);
                    }
                }
            }
            return true;
        }
        else{ //REVERSELY
            if (fgbg == FG){
                for (int i =0; i<= (0-distance);i++){ //Print distance+1 'ch's.
                    setChar(r-i, c, plotChar);
                }
            }
            else{ //BG
                for (int i =0; i<= (0-distance);i++){ //Print BG
                    if(getChar(r-i, c)==' '){ //ABLE TO PRINT
                        setChar(r-i, c, plotChar);
                    }
                }
            }
            return true;
        }
    }
    else{ //INVALID DIR
        return false;
    }
}
//-------------------END-----OF----PHASE----TWO----------------//

//-------------------START-----OF----PHASE----THREE----------------//
bool checkCommands(string commandString, int& badPos){
    int j=0;
    while (j!=commandString.size()){
        if(commandString.at(j) == 'C' || commandString.at(j) == 'c'){
            j++;
            continue;
        }
        else if(commandString.at(j) == 'F' || commandString.at(j) == 'f'){
            if(j!= commandString.size()-1){ //F is followed by char
                if(validChar(commandString.at(j+1))){
                    j+=2;//Move to the next next character.
                }
                else{
                    badPos = j+1;
                    return false;
                }
            }
            else{ //Commands ended with F.
                badPos = j+1;
                return false;
            }
        }
        else if(commandString.at(j) == 'B' || commandString.at(j) == 'b'){
            if(j!= commandString.size()-1){ //B is followed by char
                if(validChar(commandString.at(j+1))){
                    j+=2;//Move to the next next character.
                }
                else{
                    badPos = j+1;
                    return false;
                }
            }
            else{ //Commands ended with B.
                badPos = j+1;
                return false;
            }
        }
        else if(commandString.at(j) == 'H' || commandString.at(j) == 'h' || commandString.at(j) == 'V' || commandString.at(j) == 'v'){
            if(j!= commandString.size()-1){ //H is followed by char
                j++; //Move to the next next character.
                if(48 <= commandString.at(j) && commandString.at(j) <= 57){ // 48 equals to '0', 57 equals to '9', ASCII code is continuous.
                    if(j!= commandString.size()-1){ //This is not the last character.
                        if(48 <= commandString.at(j+1) && commandString.at(j+1) <= 57){
                            //2-digit, NO '-' sign situation
                            j+=2;
                        }
                        else{
                            //1-digit, NO '-' sign situation
                            j++;
                        }
                    }
                    else{
                        //THIS is the last character of the COMMAND.
                        return true;
                    }
                }
                else if(commandString.at(j)=='-'){
                    j++;
                    //'- sign situation'
                    if(j!= commandString.size()){ //'-' is not the last character.
                        if(j!= commandString.size()-1){ //Another character follows after H-_ or H-__ command.
                            if(48 <= commandString.at(j) && commandString.at(j) <= 57 && 48 <= commandString.at(j+1) && commandString.at(j+1) <= 57){ //BOTH digits are number
                                //2-digit, '-' sign situation
                                j+=2;
                            }
                            else{
                                //ONLY 1 character after '-' - Followed by command situation
                                if(48 <= commandString.at(j) && commandString.at(j) <= 57){
                                    j++;
                                }
                                else{
                                    badPos = j;
                                    return false;
                                }
                            }
                        }
                        else{
                            if(48 <= commandString.at(j) && commandString.at(j) <= 57){
                                j++;
                            }
                            else{
                                badPos = j;
                                return false;
                            }
                        }
                    }
                    else{
                        //'-' is the last character of the COMMAND.
                        badPos = j;
                        return false;
                    }
                }
                else{
                    badPos = j;
                    return false;
                }
            }
            else{ //Commands ended with H/V.
                badPos = j+1;
                return false;
            }
        }
        else{ //INVALID command
            badPos = j;
            return false;
        }
    }
    return true;
}
int performCommands(string commandString, char& plotChar, int& mode, int& badPos){
    int i =0;
    int c = 1;
    int r = 1;
    int distance;
    string twoDigits = "";
    if (!validChar(plotChar)){
        return 2;
    }
    if (!validFgbg(mode)){
        return 2;
    }
    if (!checkCommands(commandString, badPos)){
        return 1; //SYNTAX ERROR in COMMANDS
        //Do not need to reassign badPos, because &badPos is linked.
    }
    
    while(i!=commandString.size()){
        //IF BRANCHES:
        //1. 'H' or 'h' [FOLLOWED BY NUMBER or '-' AND NUMBER]
        //2. 'V' or 'v' [FOLLOWED BY NUMBER or '-' AND NUMBER]
        //3. 'C' or 'c' (SETS grid to all spaces, CurrentPos to [1,1], CurrentChar to '*', FG mode)
        //4. 'F' or 'f' [FOLLOWED BY ONE CHAR]
        //5. 'B' or 'b' [FOLLOWED BY ONE CHAR]
        //WRITING UP Code for C/F/B Types
        if(commandString.at(i) == 'C' || commandString.at(i) == 'c'){
            //SETS grid to all spaces, CurrentPos to [1,1], CurrentChar to '*', FG mode
            clearGrid();
            plotChar = '*';
            mode = FG;
            c=1;
            r=1;
            i++;
            continue; //Processing of 'C' is complete
        }
        else if (commandString.at(i) == 'F' || commandString.at(i) == 'f'){
            i++; // Proceed to next character
            mode =  FG;
            plotChar = commandString.at(i); //set mode and char
            i++;
            //Proceed to next character
            continue;
            
        }
        else if (commandString.at(i) == 'B' || commandString.at(i) == 'b'){
            i++;
            mode =  BG;
            plotChar = commandString.at(i); //set mode and char
            i++;
            //Proceed to next character
            continue;
            
        }
        else if(commandString.at(i) == 'H' || commandString.at(i) == 'h'){
            i++;//move to next char
            if(48 <= commandString.at(i) && commandString.at(i) <= 57){ //nextchar is num
                if(i!=commandString.size()-1){
                    //not the end yet!
                    if(48 <= commandString.at(i+1) && commandString.at(i+1) <= 57){
                        //2-digit, no -sign.
                        twoDigits = string(1,commandString.at(i)) + commandString.at(i+1);
                        distance = stoi(twoDigits);
                        if(validHorizDistance(c, distance)){
                            plotLine(r,c,distance,HORIZ,plotChar,mode);
                            i+=2; //finished plotting line, move 2 characters foward.
                            c+=distance;
                        }
                        else{
                            badPos = i-1; //OUT of RANGE
                            return 3;
                        }
                    }
                    else{
                        //1 digit, no -sign
                        distance = commandString.at(i) - 48; //Converts back to int if subtracts 48 from char ASCII value
                        if(validHorizDistance(c, distance)){
                            plotLine(r,c,distance,HORIZ,plotChar,mode);
                            i++; //finished plotting line, move 1 characters foward.
                            c+=distance;
                            
                        }
                        else{
                            badPos = i-1; //OUT of RANGE
                            return 3;
                        }
                    }
                }
                else{
                    //LAST NUMBER
                    distance = commandString.at(i) - 48; //Converts back to int if subtracts 48 from char ASCII value
                    if(validHorizDistance(c, distance)){
                        plotLine(r,c,distance,HORIZ,plotChar,mode);
                        i++; //finished plotting line, move 1 characters foward.
                        c+=distance;
                    }
                    else{
                        badPos = i-1; //OUT of RANGE
                        return 3;
                    }
                }
            }
            else{
                //Must be '-'sign.
                i++; //Move across - sign
                if(48 <= commandString.at(i) && commandString.at(i) <= 57){ //nextchar is num
                    if(i!=commandString.size()-1){
                        //not the end yet!
                        if(48 <= commandString.at(i+1) && commandString.at(i+1) <= 57){
                            //2-digit, no -sign.
                            twoDigits = string(1,commandString.at(i)) + commandString.at(i+1);
                            distance = 0-stoi(twoDigits);
                            if(validHorizDistance(c, distance)){
                                plotLine(r,c,distance,HORIZ,plotChar,mode);
                                i+=2; //finished plotting line, move 2 characters foward.
                                c+=distance;
                            }
                            else{
                                badPos = i-2; //OUT of RANGE
                                return 3;
                            }
                        }
                        else{
                            //1 digit,  -sign
                            distance = 0-(commandString.at(i) - 48); //Converts back to int if subtracts 48 from char ASCII value
                            if(validHorizDistance(c, distance)){
                                plotLine(r,c,distance,HORIZ,plotChar,mode);
                                i++; //finished plotting line, move 1 characters foward.
                                c+=distance;
                            }
                            else{
                                badPos = i-2; //OUT of RANGE
                                return 3;
                            }
                        }
                    }
                    else{
                        //LAST NUMBER
                        distance = 0-(commandString.at(i) - 48); //Converts back to int if subtracts 48 from char ASCII value
                        if(validHorizDistance(c, distance)){
                            plotLine(r,c,distance,HORIZ,plotChar,mode);
                            i++; //finished plotting line, move 1 characters foward.
                            c+=distance;
                        }
                        else{
                            badPos = i-2; //OUT of RANGE
                            return 3;
                        }
                    }
                }
            }
            
        }
        else if(commandString.at(i) == 'V' || commandString.at(i) == 'v'){
            i++;//move to next char
            if(48 <= commandString.at(i) && commandString.at(i) <= 57){ //nextchar is num
                if(i!=commandString.size()-1){
                    //not the end yet!
                    if(48 <= commandString.at(i+1) && commandString.at(i+1) <= 57){
                        //2-digit, no -sign.
                        twoDigits = string(1,commandString.at(i)) + commandString.at(i+1);
                        distance = stoi(twoDigits);
                        if(validVertDistance(r, distance)){
                            plotLine(r,c,distance,VERT,plotChar,mode);
                            i+=2; //finished plotting line, move 2 characters foward.
                            r+=distance;
                        }
                        else{
                            badPos = i-1; //OUT of RANGE
                            return 3;
                        }
                    }
                    else{
                        //1 digit, no -sign
                        distance = commandString.at(i) - 48; //Converts back to int if subtracts 48 from char ASCII value
                        if(validVertDistance(r, distance)){
                            plotLine(r,c,distance,VERT,plotChar,mode);
                            i++; //finished plotting line, move 1 characters foward.
                            r+=distance;
                        }
                        else{
                            badPos = i-1; //OUT of RANGE
                            return 3;
                        }
                    }
                }
                else{
                    //LAST DIGIT is NUMBER
                    distance = commandString.at(i) - 48; //Converts back to int if subtracts 48 from char ASCII value
                    if(validVertDistance(r, distance)){
                        plotLine(r,c,distance,VERT,plotChar,mode);
                        i++; //finished plotting line, move 1 characters foward.
                        r+=distance;
                    }
                    else{
                        badPos = i-1; //OUT of RANGE
                        return 3;
                    }
                }
            }
            else{
                //Must be '-'sign.
                i++; //Move across - sign
                if(48 <= commandString.at(i) && commandString.at(i) <= 57){ //nextchar is num
                    if(i!=commandString.size()-1){
                        //not the end yet!
                        if(48 <= commandString.at(i+1) && commandString.at(i+1) <= 57){
                            //2-digit, no -sign.
                            twoDigits = string(1,commandString.at(i)) + commandString.at(i+1);
                            distance = 0-stoi(twoDigits);
                            if(validVertDistance(r, distance)){
                                plotLine(r,c,distance,VERT,plotChar,mode);
                                i+=2; //finished plotting line, move 2 characters foward.
                                r+=distance;
                            }
                            else{
                                badPos = i-2; //OUT of RANGE
                                return 3;
                            }
                        }
                        else{
                            //1 digit, no -sign
                            distance = 0-(commandString.at(i) - 48); //Converts back to int if subtracts 48 from char ASCII value
                            if(validVertDistance(r, distance)){
                                plotLine(r,c,distance,VERT,plotChar,mode);
                                i++; //finished plotting line, move 1 characters foward.
                                r+=distance;
                            }
                            else{
                                badPos = i-2; //OUT of RANGE
                                return 3;
                            }
                        }
                    }
                    else{
                        //LAST DIGIT is NUMBER
                        distance = 0-(commandString.at(i) - 48); //Converts back to int if subtracts 48 from char ASCII value
                        if(validVertDistance(r, distance)){
                            plotLine(r,c,distance,VERT,plotChar,mode);
                            i++; //finished plotting line, move 1 characters foward.
                            r+=distance;
                        }
                        else{
                            badPos = i-2; //OUT of RANGE
                            return 3;
                        }
                    }
                }
            }
            
        }
    }
    return 0; //GOOD TO DRAW
}

int main()
{
    for (;;)
    {
        cout << "Enter the number of grid rows and columns (max 30 each): ";
        int nRows;
        int nCols;
        cin >> nRows >> nCols;
        cin.ignore(10000, '\n');
        if (nRows >= 1  &&  nRows <= MAXROWS  &&  nCols >= 1  &&  nCols <= MAXCOLS)
        {
            setSize(nRows, nCols);
            break;
        }
        cout << "The numbers must be between 1 and 30." << endl;
    }
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string (empty line to quit): ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = performCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
          case 0:
            draw();
            break;
          case 1:
            cout << "Syntax error at position " << position << endl;
            break;
          case 2:
            if (!isprint(currentChar))
                cout << "Current character is not printable" << endl;
            if (currentMode != FG  &&  currentMode != BG)
                cout << "Current mode is " << currentMode << ", not FG or BG" << endl;
            break;
          case 3:
            cout << "Cannot perform command at position " << position << endl;
            break;
          default:
              // It should be impossible to get here.
            cout << "performCommands returned " << status << "!" << endl;
        }
    }
}
