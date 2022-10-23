#include <iostream>
#include "parse_args.hpp"
#include "matrix.hpp"

int main(int argc, char **argv) {
    auto arguments = parse_arguments(argc, argv);
    if (!arguments.success) {
        return 1;
    } else if (arguments.help) {
        return 0;
    }

    Matrix m = {{1.0, 2.0, 3.0, 5.0},
                {5.0, 4.0, 6.0, 7.0},
                {2.0, 3.0, 4.0, 6.0},};
    auto dim = get_dimensions(m);

    row_reduce(m);
    for (auto &row : m) {
        for (auto &elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
    auto ranks = get_ranks(m);
    std::cout << ranks.first << " " << ranks.second << "\n";
    if (ranks.first == ranks.second) {
        // Has solution
        if (dim.first + 1 < dim.second) {
            // There are free variables
        } else if (dim.first + 1 > dim.second) {
            // There are more equations than variables,
            // but the equations are just linear
            // combinations of each other

        } else {
            // There is exactly one solution
            auto solution = back_substitute(m);
            for (auto e : solution) {
                std::cout << e << " ";
            }
            std::cout << "\n";
        }
    } else {
        // No solution
    }

    return 0;
}
