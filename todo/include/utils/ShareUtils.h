//
// Created by raghavendra on 12/2/24.
//

#ifndef SHAREUTILS_H
#define SHAREUTILS_H
#include <vector>
#include <algorithm>

typedef std::vector<std::vector<int>> matrix;

namespace RQ_SMPC_Utils {
    matrix getTranspose(const matrix &mat);
    void printShareMatrix(const matrix &mat);

}



#endif //SHAREUTILS_H
