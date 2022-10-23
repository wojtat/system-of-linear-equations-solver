#include <algorithm>
#include "matrix.hpp"

std::pair<size_t, size_t> get_dimensions(const Matrix &matrix) {
    return std::make_pair(matrix.size(), matrix[0].size());
}

void swap_rows(Matrix &matrix, size_t i, size_t j) {
    auto dim = get_dimensions(matrix);
    if (i >= dim.first || j >= dim.first || i == j) {
        return;
    }
    std::swap(matrix.at(i), matrix.at(j));
}

void scale_row(Matrix &matrix, size_t i, double scalar) {
    auto dim = get_dimensions(matrix);
    if (scalar == 1.0 || i >= dim.first) {
        return;
    }
    for (auto &elem : matrix[i]) {
        elem *= scalar;
    }
}

void add_multiple_of_row(Matrix &matrix, size_t whence, double scalar, size_t where) {
    auto dim = get_dimensions(matrix);
    if (whence >= dim.first || where >= dim.first || scalar == 0.0) {
        return;
    }
    for (size_t i = 0; i < dim.second; ++i) {
        matrix[where][i] += matrix[whence][i] * scalar;
    }
}

void row_reduce(Matrix &matrix) {
    auto dim = get_dimensions(matrix);
    auto smaller_dim = dim.first < dim.second ? dim.first : dim.second;
    size_t first_unreduced_row = 0;
    for (size_t col = 0; col < smaller_dim; ++col) {
        // Find an unreduced row that has a nonzero element at col
        size_t nonzero_unreduced_row = dim.first;
        for (size_t unreduced_row = first_unreduced_row; unreduced_row < dim.first; ++unreduced_row) {
            if (matrix[unreduced_row][col] != 0.0) {
                nonzero_unreduced_row = unreduced_row;
                break;
            }
        }

        // If such row doesn't exist, we can advance to the next column
        if (nonzero_unreduced_row == dim.first) {
            continue;
        }
        // If it exists, swap it with the first unreduced row
        swap_rows(matrix, first_unreduced_row, nonzero_unreduced_row);
        // And reduce all the following rows
        for (size_t row = first_unreduced_row + 1; row < dim.first; ++row) {
            add_multiple_of_row(matrix, first_unreduced_row, -matrix[row][col] / matrix[first_unreduced_row][col], row);
        }
        // We have reduced one more row
        ++first_unreduced_row;
    }
}

std::pair<size_t, size_t> get_ranks(const Matrix &reduced_augmented_matrix) {
    auto dim = get_dimensions(reduced_augmented_matrix);
    if (dim.second < 2) {
        return std::make_pair(-1, -1);
    }

    // The augmented column will have a nonzero element sooner than the other columns
    size_t A_augmented_rank = -1;
    for (int row = dim.first - 1; row >= 0; --row) {
        if (reduced_augmented_matrix[row][dim.second - 1] != 0.0) {
            A_augmented_rank = row;
            break;
        }
    }
    size_t A_rank = -1;
    for (int row = A_augmented_rank; row >= 0; --row) {
        if (reduced_augmented_matrix[row][dim.second - 2] != 0.0) {
            A_rank = row;
            break;
        }
    }
    return std::make_pair(A_rank + 1, A_augmented_rank + 1);
}
