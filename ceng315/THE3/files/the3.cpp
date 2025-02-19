#include "the3.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below
int find_min_cost(const std::vector<std::vector<int>>& costs, int N){
    if (N <= 1) return 0;
    
    int int_max = 10*N + 1;
    int numPlants = 6;
    std::vector<std::vector<int>> costTable(N-1, std::vector<int>(numPlants, int_max));
    
    for (int i = 0; i < numPlants; i++) {
        costTable[0][i] = costs[0][i];
    }

    for (int i = 1; i < N-1; i++) {
        for (int j = 0; j < numPlants; j++) {
            int cost = costs[i][j];
            for (int prev = 0; prev < numPlants; prev++) {
                if ((j == 0 && prev == 1) ||
                    (j == 1 && prev == 0) ||
                    (j >= 2 && j <= 3 && prev >= 2 && prev <= 3) ||
                    (j >= 4 && j <= 5 && prev >= 4 && prev <= 5)) {
                    continue;
                }
                costTable[i][j] = std::min(costTable[i][j], costTable[i-1][prev] + cost);
            }
        }
    }
    
    int min_cost = costTable[N-2][0];
    for (int i = 0; i < numPlants; i++) {
        min_cost = std::min(min_cost, costTable[N - 2][i]);
    }

    return min_cost;
}
