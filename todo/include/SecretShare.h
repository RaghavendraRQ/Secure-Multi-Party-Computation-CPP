//
// Created by raghavendra on 11/28/24.
//

#ifndef SECRETSHARE_H
#define SECRETSHARE_H


#include <vector>
#include <iostream>
#include <random>


class AdditiveSecretShare {
public:
    std::vector<int> shares;
    int value;
    int modulus;

    AdditiveSecretShare(int value, int modulus, std::vector<int> &shares);

    AdditiveSecretShare(int value, int modulus);

    ~AdditiveSecretShare();

    std::vector<int> getShares();

    void printShares() const;

    int computeShares();
};

#endif //SECRETSHARE_H
