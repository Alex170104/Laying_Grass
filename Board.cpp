#include "Board.h"
#include <vector>

using namespace std;

Board::Board(int nbPlayer) {
    int size;
    int vector<vector<int>> grid;

    if (2 =< nbPlayer < 5){
        size = 20;
    }
    else{
        size = 30;
    }
    grid = vector<vector<int>>(size, vector<int>(size, 0));

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            grid[i][j] = 0;
        }
    }




}