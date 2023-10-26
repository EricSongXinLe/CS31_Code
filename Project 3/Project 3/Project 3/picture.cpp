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
bool validPlotLineParameter(int r, int c, int distance, int dir, char plotChar, int fgbg){
    if( !(dir == HORIZ || dir == VERT)){ //DIRECTION is not horizontal or vertical
        return false; //ends this sub-routine
    }
    if( !(fgbg == FG || fgbg == BG)){ //fgbg input is not valid
        return false;
    }
    if(dir == HORIZ){ //only check COLUMN if direction is HORIZONTAL
        if (c+distance <= 0 || c+distance > getCols()){
            return false;
        }
    }
    if(dir == VERT){  //only check ROWS if direction is VERTICAL
        if (r+distance <=0 || r+distance > getRows()){
            return false;
        }
    }
    // r+distance and c+distance calculates the rightmost or leftmost char will be plotted. If the last character is in the plot, the whole line will be in the plot.
    // return false; will be executed when ROW or COL exceeds the boundary of the plot. [ONLY 1 to getRows() or getCols() is accepted.]
    
    if( !isprint(plotChar)){
        return false;
    }
    return true;
}
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg){
    if( !validPlotLineParameter(r, c, distance, dir, plotChar, fgbg)){ //invalid parameter
        return false; //ends funciton
    }
    return true;
}


int main()
{
    setSize(20, 15);  // grid has 20 rows, 15 columns
    if ( ! plotLine(14, 8, 3, HORIZ, '*', FG))   // first call
       cout << "1) Plotting failed when it shouldn't have!" << endl;
    if ( ! plotLine(15, 10, -2, VERT, '@', FG))  // second call
       cout << "2) Plotting failed when it shouldn't have!" << endl;
    if ( ! plotLine(13, 8, 3, HORIZ, '#', BG))   // third call
       cout << "3) Plotting failed when it shouldn't have!" << endl;
    if (plotLine(13, 14, 3, HORIZ, 'X', FG))     // fourth call
       cout << "4) Plotting succeeded when it shouldn't have!" << endl;
    draw();
}
