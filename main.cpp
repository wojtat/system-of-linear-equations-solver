#include <iostream>
#include "parse_args.hpp"

int main(int argc, char **argv) {
    auto arguments = parse_arguments(argc, argv);
    if (!arguments.success) {
        return 1;
    } else if (arguments.help) {
        return 0;
    }

    return 0;
}
