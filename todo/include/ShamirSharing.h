//
// Created by raghavendra on 12/23/24.
//

#ifndef SHAMIRSHARING_H
#define SHAMIRSHARING_H
#include <array>

template<int size>
struct Polynomial {
    std::array<int, size> _polynomial;

    explicit Polynomial(std::array<int, size>& _poly);

    static Polynomial generate(int secret, int threshold);
};

template<int size>
class ShamirSharing {
    ShamirSharing
    () = default;

    static std::array<std::pair<int, int>, size>  generate(int secret, int num_share, int threshold);
};

#endif //SHAMIRSHARING_H
