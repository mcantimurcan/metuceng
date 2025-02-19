#include "the4.h"

// DO NOT CHANGE ABOVE THIS LINE!
// You may implement helper functions below

int tasty_cake_helper(unsigned short w, 
                      unsigned short h, 
                      bool** perfect_cuts, 
                      std::vector<std::vector<int>>& cake_dp_table) 
{
    if (perfect_cuts[w][h]) {
        return w * h;
    }

    if (cake_dp_table[w][h] != -1) {
        return cake_dp_table[w][h];
    }

    int max_tasty_cake = 0;

    for (int cut = 1; cut < h; cut++) {
        int calculated_tasty_cake = tasty_cake_helper(w, cut, perfect_cuts, cake_dp_table) + tasty_cake_helper(w, h - cut, perfect_cuts, cake_dp_table);
        max_tasty_cake = std::max(max_tasty_cake, calculated_tasty_cake);
    }

    for (int cut = 1; cut < w; cut++) {
        int calculated_tasty_cake = tasty_cake_helper(cut, h, perfect_cuts, cake_dp_table) + tasty_cake_helper(w - cut, h, perfect_cuts, cake_dp_table);
        max_tasty_cake = std::max(max_tasty_cake, calculated_tasty_cake);
    }

    cake_dp_table[w][h] = max_tasty_cake;

    return cake_dp_table[w][h];
}

unsigned int alice_cutting_cake(const unsigned short cake_width,
                                const unsigned short cake_height,
                                bool **perfect_cuts){
    std::vector<std::vector<int>> cake_dp_table(cake_width + 1, std::vector<int>(cake_height + 1, -1));
    int total_area = cake_width * cake_height;
    int tasty_area = tasty_cake_helper(cake_width, cake_height, perfect_cuts, cake_dp_table);
    int wasted_area = total_area - tasty_area;
    return wasted_area;
}