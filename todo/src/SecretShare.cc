//
// Created by raghavendra on 11/28/24.
//

#include "../include/SecretShare.h"


AdditiveSecretShare::AdditiveSecretShare(const int value, const int modulus,
                                         std::vector<int> &shares): shares(std::move(shares)),
                                                                    value(value),
                                                                    modulus(modulus) {
}

AdditiveSecretShare::AdditiveSecretShare(const int value, const int modulus, const int num_share)
    : value(value),
      modulus(modulus) {
    shares = getShares(num_share);
}

AdditiveSecretShare::~AdditiveSecretShare() {
    shares.clear();
}


std::vector<int> AdditiveSecretShare::getShares(const int& num_shares) {
    if (shares.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, modulus);
        shares.reserve(num_shares);
        for (size_t i = 1; i < num_shares; ++i)
            shares.emplace_back(dis(gen));
        int random_share_sum = 0;
        for (const int &share: shares)
            random_share_sum += share;
        int remainder = (value - random_share_sum) % modulus;
        shares.emplace_back(remainder);
    }
    return shares;
}

void AdditiveSecretShare::printShares() const {
    if (not shares.empty())
        for (const auto& share: shares)
            std::cout << share << " ";
    std::cout << "\n";
}

int AdditiveSecretShare::computeShares() {
    int sum = 0;
    for (const auto share: shares)
        sum += share;
    return sum % modulus;
}
