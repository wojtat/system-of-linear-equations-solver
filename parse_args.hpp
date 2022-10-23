#ifndef SLE_SOLVER_PARSE_ARGS_HPP
#define SLE_SOLVER_PARSE_ARGS_HPP

#include <string>

struct Arguments {
    bool success;
    bool help;
    bool multi_threaded;
    std::string name;
};

Arguments parse_arguments(int argc, char **argv);

#endif //SLE_SOLVER_PARSE_ARGS_HPP
