#ifndef SLE_SOLVER_MATRIX_HPP
#define SLE_SOLVER_MATRIX_HPP

#include <vector>
#include <iostream>

using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

struct Solution {
    Vector particular_solution;
    Matrix base;
};

Solution solve_system(const Matrix &augmented);

void print_solution(std::ostream &out, const Solution &solution);

#endif //SLE_SOLVER_MATRIX_HPP
