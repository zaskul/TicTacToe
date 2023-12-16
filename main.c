#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// fill the board with empty tiles
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
void displayBoard(int boardSize, int board[boardSize][boardSize], struct KeyValuePair displayableTiles[3]){
    int rowLabel = 1;
    int counter = 0;
    char columnLabel = 65;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++)
        {
            // responsible for printing the letters of alphabet as labels for columns
            if (i == boardSize - 1){
                if (counter == i) continue;
                printf(" %c ", columnLabel);
                columnLabel++;
                counter++;
            }
            // responsible for printing digits as labels for rows
            else if (j == boardSize - 1){
                printf(" %d", rowLabel);
                rowLabel++;
            }
            // displays the tile state
            else{
                printf("%s", displayableTiles[board[i][j]].value);
            }
        }
        printf("\n");
    }
}

void playerMove(int boardSize, int board[boardSize][boardSize]){
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
                board[(int)column-65][row-1] = 1;
            }
            else
            {
                // int, char order
                char *endPointer;
                row = strtol(move, &endPointer, 10);
                if (*endPointer != '\0')
                {
                    column = *endPointer;
                    board[(int)column-65][row-1] = 1;

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

    struct KeyValuePair displayableTiles[] = {
            {0, "[ ]"},
            {1, "[X]"},
            {2, "[O]"}
    };

    int boardSize;
    bool gameOn = true;
//    scanf("%d", &boardSize);

    boardSize = 3; // max 10
    int board[boardSize][boardSize];

    fillBoard(boardSize, board);

    displayBoard(boardSize + 1, board, displayableTiles);
    playerMove(boardSize, board);
    displayBoard(boardSize + 1, board, displayableTiles);


    return 0;
}
