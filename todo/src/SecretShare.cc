//
// Created by raghavendra on 11/28/24.
//

#include "../include/SecretShare.h"


AdditiveSecretShare::AdditiveSecretShare(const int value, const int modulus,
                                         std::vector<int> &shares): shares(std::move(shares)),
                                                                    value(value),
                                                                    modulus(modulus) {
}

AdditiveSecretShare::AdditiveSecretShare(const int value, const int modulus)
    : value(value),
      modulus(modulus) {
    shares = getShares();
}

AdditiveSecretShare::~AdditiveSecretShare() {
    shares.clear();
    std::cout << "AdditiveSecretShare Destructor" << std::endl;
}


std::vector<int> AdditiveSecretShare::getShares() {
    if (shares.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, modulus);
        int first_share = dis(gen);
        int second_share = dis(gen);
        unsigned last_share = (value - first_share - second_share) % modulus;
        shares.emplace_back(first_share);
        shares.emplace_back(second_share);
        shares.emplace_back(last_share);
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
