#include "grid.h"

void plotHorizontalLine(int r, int c, int distance, char ch){
    const int GRAPH_ROWS = getRows();
    const int GRAPH_COLS = getCols();
    int currentCol;
    for (int i =0; i<=distance;i++){
        currentCol = c+i;
        if (currentCol > GRAPH_COLS || r > GRAPH_ROWS){
            break;
        }
        else{
            setChar(r, currentCol, ch);
        }
    }
}
void plotVerticalLine(int r, int c, int distance, char ch){
    const int GRAPH_ROWS = getRows();
    const int GRAPH_COLS = getCols();
    int currentRow;
    for (int i =0; i<=distance;i++){
        currentRow = r+i;
        if (currentRow > GRAPH_ROWS || c > GRAPH_COLS){
            break;
        }
        else{
            setChar(currentRow, c, ch);
        }
    }
}
void plotRectangle(int r, int c, int height, int width, char ch){
    const int GRAPH_ROWS = getRows();
    const int GRAPH_COLS = getCols();
    plotHorizontalLine(r, c, width, ch);
    plotVerticalLine(r, c, height, ch);
    plotHorizontalLine(r+width, c, width, ch);
    plotVerticalLine(r, c+height, height, ch);
}
int main()
{
    setSize(20, 30);
    plotRectangle(2, 2, 5, 0, '%');
    draw();
}
