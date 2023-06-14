#include <stdio.h>
#include <stdlib.h>

int isValidPosition(char **labyrinth, int x, int y, int rowSize, int colSize) {
    return (y >= 0 && y < rowSize - 2 && x >= 0 && x < colSize - 1 && labyrinth[y][x] == ' ');
}

int solveLabyrinth(char **labyrinth, int x, int y, int rowSize, int colSize) {
    int **visited_stack, top = 0, i;
    
    visited_stack = (int**)malloc(sizeof(int*) * (rowSize * colSize));
    
    for(i = 0; i < rowSize * colSize; i++){
        visited_stack[i] = (int*)malloc(sizeof(int)*2);
    }
    
    visited_stack[top][0] = x;
    visited_stack[top][1] = y;
    
    while (top >= 0) {
        x = visited_stack[top][0];
        y = visited_stack[top][1];
        top--;
        
        if ((x == 0 || y == 0 || y == rowSize - 2 || x == colSize - 1) && labyrinth[y][x] == ' ') {
            labyrinth[y][x] = '*';
            return 1;
        }
        
        if (isValidPosition(labyrinth, x, y, rowSize, colSize)) {
            labyrinth[y][x] = '*';
            
            visited_stack[++top][0] = x+1; 
            visited_stack[top][1] = y;

            visited_stack[++top][0] = x;
            visited_stack[top][1] = y+1;

            visited_stack[++top][0] = x-1;
            visited_stack[top][1] = y;

            visited_stack[++top][0] = x;
            visited_stack[top][1] = y-1;
        } 
    }
    return 0;
}

void markLabyrinth(char **labyrinth, int rowSize, int colSize) {
    int i, j;
    for(i=0; i<rowSize-1; i++){
        for(j=0; j<colSize; j++){
            if(labyrinth[i][j] == '*'){
                labyrinth[i][j] = '.';
            }
        }
    }
}

int main() {
    int startX, startY, rowSize, colSize, i, j;
    char **labyrinth;
    labyrinth = (char**)malloc(sizeof(char*) * 33333);
    scanf("%d %d", &startX, &startY);
    
    rowSize = 0;
    while (getchar() != EOF) {
        labyrinth[rowSize] = (char*)malloc(sizeof(char) * 33333);
        scanf("%[^\n]", labyrinth[rowSize]);
        rowSize++;
    }

    colSize = 0;
    while (labyrinth[0][colSize] != '\0') {
        colSize++;
    }

    labyrinth = (char**)realloc(labyrinth, sizeof(char*) * rowSize);
    for (i = 0; i < rowSize; i++) {
        labyrinth[i] = (char*)realloc(labyrinth[i], sizeof(char) * colSize); 
    }
    
    if (solveLabyrinth(labyrinth, startX, startY, rowSize, colSize) == 0) {
        markLabyrinth(labyrinth, rowSize, colSize);
    } 
    
    for (i = 0; i < rowSize-1; i++) {
        for(j = 0; j < colSize; j++){
            if (labyrinth[i][j] != '\0'){
                printf("%c", labyrinth[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}
