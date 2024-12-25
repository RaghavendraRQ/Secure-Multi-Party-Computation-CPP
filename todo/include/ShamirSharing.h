//
// Created by raghavendra on 12/24/24.
//

#ifndef SHAMIRSHARING_H
#define SHAMIRSHARING_H
#include <vector>

namespace ShamirSharing {
    namespace internal {
        std::vector<int> generate(int secret, int threshold);
        int evaluate(const std::vector<int>& secrets, int x);
        int modularInverse(int a);
    }

    std::vector<std::pair<int, int>> generateShares(int secret, int num_shares,int threshold);

    int reconstructSecret(const std::vector<std::pair<int, int>>& shares);


}


#endif //SHAMIRSHARING_H
