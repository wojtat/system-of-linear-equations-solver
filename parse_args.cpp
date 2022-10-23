#include "parse_args.hpp"
#include <iostream>

static void print_unrecognised_argument(const std::string &arg) {
    std::cerr << "Unrecognised command line argument `" << arg << "`\n";
}

static void print_usage(const std::string &program) {
    std::cout << program << " OPTIONS\n";
    std::cout << "System of Linear Equations solver reads a system of linear\n";
    std::cout << "equations from stdin and uses Gaussian elimination to solve it.\n";
    std::cout << "Possible OPTIONS:\n";
    std::cout << "\t--help, -h: Print this message\n";
    std::cout << "\t--multi-threaded, -mt: Use multiple threads\n";
}

Arguments parse_arguments(int argc, char **argv) {
    Arguments args;
    args.success = true;
    args.name = argv[0];
    int i = 1;
    while (i < argc) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            args.help = true;
            print_usage(args.name);
        } else if (arg == "-m" || arg == "--multi-threaded") {
            args.multi_threaded = true;
        } else {
            args.success = false;
            print_unrecognised_argument(arg);
            break;
        }
        ++i;
    }
    return args;
}
