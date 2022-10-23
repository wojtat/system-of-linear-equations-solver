#ifndef SLE_SOLVER_MATRIX_HPP
#define SLE_SOLVER_MATRIX_HPP

#include <vector>

using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

std::pair<size_t, size_t> get_dimensions(const Matrix &matrix);

void swap_rows(Matrix &matrix, size_t i, size_t j);

void scale_row(Matrix &matrix, size_t i, double scalar);

void add_multiple_of_row(Matrix &matrix, size_t whence, double scalar, size_t where);

void row_reduce(Matrix &matrix);

std::pair<size_t, size_t> get_ranks(const Matrix &reduced_augmented_matrix);

#endif //SLE_SOLVER_MATRIX_HPP
