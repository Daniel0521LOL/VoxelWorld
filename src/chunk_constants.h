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
        // inline int direction_to_face_id(const Vector3i &dir) {
        //     if (dir == Directions::UP) return 0;
        //     if (dir == Directions::DOWN) return 1;
        //     if (dir == Directions::FRONT) return 2;
        //     if (dir == Directions::BACK) return 3;
        //     if (dir == Directions::RIGHT) return 4;
        //     if (dir == Directions::LEFT) return 5;
        //     return -1; // Invalid direction
        // }
    }


}

#endif // CHUNK_CONSTANTS_H