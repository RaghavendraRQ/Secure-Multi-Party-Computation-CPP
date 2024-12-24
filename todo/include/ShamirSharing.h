//
// Created by raghavendra on 12/24/24.
//

#ifndef SHAMIRSHARING_H
#define SHAMIRSHARING_H
#include <array>

namespace ShamirSharing {
    namespace internal {
        template<unsigned long N>
        std::array<int, N> generate(int secret, int threshold) {
            std::array<int, N> ret;
            for (size_t i = 0; i < N; i++) {
                ret[i] = secret % threshold;
                secret /= threshold;
            }
            return ret;
        }
    }

    template<unsigned long N>
    std::array<std::pair<int, int>, N> generateShares(int secret, int num_shares,int threshold) {
        std::array<std::pair<int, int>, N> ret;
        for (unsigned long i = 0; i < N; i++) {
            ret[i].first = secret % threshold;
            ret[i].second = num_shares % threshold;
            secret /= threshold;
        }
        return ret;
    }

}


#endif //SHAMIRSHARING_H
