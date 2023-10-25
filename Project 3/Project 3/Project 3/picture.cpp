#include "grid.h"

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
    plotHorizontalLine(r+width, c, width, ch); //change the 'row' parameter
    plotVerticalLine(r, c+height, height, ch); //change the 'column' parameter
}
int main()
{
    setSize(20, 30);
    plotRectangle(2, 2, 5, 5, '%');
    draw();
}
