#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// fills the board with empty tiles
void fillBoard(int boardSize, int board[boardSize][boardSize]) {
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = 0;
        }
    }
}

struct KeyValuePair{
    int key;
    char value[4];
};


// displays the current state of the board
void displayBoard(int boardSize, int board[boardSize-1][boardSize-1], struct KeyValuePair displayableTiles[3]) {
    int rowLabel = 1;
    int counter = 0;
    char columnLabel = 65;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            // responsible for printing the letters of alphabet as labels for columns
            if (i == boardSize - 1) {
                if (counter == i) continue;
                printf(" %c ", columnLabel);
                columnLabel++;
                counter++;
            }
                // responsible for printing digits as labels for rows
            else if (j == boardSize - 1) {
                printf(" %d", rowLabel);
                rowLabel++;
            }
                // displays the tile state
            else {
                printf("%s", displayableTiles[board[i][j]].value);
            }
        }
        printf("\n");
    }
}

bool rowCheck(int boardSize, int board[boardSize][boardSize], int initialRow, int turn){
    // if the max amount of 'X' or 'O' (1's or 2's) value on board is equal to the current value, it is considered a win on one of the sides
    int wantedResult = turn * boardSize;
    int sumOfRow = 0;
    for (int i = 0; i < boardSize; i++){
        sumOfRow += board[initialRow][i];
    }
    return (sumOfRow == wantedResult) ? true : false;
}

bool columnCheck(int boardSize, int board[boardSize][boardSize], int initialColumn, int turn){
    int wantedResult = turn * boardSize;
    int sumOfColumn = 0;
    for (int i = 0; i < boardSize; i++){
        sumOfColumn += board[i][initialColumn];
    }
    return (sumOfColumn == wantedResult) ? true : false;
}

bool diagonalCheck(int boardSize, int board[boardSize][boardSize], int initialRow, int initialColumn, int turn){
    int wantedResult = turn * boardSize;
    int sumOfTopToBottom = 0;
    int sumOfBottomToTop = 0;
    int j = boardSize-1;
    // checks both diagonals
    if ((initialRow == initialColumn) && boardSize % 2 != 0) {
        for (int i = 0; i < boardSize; i++) {
            sumOfTopToBottom += board[i][i];
            sumOfBottomToTop += board[i][j-i];
        }
        return (sumOfTopToBottom == wantedResult|| sumOfBottomToTop == wantedResult) ? true : false;
    }
    // checks top to bottom diagonal
    else if (initialRow == initialColumn){
        for (int i = 0; i < boardSize; i++) {
            sumOfTopToBottom += board[i][i];
        }
        return (sumOfTopToBottom == wantedResult) ? true : false;
    }
    // checks bottom to top diagonal
    else{
        for (int i = 0; i < boardSize; i++) {
            sumOfBottomToTop += board[i][j-i];
        }
        return (sumOfBottomToTop == wantedResult) ? true : false;
    }
}

void victoryCheck(int boardSize, int board[boardSize][boardSize], int turn, int initialRow, int initialColumn) {
    // check if possible diagonal win
    if ((initialRow == initialColumn) || (initialRow + initialColumn == boardSize-1)){
        if (diagonalCheck(boardSize, board, initialRow, initialColumn, turn)){
            printf("GAME OVER DIAGONAL\n");
        }
    }
    else if (rowCheck(boardSize, board, initialRow, turn) || columnCheck(boardSize, board, initialColumn, turn)){
        printf("GAME OVER\n");
    }
}

void playerMove(int boardSize, int board[boardSize][boardSize], int turn){
    char move[4];
    int row;
    char column;

    // read player input
    if (fgets(move, sizeof(move), stdin) != NULL){
        // check if correct the size of input is correct
        if(move[strlen(move) - 1] != '\n'){
            printf("%c", move[strlen(move) - 1]);
            printf("Incorrect move, please try again.\n");
            while (getchar() != '\n');
        }
        else
        {
            // get the int and char values from the input string
            // remove the newline if there is one
            move[strcspn(move, "\n")] = '\0';
            // char, int order
            if (sscanf(move, "%c%d", &column, &row) == 2)
            {
                // converts to ASCII value of the letter and subtracts for correct column index
                board[row-1][(int)column-65] = turn;
                victoryCheck(boardSize, board, turn, row-1, (int)column-65);
            }
            else
            {
                // int, char order
                char *endPointer;
                row = strtol(move, &endPointer, 10);
                if (*endPointer != '\0')
                {
                    column = *endPointer;
                    board[row-1][(int)column-65] = turn;
                    victoryCheck(boardSize, board, turn, row-1, (int)column-65);
                }
                else
                {
                    printf("Incorrect input");
                }
            }
        }
    }
    else
    {
        printf("Error of reading input.");
    }
}



int main() {

    // assigns correct symbol to the corresponding value
    struct KeyValuePair displayableTiles[] = {
            {0, "[ ]"},
            {1, "[X]"},
            {2, "[O]"}
    };

    int boardSize;
    bool gameOn = true;
//    scanf("%d", &boardSize);

    boardSize = 4; // max 10
    int board[boardSize][boardSize];

    fillBoard(boardSize, board);

    while(gameOn){
        displayBoard(boardSize + 1, board, displayableTiles);
        playerMove(boardSize, board, 1);
    }

    return 0;
}
