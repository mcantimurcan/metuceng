#include <stdio.h>

double calculate_pressure_on_block(int row, int column, double block_weight);
double calculate_helper(int row, int column, double block_weight);

/* TODO: implement your recursive function(s) here */
double calculate_pressure_on_block(int row, int column, double block_weight){
    if (row == 0 && column == 0){
        printf("(%d,%d) %.8f\n", row, column, calculate_helper(row, column, block_weight));
    } else if (column != 0) {
        calculate_pressure_on_block(row, column-1, block_weight);
        printf("(%d,%d) %.8f\n", row, column, calculate_helper(row, column, block_weight));
    } else if (column == 0 && row != 0){
        calculate_pressure_on_block(row-1, row-1, block_weight);
        printf("(%d,%d) %.8f\n", row, column, calculate_helper(row, column, block_weight));
    }
    return 0.0;
}

double calculate_helper(int row, int column, double block_weight){
    if(row == 0 && column == 0){
        return 0;
    } else if (column == 0 && row != 0){
        return (block_weight * 0.5 + 0.15 * calculate_helper(row-1, column, block_weight));
    } else if (column == row && column != 0 && row != 0){
        return (block_weight * 0.5 + 0.15 * calculate_helper(row-1, column-1, block_weight));
    } else {
        return (block_weight + 0.15 * calculate_helper(row-1, column-1, block_weight) + 0.15 * calculate_helper(row-1, column, block_weight));
    }
}

int main() {
    
    /* TODO: Implement here */
    int N, W;
    scanf("%d %d", &N, &W);
    calculate_pressure_on_block(N-1, N-1, W);
    return 0;
}