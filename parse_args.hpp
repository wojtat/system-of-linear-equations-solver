#ifndef SLE_SOLVER_PARSE_ARGS_HPP
#define SLE_SOLVER_PARSE_ARGS_HPP

#include <string>

struct Arguments {
    bool success;
    bool help;
    std::string name;
};

Arguments parse_arguments(int argc, char **argv);

#endif //SLE_SOLVER_PARSE_ARGS_HPP
