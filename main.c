#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <Windows.h>
#include <ctype.h>

// fills the board with empty tiles
void fillBoard(int boardSize, int board[boardSize][boardSize]) {
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            board[i][j] = 0;
        }
    }
}

struct KeyValuePair {
    int key;
    char value[4];
};

// displays the current state of the board
void displayBoard(int boardSize, int board[boardSize-1][boardSize-1]){

    // assigns correct symbol to the corresponding value
    struct KeyValuePair displayableTiles[] = {
            {0, "[ ]"},
            {1, "[X]"},
            {2, "[O]"}
    };
    int rowLabel = 1;
    int counter = 0;
    char columnLabel = 65;

    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
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
                // displays the tiles
            else {
                printf("%s", displayableTiles[board[i][j]].value);
            }
        }
        printf("\n");
    }
}

bool rowCheck(int boardSize, int board[boardSize][boardSize], int initialRow, int turn){
    int wantedResult = turn * boardSize;
    int sumOfRow = 0;
    for (int i = 0; i < boardSize; i++){
        sumOfRow += (board[initialRow][i] == turn) ? turn : 0;
    }
    return (sumOfRow == wantedResult) ? true : false;
}

bool columnCheck(int boardSize, int board[boardSize][boardSize], int initialColumn, int turn){
    int wantedResult = turn * boardSize;
    int sumOfColumn = 0;
    for (int i = 0; i < boardSize; i++){
        sumOfColumn += (board[i][initialColumn] == turn) ? turn : 0;
    }
    return (sumOfColumn == wantedResult) ? true : false;
}

bool diagonalCheck(int boardSize, int board[boardSize][boardSize], int initialRow, int initialColumn, int turn){
    int wantedResult = turn * boardSize;
    int sumOfTopToBottom = 0;
    int sumOfBottomToTop = 0;
    int j = boardSize-1;
    // checks both diagonals
    if ((initialRow == initialColumn) && boardSize % 2 != 0){
        for (int i = 0; i < boardSize; i++){
            sumOfTopToBottom += (board[i][i] == turn) ? turn : 0 ;
            sumOfBottomToTop += (board[i][j-i] == turn) ? turn : 0;
        }
        return (sumOfTopToBottom == wantedResult|| sumOfBottomToTop == wantedResult) ? true : false;
    }
    // checks top to bottom diagonal
    else if (initialRow == initialColumn){
        for (int i = 0; i < boardSize; i++){
            sumOfTopToBottom += (board[i][i] == turn) ? turn : 0;
        }
        return (sumOfTopToBottom == wantedResult) ? true : false;
    }
    // checks bottom to top diagonal
    else{
        for (int i = 0; i < boardSize; i++){
            sumOfBottomToTop += (board[i][j-i] == turn) ? turn : 0;
        }
        return (sumOfBottomToTop == wantedResult) ? true : false;
    }
}

int victoryCheck(int boardSize, int board[boardSize][boardSize], int turn, int initialRow, int initialColumn) {
    // check if diagonal win is possible
    if ((initialRow == initialColumn) || (initialRow + initialColumn == boardSize-1)){
        if (diagonalCheck(boardSize, board, initialRow, initialColumn, turn)){
            return turn;
        }
    }
    // check the row and column win conditions
    if (rowCheck(boardSize, board, initialRow, turn) || columnCheck(boardSize, board, initialColumn, turn)){
            return turn;
    }
    return 0;
}

// check if winning conditions are met
void victory(int victoryState, bool *gameOnPtr, int boardSize, int board[boardSize][boardSize]){
    if (victoryState == 1){
        system("cls");
        displayBoard(boardSize+1, board);
        printf("X won");
        *gameOnPtr = false;
    }
    else if(victoryState == 2){
        system("cls");
        displayBoard(boardSize+1, board);
        printf("O won");
        *gameOnPtr = false;
    }
}

void playerMove(int boardSize, int board[boardSize][boardSize], int turn, bool *gameOnPtr, int *turnPtr){
    char move[4];
    int row;
    char column;
    int columnIntValue;
    // read player input
    if (fgets(move, sizeof(move), stdin) != NULL){
        // check if correct the size of input is correct
        if(move[strlen(move) - 1] != '\n'){
            printf("Incorrect move, please try again.");
            Sleep(1000);
            // clear input buffer until newline character
            while (getchar() != '\n');
        }
        else
        {
            // get the int and char values from the input string
            // remove the newline if there is one
            move[strcspn(move, "\n")] = '\0';
            // char, int order
            if (sscanf(move, "%c%d", &column, &row) == 2){
                columnIntValue = (int)toupper(column)-65;
                // check if out of bounds
                if (columnIntValue >= boardSize || row-1 >= boardSize){
                    printf("Tile out of bounds");
                    Sleep(1000);
                    return;
                }
                if (board[row-1][columnIntValue] == 0){
                    // converts to ASCII value of the letter and subtracts for correct column index
                    board[row-1][columnIntValue] = turn;
                    victory(victoryCheck(boardSize, board, turn, row-1, columnIntValue), gameOnPtr, boardSize, board);
                    *turnPtr = (turn == 2) ? 1 : 2;
                }
                else{
                    printf("Tile is already occupied or is invalid");
                    Sleep(1000);
                }

            }
            else{
                // int, char order
                char *endPointer;
                row = strtol(move, &endPointer, 10);

                if (*endPointer != '\0'){
                    columnIntValue = (int)toupper(column)-65;
                    // check if out of bounds
                    if (columnIntValue >= boardSize || row-1 >= boardSize){
                        printf("Tile out of bounds");
                        Sleep(1000);
                        return;
                    }
                    if (board[row-1][columnIntValue] == 0){
                    column = *endPointer;
                    board[row-1][columnIntValue] = turn;
                    victory(victoryCheck(boardSize, board, turn, row-1, columnIntValue), gameOnPtr, boardSize, board);
                    *turnPtr = (turn == 2) ? 1 : 2;
                    }
                    else{
                        printf("Tile is already occupied or is invalid");
                        Sleep(1000);
                    }
                }
                else{
                    printf("Incorrect input");
                    Sleep(1000);
                }
            }
        }
    }
    else{
        printf("Error of reading input.");
        Sleep(1000);
    }
}


int main() {
    int boardSize;
    bool gameOn = true;
    bool *gameOnPtr = &gameOn;
    int turn = 1;
    int *turnPtr = &turn;

//    scanf("%d", &boardSize);

    boardSize = 3; // max 10
    int board[boardSize][boardSize];

    fillBoard(boardSize, board);

    while(gameOn){
        system("cls");
        displayBoard(boardSize + 1, board);
        playerMove(boardSize, board, turn, gameOnPtr, turnPtr);

    }

    return 0;
}
