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
                {2.0, 3.0, 4.0, 6.0}};
    row_reduce(m);
    for (auto &row : m) {
        for (auto &elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
