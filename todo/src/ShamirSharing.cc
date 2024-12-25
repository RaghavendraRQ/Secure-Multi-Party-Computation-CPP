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
            for (int i: std::views::iota(1, threshold))
                result.push_back(RandomNumber::generate(0, CONSTANTS::MODULUS));
            return result;
        }

        int evaluate(const std::vector<int> &secrets,const int x) {
            int result = 0;
            for (int i = 0; i < secrets.size(); i++)
                result += static_cast<int>(pow(x, i)) * secrets[i];
            return result % static_cast<int>(CONSTANTS::MODULUS);
        }
        int modularInverse(const int a) {
            int result = 1, base = a, exp = CONSTANTS::MODULUS - 2;
            while (exp > 0) {
                if (exp % 2 == 1) result = (result * base) % CONSTANTS::MODULUS;
                base = (base * base) % CONSTANTS::MODULUS;
                exp /= 2;
            }
            return result;
        }

    }
    std::vector<std::pair<int, int>> generateShares(const int secret, const int num_shares,const int threshold) {
        const std::vector<int> polynomial = internal::generate(secret, threshold);
        std::vector<std::pair<int, int>> result;
        result.reserve(num_shares);
        for (const int i: std::views::iota(1, num_shares))
            result.emplace_back(i, internal::evaluate(polynomial, i));
        return result;
    }

    int reconstructSecret(const std::vector<std::pair<int, int>> &shares) {
        int total = 0;

        for (size_t i = 0; i < shares.size(); ++i) {
            int lagrange_coefficient = 1;
            const auto& [xi, yi] = shares[i];

            for (size_t j = 0; j < shares.size(); ++j) {
                if (i == j) continue;

                const auto& [xj, _] = shares[j];

                // Compute (xi - xj) mod CONSTANTS::MODULUS
                const int numerator = (CONSTANTS::MODULUS - xj) % CONSTANTS::MODULUS; // -xj mod MODULUS
                const int denominator = (xi - xj + CONSTANTS::MODULUS) % CONSTANTS::MODULUS; // xi - xj mod MODULUS
                const int denominator_inverse = internal::modularInverse(denominator); // modular inverse of denominator

                // Update lagrange_coefficient
                lagrange_coefficient = (lagrange_coefficient * numerator % CONSTANTS::MODULUS) * denominator_inverse % CONSTANTS::MODULUS;
                std::cout << lagrange_coefficient << std::endl;
            }

            // Update total
            total = (total + yi * lagrange_coefficient) % CONSTANTS::MODULUS;
        }

        // Ensure total is non-negative
        if (total < 0) {
            total += CONSTANTS::MODULUS;
        }

        return total;
    }


}
