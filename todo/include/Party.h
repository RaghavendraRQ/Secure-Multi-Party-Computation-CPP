//
// Created by raghavendra on 11/28/24.
//

#ifndef PARTY_H
#define PARTY_H
#include <vector>

class Party {
public:
    int modulus;
    std::vector<int> client_shares;

    Party(std::vector<int>& client_shares, int modulus);
};

class SMPCAdditionParty: public Party {
public:
    unsigned int partial_sum{0};
    SMPCAdditionParty(std::vector<int>& client_shares, int modulus);
    int computePartialSum();
};

#endif //PARTY_H
