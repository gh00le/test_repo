#include <ai.h>
#include <interface.h>

int main() {
    std::string input = "3 5 8 0 6 4 1 7 2";
    State start = parse_state(input);
    auto solution = DLS_solve(start, 19);
    print_state(start);
    if (solution.empty()) std::cout << "Solution was not found" << std::endl;
    else for (auto state : solution) print_state(state);
    std::cout << "Solution has been found by " << solution.size() << " turns" << std::endl;
    
    return 0;
}