#include <common.h>

bool is_goal(const State& state);

int find_empty(const State& state);

std::vector<int> get_possible_moves(int empty_index);

State make_move(const State& state, int empty_index, int target_index);


