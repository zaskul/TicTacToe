#include <stdio.h>
#include <string.h>


void fillBoard(int boardSize, char board[boardSize][boardSize][4]) {
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++)
        {
            strcpy(board[i][j], "[ ]");
        }
    }
}

void displayBoard(int boardSize, char board[boardSize][boardSize][4]){
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++)
        {
            printf("%s", board[i][j]);
        }
        printf("\n");
    }
}

int main() {

    int boardSize;
//    scanf("%d", &boardSize);

    boardSize = 3;
    char board[boardSize][boardSize][4];

    fillBoard(boardSize, board);

    displayBoard(boardSize, board);


    return 0;
}
