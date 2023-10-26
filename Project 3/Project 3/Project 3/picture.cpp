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

int main()
{
    setSize(2, 12);  // 2 rows, 12 columns
    assert(plotLine(1, 1, 0, HORIZ, 'H', FG));
    assert(plotLine(1, 2, 0, HORIZ, 'i', FG));
    assert(plotLine(1, 3, 0, HORIZ, '!', FG));
    draw();  //  displays  Hi!  in the top row of the grid
    assert(plotLine(1, 3, 0, HORIZ, ' ', FG));
    draw();  //  displays  Hi   in the top row of the grid
    assert(plotLine(1, 1, 10, HORIZ, ' ', BG));
    draw();  //  displays  Hi   in the top row of the grid
    assert( ! plotLine(1, 1, 10, HORIZ, '\n', FG));
    draw();  //  displays  Hi   in the top row of the grid
}
