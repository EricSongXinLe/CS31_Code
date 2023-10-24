#include "grid.h"

void plotHorizontalLine(int r, int c, int distance, char ch){
    for (int i =0; i<distance;i++){
        setChar(r, c+distance, ch);
    }
    //function IN PROGRESS, MISSING CODE
}
int main()
{
    setSize(20, 30);
    for (int r = 3; r <= 9; r += 2)
        plotHorizontalLine(r, 13, 17, '=');
    for (int r = 11; r <= 17; r += 2)
        plotHorizontalLine(r, 1, getCols()-1, '=');
    for (int r = 3; r <= 9; r += 2)
        for (int c = 1; c <= 11; c += 2)
            setChar(r, c, '*');
    for (int r = 4; r <= 8; r += 2)
        for (int c = 2; c <= 10; c += 2)
            setChar(r, c, '*');
    draw();
}
