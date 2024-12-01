//
// Created by raghavendra on 11/28/24.
//

#include "../include/Party.h"

Party::Party(std::vector<int> &client_shares, const int modulus): modulus(modulus),
                                                                  client_shares(std::move(client_shares)) {
}


SMPCAdditionParty::SMPCAdditionParty(std::vector<int> &client_shares, const int modulus): Party(client_shares,
    modulus) {
}

int SMPCAdditionParty::computePartialSum() {
    partial_sum = 0;
    for (const auto share: client_shares) {
        partial_sum += share;
    }
    return partial_sum % modulus;
}
