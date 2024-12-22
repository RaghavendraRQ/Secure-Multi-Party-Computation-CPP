//
// Created by raghavendra on 12/2/24.
//

#ifndef SHAREUTILS_H
#define SHAREUTILS_H
#include <vector>
#include <algorithm>

namespace RQ_SMPC_Utils {
    std::vector<std::vector<int>> getTranspose(const std::vector<std::vector<int>> &mat);
    void printShareMatrix(const std::vector<std::vector<int>> &mat);

}



#endif //SHAREUTILS_H
