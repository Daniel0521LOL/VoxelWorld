#ifndef CHUNK_DATA_H
#define CHUNK_DATA_H

#include "godot_cpp/templates/local_vector.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/variant/vector3i.hpp"

#include "chunk_constants.h"

using namespace godot;

namespace voxxel {

class ChunkData : public RefCounted {
	GDCLASS(ChunkData, RefCounted)

protected:
	static void _bind_methods();

public:
    ChunkData();
    ~ChunkData() override = default;
    ChunkData(const LocalVector<uint8_t> &p_data) : data(p_data) {}

    uint8_t get_block(const Vector3i &p_pos) const {
        int index = p_pos.x + (p_pos.y * CHUNK_SIZE) + (p_pos.z * CHUNK_SIZE * CHUNK_SIZE);
        if (!in_bounds(p_pos)) {
            return 0; // Return air block for out of bounds
        }
        return data[index];
    }

    void set_block(const Vector3i &p_pos, uint8_t block_id) {
        if (in_bounds(p_pos)) {
            int index = p_pos.x + (p_pos.y * CHUNK_SIZE) + (p_pos.z * CHUNK_SIZE * CHUNK_SIZE);
            data[index] = block_id;
        }
    }

private:
    LocalVector<uint8_t> data;
    bool in_bounds(const Vector3i &p_pos) const {
        return p_pos.x >= 0 && p_pos.x < CHUNK_SIZE &&
               p_pos.y >= 0 && p_pos.y < CHUNK_SIZE &&
               p_pos.z >= 0 && p_pos.z < CHUNK_SIZE;
    }
};

} // namespace voxxel

#endif // CHUNK_DATA_H