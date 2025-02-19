#include "the6.h"

// do not add extra libraries here

std::vector< std::vector<float> > get_friendship_scores(const std::vector< std::vector< std::pair<int, int> > >& network){
    return std::vector<std::vector<float> >((int)network.size(), std::vector<float>((int)network.size(), 1));
}
