//
// Created by raghavendra on 12/24/24.
//

#include "../include/ShamirSharing.h"
#include "../overflow/utilities.h"
#include "ranges"
#include "../include/utils/constants.h"

namespace ShamirSharing {
    namespace internal {
        std::vector<int> generate(const int secret, const int threshold) {
            std::vector<int> result;
            result.reserve(threshold);
            result.push_back(secret);
            for (int _: std::views::iota(1, threshold))
                result.push_back(RandomNumber::generate(0, CONSTANTS::MODULUS));
            return result;
        }

        int evaluate(const std::vector<int> &polynomial,const int x) {
            int result = 0;
            for (const int i: std::views::iota(0, static_cast<int>(polynomial.size())))
                result += static_cast<int>(pow(x, i)) * polynomial[i];
            return result % static_cast<int>(CONSTANTS::MODULUS);
        }
        int modularInverse(int a) {
            int p = CONSTANTS::MODULUS;
            a = a % p;
            if (a < 0) a += p; // Ensure a is positive

            int t = 0, new_t = 1; // Coefficients for 'p' and 'a'
            int r = p, new_r = a; // Remainders for 'p' and 'a'

            while (new_r != 0) {
                int quotient = r / new_r;

                // Update t and new_t
                int temp_t = t;
                t = new_t;
                new_t = temp_t - quotient * new_t;

                // Update r and new_r
                int temp_r = r;
                r = new_r;
                new_r = temp_r - quotient * new_r;
            }

            if (r != 1) {
                throw std::invalid_argument("Number is not invertible under the modulus");
            }

            return t < 0 ? t + p : t; // Ensure the result is positive
        }


    }
    std::vector<std::pair<int, int>> generateShares(const int secret, const int num_shares,const int threshold) {
        const std::vector<int> polynomial = internal::generate(secret, threshold);
        std::vector<std::pair<int, int>> result;
        result.reserve(num_shares);
        for (const int i: std::views::iota(1, num_shares + 1))
            result.emplace_back(i, internal::evaluate(polynomial, i));
        return result;
    }

    int reconstructSecret(const std::vector<std::pair<int, int>>& shares) {
        int total = 0;
        const size_t n = shares.size();
        const int MODULUS = CONSTANTS::MODULUS;
        for (size_t i = 0; i < n; ++i) {
            int lagrange_coefficient = 1;
            const auto& [xi, yi] = shares[i];

            for (size_t j = 0; j < n; ++j) {
                if (i == j) continue;
                const auto& [xj, _] = shares[j];

                // Calculate Lagrange coefficient
                lagrange_coefficient *= -xj * internal::modularInverse(xi - xj);
                lagrange_coefficient %= MODULUS;
                // Ensure non-negative lagrange_coefficient
                if (lagrange_coefficient < 0) {
                    lagrange_coefficient += MODULUS;
                }
            }

            // Add to the total
            std::cout << "Lagrange Coefficient: " << lagrange_coefficient << std::endl;
            total += yi * lagrange_coefficient;
            total %= MODULUS;
            std::cout << "Total: " << total << std::endl;

            // Ensure non-negative total
            if (total < 0) {
                total += MODULUS;
            }
        }

        return total;
    }



}
