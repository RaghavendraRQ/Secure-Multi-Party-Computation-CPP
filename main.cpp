#include <memory>

#include "todo/include/TaskManager.h"
#include "todo/include/SecretShare.h"
#include "todo/include/Party.h"
#include "todo/include/utils/constants.h"
#include "todo/include/utils/ShareUtils.h"


void printIt(const std::unique_ptr<TaskManager> &task_manager) {
    task_manager->printAllTasks();
}

//int main() {
//     const auto taskManager = std::make_unique<TaskManager>();
//     std::string title = "Implement SMPC";
//     std::string description = "Implement Secure Multi-Party Computation";
//     std::string title2 = "Implement HE";
//     std::string description2 = "Implement HE";
//     std::string title3 = "Implement Blockchain";
//     std::string description3 = "Implement Blockchain";
//     taskManager->addTask(title, description);
//     taskManager->addTask(title2, description2);
//     taskManager->addTask(title3, description3);
//     taskManager->printAllTasks();
//     taskManager->getTaskById(2)->setPriority(HIGH);
//     printIt(taskManager);
//
//     return 0;
// }

int main() {
    int value_count;
    std::cout << "*************** Offline Phase ***************" << std::endl;
    std::cout << "Modulus value: " << CONSTANTS::MODULUS << std::endl;
    std::cout << "Share Count: " << CONSTANTS::SHARE_COUNT << std::endl;
    std::cout << "Enter a No.of Values: ";
    std::cin >> value_count;
    std::vector<int> values(value_count);

    for (size_t i = 0; i < value_count; i++)
        std::cout << "Enter the value of " << (i+1) << "th value: ", std::cin >> values[i];

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
    matrix share_distributed = RQ_SMPC_Utils::getTranspose(shares);
    std::cout << "\nPrinting shares of to be distributed ....\n" << std::endl;
    RQ_SMPC_Utils::printShareMatrix(share_distributed);


    std::cout << "****************** Online Phase *******************" << std::endl;
    std::cout << "Distributing the shares to three parties..." << std::endl;
    std::vector<SMPCAdditionParty*> parties(value_count);
    for (int i = 0; i < value_count; ++i) {
        parties[i] = new SMPCAdditionParty(share_distributed[i], CONSTANTS::MODULUS);
    }
    std::cout << "\nComputing the partial sum...\n" << std::endl;

    for (const auto& smpc_party: parties)
        std::cout << smpc_party->computePartialSum() << std::endl;

    std::cout << "\nTotal Sum....\n" << std::endl;
    int total_sum = 0;
    for (const auto& smpc_party: parties)
        total_sum += smpc_party->computePartialSum();
    std::cout << total_sum % CONSTANTS::MODULUS << std::endl;

    for (const auto& smpc_party: parties)
        delete smpc_party;
    parties.clear();

    return 0;
}
