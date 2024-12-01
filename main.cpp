#include <iostream>
#include <memory>


#include "todo/include/TaskManager.h"
#include "todo/include/SecretShare.h"
#include "todo/include/Party.h"
#include "todo/include/utils/constants.h"


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
    int value1, value2;
    std::cout << "Offline Phase" << std::endl;
    std::cout << "Enter a value: ";
    std::cin >> value1;
    std::cout << "Enter another value: ";
    std::cin >> value2;

    const std::shared_ptr<AdditiveSecretShare> secretShare = std::make_shared<AdditiveSecretShare>(value1, MODULUS);
    const std::shared_ptr<AdditiveSecretShare> secretShare2 = std::make_shared<AdditiveSecretShare>(value2, MODULUS);
    const std::vector<int> shares = secretShare->getShares();
    const std::vector<int> shares2 = secretShare2->getShares();

    std::cout << shares[0] << " " << shares[1] << " " << shares[2] << std::endl;
    std::cout << shares2[0] << " " << shares2[1] << " " << shares2[2] << std::endl;

    std::vector first_party_shares = {shares[0], shares2[0]};
    std::vector second_party_shares = {shares[1], shares2[1]};
    std::vector third_party_shares = {shares[2], shares2[2]};

    std::cout << "Online Phase" << std::endl;
    std::cout << "Distributing the shares to three parties..." << std::endl;
    SMPCAdditionParty *const party1 = new SMPCAdditionParty(first_party_shares, MODULUS);
    SMPCAdditionParty *const party2 = new SMPCAdditionParty(second_party_shares, MODULUS);
    SMPCAdditionParty *const party3 = new SMPCAdditionParty(third_party_shares, MODULUS);

    std::cout << "Computing the partial sum..." << std::endl;

    std::cout << "Party 1: " << party1->computePartialSum() << std::endl;
    std::cout << "Party 2: " << party2->computePartialSum() << std::endl;
    std::cout << "Party 3: " << party3->computePartialSum() << std::endl;

    std::cout << "The final sum is: " << (party1->partial_sum + party2->partial_sum + party3->partial_sum) % MODULUS <<
            std::endl;

    delete party1;
    delete party2;
    delete party3;

    return 0;
}
