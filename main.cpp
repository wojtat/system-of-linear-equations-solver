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

    Matrix matrix = read_matrix(std::cin);
    if (matrix.empty()) {
        // Invalid input
        std::cerr << "Failed to read matrix. Malformed input\n";
        return 2;
    }

    auto solution = solve_system(matrix);
    print_solution(std::cout, solution);

    return 0;
}
