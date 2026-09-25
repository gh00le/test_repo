#include <interface.h>

void print_state(const State &state) {
    for (int i = 0; i < 9; ++i) {
        std::cout << state[i] << " ";
        if ((i + 1) % 3 == 0) std::cout << std::endl;
    }
    std::cout << std::endl; 
    return;
}

State parse_state(const std::string &input) {
    State state;
    state.reserve(9);
    std::stringstream ss(input);
    int num;
    while (ss >> num) state.push_back(num);
    return state;
}
