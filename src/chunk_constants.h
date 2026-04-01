#ifndef CHUNK_CONSTANTS_H
#define CHUNK_CONSTANTS_H

#include "godot_cpp/core/math.hpp"

using namespace godot;

namespace voxxel {
    constexpr int CHUNK_SIZE = 16;
    constexpr int BLOCK_SIZE = 1;

    namespace Directions {
        const Vector3i UP = Vector3i(0, 1, 0);
        const Vector3i DOWN = Vector3i(0, -1, 0);
        const Vector3i FRONT = Vector3i(0, 0, 1);
        const Vector3i BACK = Vector3i(0, 0, -1);
        const Vector3i RIGHT = Vector3i(1, 0, 0);
        const Vector3i LEFT = Vector3i(-1, 0, 0);
        const Vector3i DIRECTIONS[6] = {UP, DOWN, FRONT, BACK, RIGHT, LEFT};
    }
}

#endif // CHUNK_CONSTANTS_H