#include "node_state.h"

std::string to_string(NodeState state) {
    switch (state) {
        case NodeState::READY:    return "READY";
        case NodeState::DRAINING: return "DRAINING";
        case NodeState::DOWN:     return "DOWN";
    }
    return "UNKNOWN";
}
