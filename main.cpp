#include <memory>
#include <ranges>

#include "todo/include/SecretShare.h"
#include "todo/include/Party.h"
#include "todo/include/utils/constants.h"
#include "todo/include/utils/ShareUtils.h"
#include "todo/include/ShamirSharing.h"

#include "todo/overflow/utilities.h"


void testFunction();

void testShamir();

int main() {
    // testFunction();
    testShamir();
    return 0;
}

void testFunction() {
    std::uint16_t value_count;
    std::cout << "*************** Offline Phase ***************" << std::endl;
    std::cout << "Modulus value: " << CONSTANTS::MODULUS << std::endl;
    std::cout << "Share Count: " << CONSTANTS::SHARE_COUNT << std::endl;
    std::cout << "Enter a No.of Values: ";
    std::cin >> value_count;
    std::vector<int> values(value_count);

    static_assert(std::is_same<decltype(value_count), std::uint16_t>{}, "Value Count should be positive integer");

    // for_each loop IOTA-creates a view from 0, value_count
    std::ranges::for_each(std::views::iota(0, static_cast<int>(value_count)), [&](const int i) {
        std::cout << "Enter the value of " << (i+1) << "th value: ", std::cin >> values[i];
    });


    std::vector<std::shared_ptr<AdditiveSecretShare>> secretShares;
    secretShares.reserve(value_count);

    for (size_t i = 0; i < value_count; i ++)
        secretShares.emplace_back(std::make_shared<AdditiveSecretShare>(values[i], CONSTANTS::MODULUS, value_count));

    std::vector<std::vector<int>> shares(value_count);

    for (size_t i = 0; i < value_count; ++i) {
        shares[i] = secretShares[i]->getShares(value_count);
    }

    std::cout << "\nPrinting shares of each party....\n" << std::endl;
    RQ_SMPC_Utils::printShareMatrix(shares);
    std::vector<std::vector<int>> share_distributed = RQ_SMPC_Utils::getTranspose(shares);
    std::cout << "\nPrinting shares of to be distributed ....\n" << std::endl;
    RQ_SMPC_Utils::printShareMatrix(share_distributed);

    // Distributing the shares to all the parities.

    std::cout << "****************** Online Phase *******************" << std::endl;
    std::cout << "Distributing the shares to three parties..." << std::endl;
    std::vector<SMPCAdditionParty*> parties(value_count);
    for (int i = 0; i < value_count; ++i) {
        parties[i] = new SMPCAdditionParty(share_distributed[i], CONSTANTS::MODULUS);   // Creating a vector of parties
    }
    std::cout << "\nComputing the partial sum...\n" << std::endl;

    // Computing the partial sum of all parties.
    // High Computational task.
    // Creating a timer here to test the efficiency.

    Timer timer1(__FUNCTION__);
    int total_sum = 0;

    for (const auto& smpc_party: parties) {
        const int temp = smpc_party->computePartialSum();
        total_sum += temp;
        std::cout << temp << std::endl;
    }

    std::cout << "\nTotal Sum....\n" << std::endl;
    std::cout << total_sum % CONSTANTS::MODULUS << std::endl;
    timer1.lapse();
    //TODO: improve this using smart pointers.
    for (const auto& smpc_party: parties)
        delete smpc_party;
    parties.clear();

}

void testShamir() {
    int secret, threshold;
    std::cout << "Enter Secret Value: ", std::cin >> secret;
    std::cout << "Enter Threshold Value: ", std::cin >> threshold;
    std::array arr = {1, 2, 3, 4};
    int i = 2;
    auto poly = ShamirSharing::internal::generate<5>(secret, threshold);
}