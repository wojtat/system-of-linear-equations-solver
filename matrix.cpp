#include "matrix.hpp"
#include <algorithm>

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

std::pair<size_t, size_t> get_ranks(const Matrix &matrix) {
    auto dim = get_dimensions(matrix);
    if (dim.second < 2) {
        return std::make_pair(-1, -1);
    }

    auto non_zero = [](double x) {
        return x != 0.0;
    };
    size_t A_augmented_rank = -1;
    for (int row = (int)dim.first - 1; row >= 0; --row) {
        if (std::any_of(matrix[row].begin(), matrix[row].end(), non_zero)) {
            A_augmented_rank = row;
            break;
        }
    }
    size_t A_rank = -1;
    for (int row = A_augmented_rank; row >= 0; --row) {
        if (std::any_of(matrix[row].begin(), matrix[row].end() - 1, non_zero)) {
            A_rank = row;
            break;
        }
    }

    return std::make_pair(A_rank + 1, A_augmented_rank + 1);
}

Vector back_substitute(const Matrix &matrix) {
    auto dim = get_dimensions(matrix);
    Vector vars(dim.first);
    for (int v = (int)dim.first - 1; v >= 0; --v) {
        auto value = matrix[v][dim.second - 1];
        for (int prev = v + 1; prev < (int)dim.first; ++prev) {
            value -= vars[prev] * matrix[v][prev];
        }
        vars[v] = value / matrix[v][v];
    }

    return vars;
}

std::vector<size_t> find_column_mapping(const Matrix &matrix, size_t num_free_variables) {
    auto dim = get_dimensions(matrix);

    // Find pivot and free variable locations
    std::vector<size_t> column_mapping(dim.second - 1);
    {
        size_t free_var_index = dim.first;
        size_t pivot_index = 0;
        size_t row = 0;
        for (size_t col = 0; col < dim.second - 1; ++col) {
            if (matrix[row][col] == 0.0) {
                // Free variable
                column_mapping[free_var_index++] = col;
            } else {
                // Pivot
                column_mapping[pivot_index++] = col;
                if (row < dim.first - 1) {
                    ++row;
                }
            }
        }
    }
    return column_mapping;
}

Vector back_substitute(const Matrix &matrix, size_t num_free_variables, const std::vector<size_t> &column_mapping) {
    auto dim = get_dimensions(matrix);

    Vector vars(dim.first + num_free_variables);

    for (int v_index = (int)(dim.first + num_free_variables - 1); v_index >= (int)dim.first; --v_index) {
        vars[column_mapping[v_index]] = 0.0;
    }
    for (int v_index = (int)dim.first - 1; v_index >= 0; --v_index) {
        auto v = column_mapping[v_index];
        auto value = matrix[v_index][dim.second - 1];
        for (int prev = (int)v + 1; prev < (int)dim.second - 1; ++prev) {
            value -= vars[prev] * matrix[v_index][prev];
        }
        vars[v] = value / matrix[v_index][v];
    }

    return vars;
}

Solution solve_system(const Matrix &augmented) {
    Solution solution;

    auto copy = augmented;
    row_reduce(copy);
    size_t A_rank, A_augmented_rank;
    {
        auto ranks = get_ranks(copy);
        A_rank = ranks.first;
        A_augmented_rank = ranks.second;
    }
    copy.resize(A_augmented_rank);

    auto dim = get_dimensions(copy);
    if (A_rank == A_augmented_rank) {
        auto num_free_variables = dim.second - dim.first - 1;
        if (num_free_variables > 0) {
            auto column_mapping = find_column_mapping(copy, num_free_variables);
            auto sol = back_substitute(copy, num_free_variables, column_mapping);

            for (size_t v_index = dim.first; v_index < sol.size(); ++v_index) {
                Matrix homogenous(dim.first, Vector(dim.first + 1, 0.0));
                for (size_t row = 0; row < dim.first; ++row) {
                    for (size_t col = 0; col < dim.first; ++col) {
                        homogenous[row][col] = copy[row][column_mapping[col]];
                    }
                    homogenous[row][dim.first] = -copy[row][column_mapping[v_index]];
                }

                auto base_vec_short = back_substitute(homogenous);
                Vector base_vec(sol.size());
                for (size_t v = 0; v < dim.first; ++v) {
                    base_vec[column_mapping[v]] = base_vec_short[v];
                }
                for (size_t v = dim.first; v < sol.size(); ++v) {
                    base_vec[column_mapping[v]] = 0.0;
                }
                base_vec[column_mapping[v_index]] = 1.0;
                solution.base.push_back(std::move(base_vec));
            }

            solution.particular_solution = std::move(sol);
        } else {
            // num_free_variables == 0
            solution.particular_solution = back_substitute(copy);
        }
    } else {
        // A_rank < A_augmented_rank
        // No solution
    }

    return solution;
}

void print_solution(std::ostream &out, const Solution &solution) {
    if (solution.particular_solution.empty()) {
        out << "No solution\n";
        return;
    }
    if (solution.base.size() > 0) {
        out << "Infinitely many solutions\n";
        out << "Particular solution:\n";
        for (auto e: solution.particular_solution) {
            out << e << " ";
        }
        out << "\nBase of the homogeneous solution set:\n";
        for (const auto &base_vec : solution.base) {
            for (auto e: base_vec) {
                out << e << " ";
            }
            out << "\n";
        }
    } else {
        out << "One unique solution:\n";
        for (auto e: solution.particular_solution) {
            std::cout << e << " ";
        }
        out << "\n";
    }
}

