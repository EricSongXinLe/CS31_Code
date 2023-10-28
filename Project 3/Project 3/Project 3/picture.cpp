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
int performCommands(string commandString, char& plotChar, int& mode, int& badPos){
    int i =0;
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
            //SET pos to 1,1 pending
            i++;
            continue; //Processing of 'C' is complete
        }
        else if (commandString.at(i) == 'F' || commandString.at(i) == 'f'){
            if (i!= commandString.size()-1){ //F is followed by a command
                i++; // Proceed to next character
                if(validChar(commandString.at(i))){ //Able to proceed with program
                    mode =  FG;
                    plotChar = commandString.at(i); //set mode and char
                    i++;
                    //Proceed to next character
                    continue;
                }
                else{ //inprintable character
                    return 2;
                }
            }
            else{ // command string ends but a character is expected
                badPos = commandString.size();
                return 1;
            }
        }
        else if (commandString.at(i) == 'B' || commandString.at(i) == 'b'){
            if (i!= commandString.size()-1){ //F is followed by a command
                i++; // Proceed to next character
                if(validChar(commandString.at(i))){ //Able to proceed with program
                    mode =  BG;
                    plotChar = commandString.at(i); //set mode and char
                    i++;
                    //Proceed to next character
                    continue;
                }
                else{ //inprintable character
                    return 2;
                }
            }
            else{ // command string ends but a character is expected
                badPos = commandString.size();
                return 1;
            }
        }
        
    }
    return 0;
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
