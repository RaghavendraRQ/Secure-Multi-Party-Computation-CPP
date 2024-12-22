//
// Created by raghavendra on 12/2/24.
//
#include "../../include/utils/ShareUtils.h"
#include <iostream>

std::vector<std::vector<int>> RQ_SMPC_Utils::getTranspose(const std::vector<std::vector<int>> &mat) {
    if (mat.empty()) return {};
    const size_t rows = mat.size();
    const size_t cols = mat[0].size();

    std::vector<std::vector<int>> transposed(cols);

    for (size_t i = 0; i < cols; ++i) {
        std::vector<int> row;
        for (size_t j = 0; j < rows; ++j) {
            row.emplace_back(mat[j][i]);
        }
        transposed[i] = row;
    }
    return transposed;
}

void RQ_SMPC_Utils::printShareMatrix(const std::vector<std::vector<int>> &mat) {
    for (int i = 0; i < mat.size(); ++i) {
        std::cout << i + 1 << ": ";
        for (int j = 0; j < mat[0].size(); ++j)
            std::cout << mat[i][j] << " ";
        std::cout << '\n';
    }
}
