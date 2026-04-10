#include "world_data.h"

using namespace godot;

namespace voxxel {

void WorldData::_bind_methods() {
}

Ref<ChunkData> WorldData::get_chunk(const Vector3i &p_chunk_pos) {
    if (chunks.has(p_chunk_pos)) {
        return chunks[p_chunk_pos];
    }
    return Ref<ChunkData>();
}

Ref<ChunkData> WorldData::initialize_chunk(const Vector3i &p_chunk_pos) {
    if (!chunks.has(p_chunk_pos)) {
        Ref<ChunkData> new_chunk;
        new_chunk.instantiate();
        chunks[p_chunk_pos] = new_chunk;
        return new_chunk;
    }
    return chunks[p_chunk_pos];
}

Ref<RaycastResult> WorldData::raycast(const Vector3 &p_origin, const Vector3 &p_direction, float p_max_distance) {
    Ref<RaycastResult> result;
    result.instantiate();
    result->set_hit(false);

    Vector3 current_position = p_origin;
    Vector3 offsets = p_direction.sign().minf(0.0f);
    Vector3 grid_size = Vector3(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);

    while (true) {
        Vector3 edge_positions = (current_position + offsets).ceil();
        Vector3 edge_times = (current_position - edge_positions).abs() / p_direction;
        current_position += edge_times[edge_times.min_axis_index()] * p_direction;
        float raycast_distance = (p_origin - current_position).length();
        
        if (raycast_distance > p_max_distance) {
            return result;
        }
        
        Vector3i block_pos = Vector3i(current_position);
        Vector3i normal = Vector3i(0, 0, 0);
        normal[edge_times.min_axis_index()] = -p_direction.sign()[edge_times.min_axis_index()];
        Vector3i hit_block_pos = block_pos - normal;
        if (get_block(hit_block_pos) != 0) {
            result->set_hit(true);
            result->set_chunk_pos(hit_block_pos / CHUNK_SIZE);
            result->set_block_pos(hit_block_pos % CHUNK_SIZE);
            result->set_face_normal(normal);
            return result;
        }

        return result;
    }
}

uint8_t WorldData::get_block(const Vector3i &p_global_pos) {
    Vector3i chunk_pos = p_global_pos / CHUNK_SIZE;
    Vector3i local_pos = p_global_pos % CHUNK_SIZE;

    if (chunks.has(chunk_pos)) {
        return chunks[chunk_pos]->get_block(local_pos);
    }
    return 0;
}

} // namespace voxxel