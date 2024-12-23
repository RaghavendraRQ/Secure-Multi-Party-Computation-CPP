//
// Created by raghavendra on 12/23/24.
//
#include <ranges>
#include <../todo/include/ShamirSharing.h>
#include <../todo/overflow/utilities.h>
#include <../todo/include/utils/constants.h>

template<int size>
Polynomial<size> Polynomial<size>::generate(int secret, int threshold) {
    _polynomial[0] = secret;
    for (const size_t i: std::views::iota(1, threshold))
        _polynomial[i] = RandomNumber::generate(0, CONSTANTS::MODULUS);

    return Polynomial<size>(_polynomial);
}

template<int size>
Polynomial<size>::Polynomial(std::array<int, size>& _poly): _polynomial(_poly) {}


template<int size>
std::array<std::pair<int, int>, size> ShamirSharing<size>::generate(int secret, int num_share, int threshold) {
    Polynomial<size> polynomial = Polynomial<size>::generate(secret, threshold);
    return NULL;
}
