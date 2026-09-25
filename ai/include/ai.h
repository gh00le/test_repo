#include <common.h>

struct StateHash {
    size_t operator()(const State& state) const;
};

std::vector<State> reconstruct_path(
        const std::unordered_map<State, State, StateHash>& parent
      , State current);

std::vector<State> BFS_solve(State init_state);

bool dls(const State& state, int depth, int limit, 
        std::vector<State>& solution,
        std::unordered_set<State, StateHash>& closed);

std::vector<State> DLS_solve(State init_state, int limit);

int misplaced_tiles(const State& state);
int manhattan_distance(const State& state);

std::vector<State> EST_solve(State init_state, int (*est)(const State&));